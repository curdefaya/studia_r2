#include <iostream>

struct Node{
    int val;
    Node* next;

    Node(int v): val(v), next(nullptr) {}
};

struct queue{
    Node* first = nullptr;
    Node* last = nullptr;

    void enqueue(int value){
        Node* nowy = new Node(value);
        if (first == nullptr){
            first = nowy;
            last = nowy;
        } else {
            last->next = nowy;
            last = nowy;
        }
    }

    void dequeue(){
        if(first == nullptr){
            std::cout<<"\nKolejka jest pusta";
            return;
        }

        Node* temp = first;
        first->next = first;
        delete temp;
        
        if(first==nullptr){
            last==nullptr;
        }
    }


    void getfront(){
        if(first == nullptr){
            std::cout << "\nblad getfront()";
        } else {
            std::cout << "\nget front: " << first->val;
        }
    }

    bool isEmpty(){
        if(first == nullptr){
            // cout << "\nkolejka jest pusta";
            return true;
        }
        return false;
    }

    int size() const{
        int n=0;
        Node* temp = first;
        while(temp!=nullptr){
            // std::cout << "\nAktualny element: " << temp->val;
            n++;
            temp = temp->next;
        }
        return n;
    }


};

int main(){
    queue kolejka;
    kolejka.enqueue(15);
    kolejka.enqueue(20);
    kolejka.enqueue(25);
    kolejka.getfront();
    std::cout << "\ndlugosc: " << kolejka.size();

    
    return 0;
}