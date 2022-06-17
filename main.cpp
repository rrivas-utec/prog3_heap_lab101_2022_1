#include <iostream>
#include <deque>
#include "heap.h"

using namespace std;

int main() {
    heap<int> h1;
    h1.push(10);
    h1.push(4);
    h1.push(30);
    h1.push(11);
    h1.push(1);
    h1.push(50);
    cout << h1.size() << endl;
    cout << "----\n";
    while(!h1.empty()) {
        cout << h1.top() << endl;
        h1.pop();
    }
    cout << "----\n";
    heap<int, deque> h2 = {10, 4, 30, 50, 11, 1, 55, 77};
    cout << h2.size() << endl;
    cout << "----\n";
    while(!h2.empty()) {
        cout << h2.top() << endl;
        h2.pop();
    }
    return 0;
}
