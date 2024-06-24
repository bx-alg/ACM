#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_SIZE = 10;

class CircularQueue {
private:
    int data[MAX_SIZE];
    int front;
    int rear;
    int count;

public:
    CircularQueue() : front(0), rear(0), count(0) {}

    bool isFull() {
        return count == MAX_SIZE;
    }

    bool isEmpty() {
        return count == 0;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "队列满！" << endl;
            return;
        }
        data[rear] = value;
        rear = (rear + 1) % MAX_SIZE;
        count++;
    }

    void dequeue(int n) {
        if (isEmpty()) {
            cout << "队列空！" << endl;
            return;
        }
        if (n > count) {
            cout << "队列中没有足够的元素出队 " << n << " 个元素。" << endl;
            return;
        }
        cout << "出队元素: ";
        for (int i = 0; i < n; ++i) {
            if (isEmpty()) {
                cout << "\n队列空！" << endl;
                return;
            }
            cout << data[front] << " ";
            front = (front + 1) % MAX_SIZE;
            count--;
        }
        cout << endl;
    }

    void peek() {
        if (isEmpty()) {
            cout << "队列空！" << endl;
        } else {
            cout << "队头元素: " << data[front] << endl;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "队列空！" << endl;
            return;
        }
        cout << "队列中的元素: ";
        for (int i = 0; i < count; ++i) {
            cout << data[(front + i) % MAX_SIZE] << " ";
        }
        cout << endl;
    }
};

int main() {
    srand((unsigned) time(0));
    CircularQueue queue;
    for (int i = 0; i < 10; ++i) {
        int num = rand() % 100;
        queue.enqueue(num);
    }
    queue.display();
    int n;
    cout << "请输入出队元素个数 (n < 10): ";
    cin >> n;
    queue.dequeue(n);
    queue.display();
    queue.peek();

    return 0;
}
