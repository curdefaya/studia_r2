#include <iostream>

#include <vector>

using namespace std;

class Vec {
    private:
        vector < int > data;

    public:
    Vec(vector<int> d) : data(d) {}

    void bubbleSort() {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1])
                    swap(data[j], data[j + 1]);
            }
        }
    }

    void bubbleSort_opt() {
        int n = data.size();
        bool
        breakl = false;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                    breakl = true;
                }
            }
            if (!
                breakl) break;
        }
    }

    void selectionSort() {
        int n = data.size();
        int min;
        for (int i = 0; i < n - 1; i++) {
            min = i;
            for (int j = i + 1; j < n; j++) {
                if (data[j] < data[min]) {
                    min = j;
                }
            }
            swap(data[i], data[min]);
        }
    }

    void insertionSort() {
        int n = data.size();
        for (int i = 0; i < n; i++) {
            int k = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > k) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = k;
        }
    }

    void print() {
        cout << "\n";
        for (int i: data) {
            cout << i << " ";
        }
    }


};

int main() {
    // vector < int > data = {
    //     10,
    //     2,
    //     3,
    //     1,
    //     9,
    //     4,
    //     15,
    //     10,
    //     11
    // };
    // print_vec(data);
    // selectionSort(data);
    // print_vec(data);

    Vec v({
        1,
        4,
        2,
        6,
        3,
        8,
        4
    });

    cout << "Przed sortowaniem: ";
    v.print();

    v.bubbleSort_opt();

    cout << "\nPo sortowaniu:    ";
    v.print();
    return 0;
}