#include <iostream>
#include <vector>

using namespace std;

struct Record {
    int key;
    char id;
};

struct sortStat {
    long long comp = 0;       
    long long operations = 0; 
};

class Vec {
private:
    vector<Record> data;

public:
    Vec(vector<Record> d) : data(d) {}

    virtual Vec* clone() const {
        return new Vec(*this);
    }

    void bubbleSort_opt(sortStat &a) {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false; 
            for (int j = 0; j < n - i - 1; j++) {
                a.comp++;
                if (data[j].key > data[j + 1].key) {
                    a.operations++;
                    swap(data[j], data[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break; 
        }
    }

    void selectionSort(sortStat &a) {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                a.comp++;
                if (data[j].key < data[min_idx].key) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                a.operations++;
                swap(data[i], data[min_idx]);
            }
        }
    }

    void insertionSort(sortStat &a) {
        int n = data.size();
        for (int i = 1; i < n; i++) {
            Record key = data[i];
            int j = i - 1;
            
            while (j >= 0) {
                a.comp++; 
                if (data[j].key > key.key) {
                    data[j + 1] = data[j];
                    a.operations++;
                    j--;
                } else {
                    break;
                }
            }
            data[j + 1] = key;
        }
    }

    void print() const {
        for (const auto &item : data) {
            cout << "(" << item.key << "," << item.id << ") ";
        }
        cout << "\n";
    }

    virtual ~Vec() = default;
};

int main() {
    vector<Record> data = {
        {3, 'A'}, {1, 'B'}, {3, 'C'}, {2, 'D'}, {1, 'E'}, {3, 'F'}
    };

    Vec vec(data);

    cout << "Dane wejsciowe:\n";
    vec.print();
    cout << "\n";

    Vec* v1 = vec.clone();
    sortStat stats1;
    v1->bubbleSort_opt(stats1);
    cout << "BubbleSort Opt:\n";
    v1->print();
    delete v1;

    Vec* v2 = vec.clone();
    sortStat stats2;
    v2->selectionSort(stats2);
    cout << "SelectionSort:\n";
    v2->print();
    delete v2;

    Vec* v3 = vec.clone();
    sortStat stats3;
    v3->insertionSort(stats3);
    cout << "InsertionSort:\n";
    v3->print();
    delete v3;

    return 0;
}