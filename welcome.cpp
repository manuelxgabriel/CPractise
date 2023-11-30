#include <iostream>
#include <vector>

void printVec(std::vector<int>& v){
    for (int num : v){
        std::cout << num << " ";
    }
}

void printArr(const char* arr, int size){
    int count = 0;
    for (int i  = 0; i < size; i++){
        if(arr[i] == 'o'){
            count += 1;
        }

        std::cout << arr[i] << " ";
    }

    std::cout << '\n' << "number of o: " << count;

}

int main() {

  const char arr[] = {"Today was a good day"};
  int size = std::strlen(arr);
  printArr(arr, size);

  std::vector<int> v;
  v.push_back(3);
  v.push_back(8);
  v.push_back(9);

  //printVec(v);

  return 0;

}
