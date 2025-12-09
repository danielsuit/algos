// based on cs3650 starter code

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <stdlib.h>

#define MAX_FILES 128
#define MAX_FILENAME 256
#define MAX_FILE_SIZE 4096
#define DISK_SIZE (1024 * 1024)
#define TYPE_FILE 1
#define TYPE_DIR 2

//files
typedef struct {
  char name[MAX_FILENAME];
  char data[MAX_FILE_SIZE];
  size_t size;
  mode_t mode;
  time_t mod_time;
  time_t access_time;
  // sets to 1 if in use
  int in_use;
  int type;
  int parent_idx; 
} file_t;

typedef struct {
  int num_files;
  file_t files[MAX_FILES];
} filesystem_t;


static filesystem_t *filesystem = NULL;
static const char *disk_path = NULL;

void save_filesystem() {
  if (!disk_path || !filesystem) return;
  FILE *fp = fopen(disk_path, "wb");
  if (!fp) {
    perror("failed to save");
    return;
  }
  fwrite(filesystem, sizeof(filesystem_t), 1, fp);
  fclose(fp);
}
void load_filesystem() {
  if (!disk_path) return;
  FILE *fp = fopen(disk_path, "rb");
  if (!fp) {
    filesystem = calloc(1, sizeof(filesystem_t));
    filesystem->num_files = 0;
    for (int i = 0; i < MAX_FILES; i++) {
      filesystem->files[i].in_use = 0;
    }
    filesystem->files[0].in_use = 1;
    filesystem->files[0].type = TYPE_DIR;
    strcpy(filesystem->files[0].name, "/");
    filesystem->files[0].parent_idx = -1;
    filesystem->files[0].mode = 040755;
    filesystem->files[0].size = 0;
    filesystem->files[0].mod_time = time(NULL);
    filesystem->files[0].access_time = time(NULL);
    filesystem->num_files = 1;
    save_filesystem();
    return;
  }
  filesystem = calloc(1, sizeof(filesystem_t));
  size_t read = fread(filesystem, sizeof(filesystem_t), 1, fp);
  fclose(fp);
  if (read != 1) {
    printf("Error reading filesystem, reinitializing...\n");
    filesystem->num_files = 0;
    for (int i = 0; i < MAX_FILES; i++) {
      filesystem->files[i].in_use = 0;
    }
    save_filesystem();
  }
}
int find_file(const char *name) {
  int rv = -1;
  for (int i = 0; i < MAX_FILES; i++) {
    if (filesystem->files[i].in_use && strcmp(filesystem->files[i].name, name) == 0) {
      return i;
    }
  }
  return rv;
}
int find_free_slot() {
  int rv = -1;
  for (int i = 0; i < MAX_FILES; i++) {
    if (!filesystem->files[i].in_use) {
      return i;
    }
  }
  return rv;
}
void get_parent_path(const char *path, char *parent) {
  if (strcmp(path, "/") == 0) {
    strcpy(parent, "/");
    return;
  }
  const char *last_slash = strrchr(path, '/');
  if (last_slash == path) {
    strcpy(parent, "/");
  }
  else if (last_slash != NULL) {
    size_t len = last_slash - path;
    strncpy(parent, path, len);
    parent[len] = '\0';
  } 
  else {
    strcpy(parent, "/");
  }
}
void get_filename(const char *path, char *filename) {
  if (strcmp(path, "/") == 0) {
    strcpy(filename, "/");
    return;
  }
  const char *last_slash = strrchr(path, '/');
  if (last_slash != NULL) {
    strcpy(filename, last_slash + 1);
  }
  else {
    strcpy(filename, path);
  }
}
int find_dir_by_path(const char *path) {
  if (strcmp(path, "/") == 0) {
    return 0;
  }
  char temp_path[MAX_FILENAME];
  strcpy(temp_path, path);
  char *token;
  char *rest = temp_path;
  int current_dir = 0;
  if (rest[0] == '/') rest++;
  while ((token = strtok_r(rest, "/", &rest))) {
    int found = -1;
    for (int i = 0; i < MAX_FILES; i++) {
      if (filesystem->files[i].in_use && 
        filesystem->files[i].parent_idx == current_dir &&
        strcmp(filesystem->files[i].name, token) == 0) {
        found = i;
        break;
      }
    }
    if (found < 0) {
      return -1;
    }
    current_dir = found;
  }
  return current_dir;
}
int find_in_dir(int parent_idx, const char *name) {
  for (int i = 0; i < MAX_FILES; i++) {
    if (filesystem->files[i].in_use && 
      filesystem->files[i].parent_idx == parent_idx &&
      strcmp(filesystem->files[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}
int find_by_path(const char *path) {
  if (strcmp(path, "/") == 0) {
    return 0;
  }
  char parent_path[MAX_FILENAME];
  char filename[MAX_FILENAME];
  get_parent_path(path, parent_path);
  get_filename(path, filename);
  int parent_idx = find_dir_by_path(parent_path);
  if (parent_idx < 0) {
    return -1;
  }
  return find_in_dir(parent_idx, filename);
}
int is_dir_empty(int dir_idx) {
  for (int i = 0; i < MAX_FILES; i++) {
    if (filesystem->files[i].in_use && filesystem->files[i].parent_idx == dir_idx) {
      return 0;
    }
  }
  return 1;
}
// implementation for: man 2 access
// Checks if a file exists.
int nufs_access(const char *path, int mask) {
  int rv = 0;
  int idx = find_by_path(path);
  if (idx >= 0){
    rv = 0;
  }
  else{
    rv = -ENOENT;
  }
  printf("access(%s, %04o) -> %d\n", path, mask, rv);
  return rv;
}

// Gets an object's attributes (type, permissions, size, etc).
// Implementation for: man 2 stat
// This is a crucial function.
int nufs_getattr(const char *path, struct stat *st) {
  int rv = 0;
  memset(st, 0, sizeof(struct stat));
  int idx = find_by_path(path);
  if (idx < 0) {
    rv = -ENOENT;
  } 
  else {
    if (filesystem->files[idx].type == TYPE_DIR){
      st->st_nlink = 2;
    }
    else{
      st->st_nlink = 1;
    }
    st->st_mode = filesystem->files[idx].mode;
    st->st_size = filesystem->files[idx].size;
    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_mod_time = filesystem->files[idx].mod_time;
    st->st_atime = filesystem->files[idx].access_time;
  }
  printf("getattr(%s) -> (%d) {mode: %04o, size: %ld}\n", path, rv, st->st_mode, st->st_size);
  return rv;
}

// implementation for: man 2 readdir
// lists the contents of a directory
int nufs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
  struct stat st;
  int rv = 0;
  filler(buf, ".", &st, 0);
  filler(buf, "..", &st, 0);
  int dir_idx = find_by_path(path);
  if (dir_idx < 0) {
    rv = -ENOENT;
  }
  else {
    for (int i = 0; i < MAX_FILES; i++) {
      if (filesystem->files[i].in_use && filesystem->files[i].parent_idx == dir_idx) {
        filler(buf, filesystem->files[i].name, &st, 0);
      }
    }
  }
  printf("readdir(%s) -> %d\n", path, rv);
  return 0;
}

// mknod makes a filesystem object like a file or directory
// called for: man 2 open, man 2 link
// Note, for this assignment, you can alternatively implement the create
// function.
int nufs_mknod(const char *path, mode_t mode, dev_t rdev) {
  int rv = 0;
  char parent_path[MAX_FILENAME];
  char filename[MAX_FILENAME];
  get_parent_path(path, parent_path);
  get_filename(path, filename);
  if (strlen(filename) == 0) {
    rv = -EINVAL;
    printf("mknod(%s, %04o) -> %d\n", path, mode, rv);
    return rv;
  }
  int parent_idx = find_dir_by_path(parent_path);
  if (parent_idx < 0) {
    rv = -ENOENT;
    printf("mknod(%s, %04o) -> %d (parent not found)\n", path, mode, rv);
    return rv;
  }
  if (find_in_dir(parent_idx, filename) >= 0) {
    rv = -EEXIST;
    printf("mknod(%s, %04o) -> %d (already exists)\n", path, mode, rv);
    return rv;
  }
  int idx = find_free_slot();
  if (idx < 0) {
    rv = -ENOSPC;
    printf("mknod(%s, %04o) -> %d (no space)\n", path, mode, rv);
    return rv;
  }
  strncpy(filesystem->files[idx].name, filename, MAX_FILENAME - 1);
  filesystem->files[idx].name[MAX_FILENAME - 1] = '\0';
  filesystem->files[idx].size = 0;
  filesystem->files[idx].mode = mode | 0100000;
  filesystem->files[idx].mod_time = time(NULL);
  filesystem->files[idx].access_time = time(NULL);
  filesystem->files[idx].in_use = 1;
  filesystem->files[idx].type = TYPE_FILE;
  filesystem->files[idx].parent_idx = parent_idx;
  memset(filesystem->files[idx].data, 0, MAX_FILE_SIZE);
  filesystem->num_files++;
  save_filesystem();
  printf("mknod(%s, %04o) -> %d\n", path, mode, rv);
  return rv;
}

// most of the following callbacks implement
// another system call; see section 2 of the manual
int nufs_mkdir(const char *path, mode_t mode) {
  int rv = 0;
  char parent_path[MAX_FILENAME];
  char dirname[MAX_FILENAME];
  get_parent_path(path, parent_path);
  get_filename(path, dirname);
  if (strlen(dirname) == 0) {
    rv = -EINVAL;
    printf("mkdir(%s) -> %d\n", path, rv);
    return rv;
  }
  int parent_idx = find_dir_by_path(parent_path);
  if (parent_idx < 0) {
    rv = -ENOENT;
    printf("mkdir(%s) -> %d (parent not found)\n", path, rv);
    return rv;
  }
  if (find_in_dir(parent_idx, dirname) >= 0) {
    rv = -EEXIST;
    printf("mkdir(%s) -> %d (already exists)\n", path, rv);
    return rv;
  }
  int idx = find_free_slot();
  if (idx < 0) {
    rv = -ENOSPC;
    printf("mkdir(%s) -> %d (no space)\n", path, rv);
    return rv;
  }
  strncpy(filesystem->files[idx].name, dirname, MAX_FILENAME - 1);
  filesystem->files[idx].name[MAX_FILENAME - 1] = '\0';
  filesystem->files[idx].size = 0;
  filesystem->files[idx].mode = 040755; // Directory
  filesystem->files[idx].mod_time = time(NULL);
  filesystem->files[idx].access_time = time(NULL);
  filesystem->files[idx].in_use = 1;
  filesystem->files[idx].type = TYPE_DIR;
  filesystem->files[idx].parent_idx = parent_idx;
  filesystem->num_files++;
  save_filesystem();
  printf("mkdir(%s) -> %d\n", path, rv);
  return rv;
}

int nufs_unlink(const char *path) {
  int rv = 0;
  int idx = find_by_path(path);
  if (idx < 0) {
    rv = -ENOENT;
  } 
  else if (filesystem->files[idx].type == TYPE_DIR) {
    rv = -EISDIR;
  } 
  else {
    filesystem->files[idx].in_use = 0;
    filesystem->files[idx].name[0] = '\0';
    filesystem->files[idx].size = 0;
    filesystem->num_files--;
    save_filesystem();
  }
  printf("unlink(%s) -> %d\n", path, rv);
  return rv;
}

int nufs_link(const char *from, const char *to) {
  int rv = -1;
  printf("link(%s => %s) -> %d\n", from, to, rv);
  return rv;
}

int nufs_rmdir(const char *path) {
  int rv = 0;
  if (strcmp(path, "/") == 0) {
    rv = -EINVAL;
    printf("rmdir(%s) -> %d (can't remove root)\n", path, rv);
    return rv;
  }
  int idx = find_by_path(path);
  if (idx < 0) {
    rv = -ENOENT;
  } 
  else if (filesystem->files[idx].type != TYPE_DIR) {
    rv = -ENOTDIR;
  } 
  else if (!is_dir_empty(idx)) {
    rv = -ENOTEMPTY;
  } 
  else {
    filesystem->files[idx].in_use = 0;
    filesystem->files[idx].name[0] = '\0';
    filesystem->num_files--;
    save_filesystem();
  }
  printf("rmdir(%s) -> %d\n", path, rv);
  return rv;
}

// implements: man 2 rename
// called to move a file within the same filesystem
int nufs_rename(const char *from, const char *to) {
  int rv = 0;
  int from_idx = find_by_path(from);
  if (from_idx < 0) {
    rv = -ENOENT;
    printf("rename(%s => %s) -> %d (source not found)\n", from, to, rv);
    return rv;
  }
  char new_parent_path[MAX_FILENAME];
  char new_filename[MAX_FILENAME];
  get_parent_path(to, new_parent_path);
  get_filename(to, new_filename);
  int new_parent_idx = find_dir_by_path(new_parent_path);
  if (new_parent_idx < 0) {
    rv = -ENOENT;
    printf("rename(%s => %s) -> %d (dest parent not found)\n", from, to, rv);
    return rv;
  }
  int to_idx = find_in_dir(new_parent_idx, new_filename);
  if (to_idx >= 0 && to_idx != from_idx) {
    rv = -EEXIST;
    printf("rename(%s => %s) -> %d (dest exists)\n", from, to, rv);
    return rv;
  }
  strncpy(filesystem->files[from_idx].name, new_filename, MAX_FILENAME - 1);
  filesystem->files[from_idx].name[MAX_FILENAME - 1] = '\0';
  filesystem->files[from_idx].parent_idx = new_parent_idx;
  filesystem->files[from_idx].mod_time = time(NULL);
  save_filesystem();
  printf("rename(%s => %s) -> %d\n", from, to, rv);
  return rv;
}

int nufs_chmod(const char *path, mode_t mode) {
  int rv = -1;
  printf("chmod(%s, %04o) -> %d\n", path, mode, rv);
  return rv;
}

int nufs_truncate(const char *path, off_t size) {
  int rv = 0;
  int idx = find_by_path(path);
  if (idx < 0) {
    rv = -ENOENT;
  } 
  else if (filesystem->files[idx].type == TYPE_DIR) {
    rv = -EISDIR;
  } 
  else {
    if (size > MAX_FILE_SIZE) {
      size = MAX_FILE_SIZE;
    }
    if (size < filesystem->files[idx].size) {
      memset(filesystem->files[idx].data + size, 0, filesystem->files[idx].size - size);
    }
    filesystem->files[idx].size = size;
    filesystem->files[idx].mod_time = time(NULL);
    save_filesystem();
  }
  printf("truncate(%s, %ld bytes) -> %d\n", path, size, rv);
  return rv;
}

// This is called on open, but doesn't need to do much
// since FUSE doesn't assume you maintain state for
// open files.
// You can just check whether the file is accessible.
int nufs_open(const char *path, struct fuse_file_info *fi) {
  int rv = 0;
  printf("open(%s) -> %d\n", path, rv);
  return rv;
}

// Actually read data
int nufs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
  int rv = 0;
  int idx = find_by_path(path);
  if (idx < 0) {
    rv = -ENOENT;
  }
  else if (filesystem->files[idx].type == TYPE_DIR) {
    rv = -EISDIR;
  }
  else {
    if (offset >= filesystem->files[idx].size) {
      rv = 0;
    } 
    else {
      if (offset + size > filesystem->files[idx].size) {
        size = filesystem->files[idx].size - offset;
      }
      memcpy(buf, filesystem->files[idx].data + offset, size);
      filesystem->files[idx].access_time = time(NULL);
      rv = size;
    }
  }
  printf("read(%s, %ld bytes, @+%ld) -> %d\n", path, size, offset, rv);
  return rv;
}

// Actually write data
int nufs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
  int rv = 0;
  int idx = find_by_path(path);
  if (idx < 0) {
    rv = -ENOENT;
  }
  else if (filesystem->files[idx].type == TYPE_DIR) {
    rv = -EISDIR;
  }
  else {
    if (offset + size > MAX_FILE_SIZE) {
      size = MAX_FILE_SIZE - offset;
      if (size <= 0) {
        rv = -EFBIG;
        printf("write(%s, %ld bytes, @+%ld) -> %d (too large)\n", path, size, offset, rv);
        return rv;
      }
    }
    memcpy(filesystem->files[idx].data + offset, buf, size);
    if (offset + size > filesystem->files[idx].size) {
      filesystem->files[idx].size = offset + size;
    }
    filesystem->files[idx].mod_time = time(NULL);
    save_filesystem();
    rv = size;
  }
  printf("write(%s, %ld bytes, @+%ld) -> %d\n", path, size, offset, rv);
  return rv;
}

// Update the timestamps on a file or directory.
int nufs_utimens(const char *path, const struct timespec ts[2]) {
  int rv = -1;
  printf("utimens(%s, [%ld, %ld; %ld %ld]) -> %d\n", path, ts[0].tv_sec,
         ts[0].tv_nsec, ts[1].tv_sec, ts[1].tv_nsec, rv);
  return rv;
}

// Extended operations
int nufs_ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) {
  int rv = -1;
  printf("ioctl(%s, %d, ...) -> %d\n", path, cmd, rv);
  return rv;
}

void nufs_init_ops(struct fuse_operations *ops) {
  memset(ops, 0, sizeof(struct fuse_operations));
  ops->access = nufs_access;
  ops->getattr = nufs_getattr;
  ops->readdir = nufs_readdir;
  ops->mknod = nufs_mknod;
  // ops->create   = nufs_create; // alternative to mknod
  ops->mkdir = nufs_mkdir;
  ops->link = nufs_link;
  ops->unlink = nufs_unlink;
  ops->rmdir = nufs_rmdir;
  ops->rename = nufs_rename;
  ops->chmod = nufs_chmod;
  ops->truncate = nufs_truncate;
  ops->open = nufs_open;
  ops->read = nufs_read;
  ops->write = nufs_write;
  ops->utimens = nufs_utimens;
  ops->ioctl = nufs_ioctl;
};

struct fuse_operations nufs_ops;

int main(int argc, char *argv[]) {
  assert(argc > 2 && argc < 6);
  disk_path = argv[--argc];
  load_filesystem();
  nufs_init_ops(&nufs_ops);
  return fuse_main(argc, argv, &nufs_ops, NULL);
}
