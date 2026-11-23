#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>

using namespace std;

long long comparisons = 0;
long long swapsCount = 0;
int currentDepth = 0;
int maxDepth = 0;
bool randomPivot = false;

int partition(vector<int>& data, int left, int right) {
    if (randomPivot) {
        int pivotPosition = left + rand() % (right - left + 1);
        swap(data[pivotPosition], data[right]);
        swapsCount++;
    }

    int pivot = data[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        comparisons++;

        if (data[j] < pivot) {
            i++;
            swap(data[i], data[j]);
            swapsCount++;
        }
    }

    swap(data[i + 1], data[right]);
    swapsCount++;
    return i + 1;
}

void quickSort(vector<int>& data, int left, int right) {
    currentDepth++;
    if (currentDepth > maxDepth) {
        maxDepth = currentDepth;
    }

    if (left < right) {
        int pivotPosition = partition(data, left, right);

        quickSort(data, left, pivotPosition - 1);
        quickSort(data, pivotPosition + 1, right);
    }

    currentDepth--;
}

void resetStats() {
    comparisons = 0;
    swapsCount = 0;
    currentDepth = 0;
    maxDepth = 0;
}

vector<int> createData(int n, int type) {
    vector<int> data(n);

    if (type == 0) {
        for (int i = 0; i < n; i++) {
            data[i] = rand() % (n * 10 + 1);
        }
    } else {
        for (int i = 0; i < n; i++) {
            data[i] = i + 1;
        }

        if (type == 2) {
            reverse(data.begin(), data.end());
        }
    }

    return data;
}

void printMeasurements() {
    cout << "\n";
    cout << left << setw(12) << "Dane"
         << " " << right << setw(8) << "n"
         << " " << left << setw(14) << "Pivot"
         << " " << right << setw(16) << "Porownania"
         << " " << setw(14) << "Zamiany"
         << setw(18) << "Maks. glebokosc" << "\n";

    // type: 0 - losowe, 1 - rosnace, 2 - malejace
    for (int type = 0; type <= 2; type++) {
        const char* dataName;

        if (type == 0) {
            dataName = "losowe";
        } else if (type == 1) {
            dataName = "rosnace";
        } else {
            dataName = "malejace";
        }

        for (int n : {100, 1000, 5000, 10000}) {
            for (int pivotType = 0; pivotType <= 1; pivotType++) {
                vector<int> data = createData(n, type);

                if (pivotType == 0) {
                    randomPivot = false;
                } else {
                    randomPivot = true;
                }

                resetStats();
                quickSort(data, 0, n - 1);

                const char* pivotName;
                if (pivotType == 0) {
                    pivotName = "ostatni";
                } else {
                    pivotName = "losowy";
                }

                cout << left << setw(12) << dataName
                     << " " << right << setw(8) << n
                     << " " << left << setw(14) << pivotName
                     << " " << right << setw(16) << comparisons
                     << " " << setw(14) << swapsCount
                     << setw(18) << maxDepth << "\n";
            }
        }
    }
}

int main() {
    srand(1);

    vector<int> data = {8, 3, 6, 2, 7, 1, 5, 4};
    int n = data.size();

    quickSort(data, 0, n - 1);

    cout << "Quick Sort: ";
    for (int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
    cout << "\n";

    printMeasurements();

    return 0;
}
