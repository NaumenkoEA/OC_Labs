#include <iostream>
#include <windows.h>
#include <algorithm>
using namespace std;

CRITICAL_SECTION cs;
HANDLE event1, event2;

struct dataArray {
    int size;
    char* array;
    int K;
    char sum = 0;
};

DWORD WINAPI work(void* obj) {

    dataArray* dAr = (dataArray*)obj;
    char* mas = dAr->array;

    cout << "Thread work is started" << endl;
    int time;
    cout << "Input time interval to sleep: ";
    cin >> time;

    for (int i = 0; i < dAr->size - 1; i++)
    {
        int imin = i;
        for (int j = i + 1; j < dAr->size; j++)
            if (mas[j] < mas[imin]) imin = j;
        char a = mas[i];
        mas[i] = mas[imin];
        mas[imin] = a;
    }

    for (int i = 0; i < dAr->size; i++) {
        cout << mas[i] << " ";
        Sleep(time);
    }
    cout << endl << "Thread work is finished" << endl;

    SetEvent(event1);
    return 0;
}

DWORD WINAPI sumElement(LPVOID  obj) {
    /*WaitForSingleObject(event2, INFINITE);
    EnterCriticalSection(&cs);
    dataArray* dAr = (dataArray*)obj;
    char* mas = dAr->array;
    cout << "Thread sumElement is started" << endl;

    int sum = 0;
    int count = 0 ;
    if(dAr->K <=dAr->size){
        int time;
        cout << "Input time interval to sleep:";
        cin >> time;
    for (int i = 0; i < dAr->K ; i++) {

        sum += mas[i];
        cout<<" sum ["<<i+1<<"] ="<< sum <<endl;
        Sleep(time);
    }
    }
    double average = sum / dAr->K;
    cout << "\nAverage of array is " <<average << endl;
    cout << endl << "Thread sumElement is finished" << endl;
    LeaveCriticalSection(&cs);
    return 0;*/

    WaitForSingleObject(event2, INFINITE);
    EnterCriticalSection(&cs);
    dataArray* Arr = (dataArray*)obj;
    for (int i = 0; i < Arr->K; i++) {
        Arr->sum += Arr->array[i];
    }
    Arr->sum /= Arr->K;
    cout << "\nAverage of array is " <<Arr->sum << endl;
    LeaveCriticalSection(&cs);

    return 0;
}

int main() {
    int size;
    cout << "Input size of array: ";
    cin >> size;
    char* array = new char[size];
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }

    cout << "The size of array is " << size << endl;
    cout << "Array: " << endl;
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    event1 = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (event1 == NULL)
        return GetLastError();
    event2 = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (event2 == NULL)
        return GetLastError();
    InitializeCriticalSection(&cs);

    dataArray* d = new dataArray();
    d->size = size;
    d->array = array;
    int k;
    cout << endl << "Input number K: ";
    cin >> k;
    d->K = k;

    InitializeCriticalSection(&cs);
    HANDLE hThread;
    DWORD IDThread;
    HANDLE hThread2;
    DWORD IDThread2;
    hThread = CreateThread(NULL, 0, work, (void*)d, 0, &IDThread);
    if (hThread == NULL)
        return GetLastError();
    hThread2 = CreateThread(NULL, 0, sumElement, (void*)d, 0, &IDThread2);
    if (hThread2 == NULL)
        return GetLastError();

    WaitForSingleObject(event1, INFINITE);

    SetEvent(event2);
    Sleep(10);
    EnterCriticalSection(&cs);

    LeaveCriticalSection(&cs);
    DeleteCriticalSection(&cs);
    CloseHandle(hThread);
    CloseHandle(hThread2);

    delete[] array;
    return 0;
}