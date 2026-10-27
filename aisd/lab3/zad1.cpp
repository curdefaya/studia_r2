#include <iostream>

struct Node {
    int val;
    Node* next;
};

struct Stack {
    Node* top = nullptr;

    void push(int value) {
        Node* newN = new Node();
        newN->val = value;
        newN->next = top;
        top = newN;
    }

    void pop() {
        if (top == nullptr) return;

        Node* temp = top;
        top = top->next;
        delete temp;
    }

    void peek() const {
        if (top != nullptr) {
            std::cout << "\ntop_val " << top->val;
        } else {
            std::cout << "\nStos jest pusty";
        }
    }

    ~Stack() {
        while (top != nullptr) {
            pop();
        }
    }
};

int main() {
    Stack stos;

    stos.push(20);
    stos.push(5);
    stos.push(15);

    stos.peek();

    stos.pop();

    stos.peek();

    return 0;
}