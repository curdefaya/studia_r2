#include <iostream>
#include <string>

struct Node {
    char val;
    Node* next;
};

struct Stack {
    Node* top = nullptr;

    void push(char value) {
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

    char peek() const {
        if (top != nullptr) {
            // std::cout << "\ntop_val " << top->val;
            return top->val;
        } else {
            std::cout << "\nStos jest pusty";
            return '\0';
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
    bool czyBledne = false;
    std::string wyrazenie = "(a + b) * [c - {d / e}]";

    int n = wyrazenie.length();
    for (int i = 0; i<n; i++){
        if(wyrazenie[i] == '(' || wyrazenie[i] == '{' || wyrazenie[i] == '[' ){
            stos.push(wyrazenie[i]);
        } else if(wyrazenie[i] == ')' || wyrazenie[i]=='}' || wyrazenie[i]==']'){

            if (wyrazenie[i] == ')' && stos.peek() == '('){
                stos.pop();
            } else if(wyrazenie[i] == '}' && stos.peek() == '{'){
                stos.pop();
            } else if(wyrazenie[i] == ']' && stos.peek() == '['){
                stos.pop();
            } else {
                czyBledne = true;
                break;
            }
        }
        
    }
    if (stos.peek() == '\0' && !czyBledne){
        std::cout<<"\nPOPRAWNE";
    } else {
        std::cout<<"\nNIEPOPRAWNE";
    }

    return 0;
}