// 2021111945 송하연 
// prac3 문제2

#include <iostream>
using namespace std;


void heapify(int A[], int root, int n) {
    int parent, left_son, right_son, root_value, son;
    parent = root;
    root_value = A[root];
    left_son = 2 * parent + 1; // 배열 인덱스라 +1
    right_son = left_son + 1;

    while (left_son < n) { // 배열 인덱스가 n-1까지이므로 < n 사용
        if (right_son < n && A[left_son] < A[right_son]) { // 자식 노드 중 더 큰 값
            son = right_son;
        } else {
            son = left_son;
        }

        if (root_value < A[son]) {
            A[parent] = A[son]; // 새로운 부모 노드
            parent = son;

            left_son = parent * 2 + 1;
            right_son = left_son + 1;
        } else {
            break;
        }
    }
    A[parent] = root_value;  
}

void makeHeap(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) { // 정렬할 배열 힙 변환 : 말단 노드의 부모 n / 2 - 1
        heapify(A, i, n);
    }
}

void heapSort(int A[], int n) {
    makeHeap(A, n); 

    for (int i = n - 1; i > 0; i--) {
        swap(A[0], A[i]); 
        heapify(A, 0, i); 
    }
}



int main() {
    cout << "\n============2021111945 송하연 prac3 문제2 ================\n\n";
    
    int A[] = {4,1,3,2,16,9,10,14,8,7}; 
    int n = sizeof(A) / sizeof(A[0]); 
    
    cout << "\n초기 배열:";
     for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }

    makeHeap(A, n); 
    cout << "\n생성된 최대 힙 배열: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    heapSort(A, n);
    cout << "힙 정렬 결과: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    return 0;
}
