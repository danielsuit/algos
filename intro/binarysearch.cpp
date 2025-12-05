#include <vector>
#include <iostream>
void binary_search(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    std::size_t len = sizeof(arr) / sizeof(arr[0]);
    int mid = len / 2;
    int pos = -1;
    for(int i = 0; i < len; i++){
        if(arr[mid] == i){
            pos = mid;
            std::cout << "Element " << i << " found at position: " << pos << std::endl;
            break;
        }
        else if(arr[mid] < i){
            mid = (mid + len) / 2;
        }
        else{
            mid = mid / 2;
        }
    }
}
int main() {
    binary_search();
    return 0;
}