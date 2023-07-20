#include<iostream>
#include<vector>

using namespace std;

long long number;

bool isPalindrome(long long k) { // O(|n|) , n = number and |n| = digits 
    long long reverse = 0;
    long long temp = number;
    while(temp != 0) {
        int k = temp % 10;
        reverse = (reverse * 10) + k;
        temp /= 10;
    }
    return number == reverse;
}

void next_palindrome(long long input) {
    while(!isPalindrome(number)) { // O(n * |n|)
        number++;
    }
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> number;
        number += 1;
        next_palindrome(number);
        cout << number << endl;
    }
    return 0;
}