//2021111945 송하연 

#include <iostream>

using namespace std;
int level = 1;

void PrintArray(int* A, int n, int level) {

    cout << level <<"단계 : ";
    for (int i = 0; i < n; i++) {
        cout  <<"["<< A[i] <<"]" << " ";
    }
    cout << endl;
}


//비순환적 버블
void Bubble(int* A, int n){ 
    bool Sorted = false;
      while(!Sorted){
        Sorted = true;
        for(int i = 0; i < n-1; i++){
            if(A[i] > A[i+1]){
                swap(A[i], A[i+1]);
                Sorted = false;
            }
              PrintArray(A,n,level);
        }
        level++;
    }
 

}


//순환적 버블
void RecursiveBubble(int* A, int n){ 

   if (n <=  1 ) return;
   bool Sorted = true; 

   for(int i = 0; i < n-1; i++){ 
        if(A[i] > A[i+1]){
            swap(A[i], A[i+1]);
            Sorted = false;
        }
            PrintArray(A,n,level);
    }
    level ++;
    if (Sorted) return;
    RecursiveBubble(A, n);
}


int main() {
    cout << "=========== 2021111945 송하연 ===========" << endl;
    int size; 
    cout << "배열의 크기를 입력하세요 : " ; 
    cin >>  size;
    int* A = new int[size];

    cout << "배열의 요소를 입력하세요(" << size << "개 입력) : ";
    for(int j = 0; j < size; j++){
        cin >> A[j];
    }

int choice;
    cout << "정렬 방법을 선택하세요 (1: 비순환적, 2: 순환적) : ";
    cin >> choice;

    if (choice == 1) {
        cout << "=========== 비순환적 버블 정렬 ===========" << endl;
        Bubble(A, size);
    } else if (choice == 2) {
        cout << "=========== 순환적 버블 정렬 ===========" << endl;
        RecursiveBubble(A, size); 
    } 
    delete[] A;

    return 0;
}
