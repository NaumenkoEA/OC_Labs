#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

void fillArr (int arrSize ,unsigned int *arr);
void outArr (int arrSize ,unsigned int *arr);
void outSortArr(int arrSize ,unsigned int *arr);

int main() {
    srand ( time(NULL) );

    int arrSize;

    std::cout << "\n Hello!" << std::endl;


    arrSize = rand() % 10 +1;
    std::cout << " The dimension of the array is random  "<< arrSize<< std::endl;
    unsigned int *arr = new unsigned int [arrSize];

    fillArr(arrSize,arr);
    outArr(arrSize,arr);
    std::thread worker(outSortArr, std::ref(arrSize),std::ref(arr));


    worker.join();
    delete [] arr;
    return 0;
}
void outSortArr(int arrSize ,unsigned int *arr){
    std::cout<<" Numbers with one at the end : ";
    for (int i = 0; i < arrSize ; i ++){
        if(arr[i] % 10 == 1){
           std::cout<<arr[i]<<"\t";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    std::cout <<"\n";
}
void fillArr (int arrSize , unsigned int *arr){

    for(int i=0 ;i < arrSize ; i++){
        arr[i] =rand() % 100 +1 ;
    }
}
void outArr (int arrSize ,unsigned int *arr){
    for(int i = 0 ; i < arrSize; i++){
        std::cout<<i+1<<":\t"<< arr[i]<<"\n";
    }
}