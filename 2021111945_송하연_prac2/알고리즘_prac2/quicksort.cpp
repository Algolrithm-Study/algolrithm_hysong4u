//2021111945 송하연 

#include <iostream>
#include <stack>
#include<algorithm>
#include <set>

using namespace std;
const int MAX_LENTH = 10;

void GenerateRandomArray(int N[], int size) {
    srand(static_cast<unsigned int>(time(0)));
    
    set<int> uniqueNumbers; 

    while (uniqueNumbers.size() < size) {
        int randomNum = rand() % 100000 + 1; 
        uniqueNumbers.insert(randomNum); 
    }

    int index = 0;
    for (int num : uniqueNumbers) {
        N[index++] = num;
    }
}

void PrintArray(int A[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "]" << " ";
    }
    cout << endl;
}


void PrintStep(int A[], int n, int pivotIndex, int left, int right) {
    cout << "배열 상태: ";
    PrintArray(A, n);
    cout << "선택된 피벗: [" << A[pivotIndex] << "] " <<  " Left: " << left << "  Right: " << right << endl << endl;
}


int Partition(int A[], int Left, int Right) {
    int PartElem = Left;
    int Value = A[PartElem];

    while (Left < Right) {
        while (Left < Right && A[Right] <= Value) { //pivot보다 큰 값이 나올 때까지
            Right--;
        }
        while (Left < Right && A[Left] >= Value) { //pivot보다 작은 값이 나올 때까지
            Left++;
        }
        if (Left < Right) {
            swap(A[Left], A[Right]);
        }
    }
    swap(A[PartElem], A[Right]); 
    return Right; 
}

void RecursiveQuickSort(int A[], int Left, int Right) {
    if (Left < Right) {
        int PartIndex = Partition(A, Left, Right);
        PrintStep(A, Right + 1, PartIndex, Left, Right);
        RecursiveQuickSort(A, Left, PartIndex - 1);
        RecursiveQuickSort(A, PartIndex + 1, Right);
    }
}

void QuickSort(int A[], int n){
    stack<int> s;
    s.push(0);
    s.push(n-1);
    while(!s.empty()){
        int Right = s.top(); s.pop();
        int Left = s.top(); s.pop();

        if (Left < Right) {
        int PartIndex = Partition(A,Left,Right);
        PrintStep(A, n, PartIndex, Left, Right);
         if (PartIndex - 1 > Left) {
                s.push(Left);
                s.push(PartIndex - 1);
            }
        if (PartIndex + 1 < Right) {
                s.push(PartIndex + 1);
                s.push(Right);
            }
        }
    }
    
}

int main() {
    cout << "\n=========== 2021111945 송하연 ===========" << endl << endl;
    int A[MAX_LENTH]; 

    cout << "\n=========== 정렬 전 배열  ===========" << endl;
    GenerateRandomArray(A, MAX_LENTH);
    PrintArray(A, MAX_LENTH);

    cout << "\n=========== 순환적 퀵 정렬 ===========" << endl;
    RecursiveQuickSort(A, 0, 9);

    cout << "\n=========== 순환적 퀵 정렬 최종 결과 ============" << endl;
    PrintArray(A, MAX_LENTH); 

    cout << "\n=========== 정렬 전 배열 ===========" << endl;
    GenerateRandomArray(A, MAX_LENTH);
    PrintArray(A, MAX_LENTH);

    cout << "\n=========== 비순환적 퀵 정렬 ===========" << endl;
    QuickSort(A, MAX_LENTH);

    cout << "\n=========== 비순환적 퀵 정렬 최종 결과 ============" << endl;
    PrintArray(A, MAX_LENTH); 

    return 0;
}
