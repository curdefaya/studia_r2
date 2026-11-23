#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>

using namespace std;

struct sortStat {
    long long comp = 0;       
    long long operations = 0; 
};

class Vec {
private:
    vector<int> data;

public:
    Vec(vector<int> d) : data(d) {}

    virtual Vec* clone() const {
        return new Vec(*this);
    }

    void bubbleSort(sortStat &a) {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                a.comp++; 
                if (data[j] > data[j + 1]) {
                    a.operations++; 
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void bubbleSort_opt(sortStat &a) {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false; 
            for (int j = 0; j < n - i - 1; j++) {
                a.comp++;
                if (data[j] > data[j + 1]) {
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
                if (data[j] < data[min_idx]) {
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
            int key = data[i];
            int j = i - 1;
            
            while (j >= 0) {
                a.comp++; 
                if (data[j] > key) {
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
        for (int i : data) {
            cout << i << " ";
        }
        cout << "\n";
    }

    virtual ~Vec() = default;
};

Vec makeRand(int n) {
    vector<int> data;
    data.reserve(n);
    for (int i = 0; i < n; i++) {
        data.push_back(rand() % n);
    }
    return Vec(data);
}

void testVector(int size) {
    cout << "TEST DLA TABLICY " << size << " ELEMENTOW\n";

    Vec vec = makeRand(size);

    Vec* v1 = vec.clone();
    sortStat stats1;
    auto start1 = chrono::high_resolution_clock::now();
    v1->bubbleSort_opt(stats1);
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time1 = end1 - start1;

    cout << "Statystyki BubbleSort Opt:\n";
    cout << "Czas: " << time1.count() << " ms\n";
    cout << "Porownania: " << stats1.comp << "\n";
    cout << "Operacje przestawien: " << stats1.operations << "\n\n";
    delete v1;

    Vec* v2 = vec.clone();
    sortStat stats2;
    auto start2 = chrono::high_resolution_clock::now();
    v2->selectionSort(stats2);
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time2 = end2 - start2;

    cout << "Statystyki SelectionSort:\n";
    cout << "Czas: " << time2.count() << " ms\n";
    cout << "Porownania: " << stats2.comp << "\n";
    cout << "Operacje przestawien: " << stats2.operations << "\n\n";
    delete v2;

    Vec* v3 = vec.clone();
    sortStat stats3;
    auto start3 = chrono::high_resolution_clock::now();
    v3->insertionSort(stats3);
    auto end3 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time3 = end3 - start3;

    cout << "Statystyki InsertionSort:\n";
    cout << "Czas: " << time3.count() << " ms\n";
    cout << "Porownania: " << stats3.comp << "\n";
    cout << "Operacje przestawien: " << stats3.operations << "\n\n";
    delete v3;
}

int main() {
    srand(time(nullptr));

    testVector(100);
    testVector(1000);
    testVector(10000);
    testVector(100000);

    return 0;
}