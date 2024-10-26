// 2021111945 송하연 
// prac3 문제1

#include <iostream>
#include <fstream>
using namespace std;

// 반복적 회문 검사
bool check_palindrome(string word) {
    int length = 0;
    bool is_palindrome = true;

    while (word[length] != '\0') {
        length++;
    }
    int left = 0;
    int right = length - 1;

    while (left < right) {
        if (word[left] != word[right]) {
            is_palindrome = false;
            break;
        }
        left++;
        right--;
    }

    return is_palindrome;
}

// 순환적 회문 검사
bool recursive_palindrome(string word, int left, int right) {
    if (left >= right) {
        return true;
    }

    if (word[left] != word[right]) {
        return false;
    }

    return recursive_palindrome(word, left + 1, right - 1);
}

int main() {
    cout << "============2021111945 송하연 prac3 문제1 ================" << endl <<endl;
    ifstream file("palindrome.txt");

    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다." << endl;
        return 1;
    }

    string line;

    while (getline(file, line)) { 
        cout << line << endl;
        
        if (check_palindrome(line)) {
            cout << line << "는 반복적으로 회문입니다" << endl ;
        } else {
            cout << line << "는 반복적으로 회문이 아닙니다" << endl ;
        }

 
        if (recursive_palindrome(line, 0, line.length() - 1)) {
            cout << line << "는 순환적으로 회문입니다" << endl << endl;
        } else {
            cout << line << "는 순환적으로 회문이 아닙니다" << endl << endl;
        }
    }

    file.close();
    return 0;
}
