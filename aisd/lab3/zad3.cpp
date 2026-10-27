#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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

    int peek() const {
        if (top != nullptr) {
            // std::cout << "\ntop_val " << top->val;
            return top->val;
        } else {
            std::cout << "\nStos jest pusty";
            return -1;
        }
    }

    ~Stack() {
        while (top != nullptr) {
            pop();
        }
    }
};

void ONP(std::string wyrazenie){
    Stack stos;
    std::stringstream ss(wyrazenie);
    std::string el;
    std::vector<std::string> elementy;
    while(ss>>el){
        elementy.push_back(el);
    }
    for (const auto& w : elementy) {
        // std::cout << w << "\n";
        if (w == "+" || w == "-" || w == "*" || w == "/"){
            int a = stos.peek();
            stos.pop();
            int b = stos.peek();
            stos.pop();

            if (w == "+") {stos.push(a+b);}
            if (w == "-") {stos.push(a-b);}
            if (w == "*") {stos.push(a*b);}
            if (w == "/") {stos.push(a/b);}
        }else {
            int liczba = std::stoi(w);
            stos.push(liczba);
        }

    }
    std::cout << "\n" <<  stos.peek(); 
}

int main() {
    std::string wyrazenie = "5 2 3 * +";
    ONP(wyrazenie);

    return 0;
}