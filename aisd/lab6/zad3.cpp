#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

long long insertionComparisons = 0;
long long mergeComparisons = 0;
long long quickComparisons = 0;

void insertionSort(vector<int>& data) {
    for (size_t i = 1; i < data.size(); i++) {
        int value = data[i];
        size_t j = i;
        while (j > 0) {
            insertionComparisons++;
            if (data[j - 1] <= value) {
                break;
            }
            data[j] = data[j - 1];
            j--;
        }
        data[j] = value;
    }
}

void merge(vector<int>& data, int left, int middle, int right) {
    vector<int> leftPart(data.begin() + left, data.begin() + middle + 1);
    vector<int> rightPart(data.begin() + middle + 1, data.begin() + right + 1);
    size_t i = 0;
    size_t j = 0;
    int position = left;

    while (i < leftPart.size() && j < rightPart.size()) {
        mergeComparisons++;
        if (leftPart[i] <= rightPart[j]) {
            data[position++] = leftPart[i++];
        } else {
            data[position++] = rightPart[j++];
        }
    }
    while (i < leftPart.size()) data[position++] = leftPart[i++];
    while (j < rightPart.size()) data[position++] = rightPart[j++];
}

void mergeSort(vector<int>& data, int left, int right) {
    if (left >= right) return;
    int middle = left + (right - left) / 2;
    mergeSort(data, left, middle);
    mergeSort(data, middle + 1, right);
    merge(data, left, middle, right);
}

int partition(vector<int>& data, int left, int right) {
    int pivot = data[right];
    int smaller = left - 1;
    for (int i = left; i < right; i++) {
        quickComparisons++;
        if (data[i] < pivot) {
            smaller++;
            swap(data[smaller], data[i]);
        }
    }
    swap(data[smaller + 1], data[right]);
    return smaller + 1;
}

void quickSort(vector<int>& data, int left, int right) {
    if (left < right) {
        int pivot = partition(data, left, right);
        quickSort(data, left, pivot - 1);
        quickSort(data, pivot + 1, right);
    }
}

double milliseconds(long long nanoseconds) {
    return nanoseconds / 1000000.0;
}

void resetCounters() {
    insertionComparisons = mergeComparisons = quickComparisons = 0;
}

vector<int> randomData(int n, mt19937& random) {
    vector<int> data(n);
    for (int i = 0; i < n; i++) data[i] = random() % (n * 10 + 1);
    return data;
}

int main() {
    mt19937 random(1);

    cout << "Eksperyment 1 - rozmiar danych\n";
    cout << left << setw(8) << "n"
         << setw(26) << "Insertion Sort"
         << setw(26) << "Merge Sort"
         << setw(26) << "Quick Sort" << "\n";

    for (int n : {100, 1000, 5000, 10000, 50000}) {
        vector<int> original = randomData(n, random);
        vector<int> insertionData = original;
        vector<int> mergeData = original;
        vector<int> quickData = original;
        resetCounters();

        auto start = chrono::steady_clock::now();
        insertionSort(insertionData);
        auto end = chrono::steady_clock::now();
        long long insertionTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        long long insertionCount = insertionComparisons;

        start = chrono::steady_clock::now();
        mergeSort(mergeData, 0, n - 1);
        end = chrono::steady_clock::now();
        long long mergeTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        long long mergeCount = mergeComparisons;

        start = chrono::steady_clock::now();
        quickSort(quickData, 0, n - 1);
        end = chrono::steady_clock::now();
        long long quickTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        long long quickCount = quickComparisons;

        cout << left << setw(8) << n
             << setw(26) << (to_string(static_cast<long long>(milliseconds(insertionTime) * 1000) / 1000.0) + " ms, " + to_string(insertionCount) + " porownan")
             << setw(26) << (to_string(static_cast<long long>(milliseconds(mergeTime) * 1000) / 1000.0) + " ms, " + to_string(mergeCount) + " porownan")
             << setw(26) << (to_string(static_cast<long long>(milliseconds(quickTime) * 1000) / 1000.0) + " ms, " + to_string(quickCount) + " porownan")
             << "\n";
    }

    const int n = 10000;
    cout << "\nEksperyment 2 - charakter danych, n = " << n << "\n";
    cout << left << setw(14) << "Dane"
         << setw(28) << "Insertion Sort"
         << setw(28) << "Merge Sort"
         << setw(28) << "Quick Sort" << "\n";

    vector<pair<string, vector<int>>> datasets;
    datasets.push_back({"losowe", randomData(n, random)});

    vector<int> increasing(n);
    for (int i = 0; i < n; i++) increasing[i] = i;
    datasets.push_back({"rosnace", increasing});

    vector<int> decreasing(n);
    for (int i = 0; i < n; i++) decreasing[i] = n - i;
    datasets.push_back({"malejace", decreasing});

    vector<int> almostSorted = increasing;
    for (int i = 0; i < n / 100; i++) {
        int a = (i * 97) % n;
        int b = (i * 97 + 1) % n;
        swap(almostSorted[a], almostSorted[b]);
    }
    datasets.push_back({"prawie uporzadkowane", almostSorted});

    for (const auto& dataset : datasets) {
        vector<int> insertionData = dataset.second;
        vector<int> mergeData = dataset.second;
        vector<int> quickData = dataset.second;
        resetCounters();

        auto start = chrono::steady_clock::now();
        insertionSort(insertionData);
        auto end = chrono::steady_clock::now();
        long long insertionTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        long long insertionCount = insertionComparisons;

        start = chrono::steady_clock::now();
        mergeSort(mergeData, 0, n - 1);
        end = chrono::steady_clock::now();
        long long mergeTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        long long mergeCount = mergeComparisons;

        start = chrono::steady_clock::now();
        quickSort(quickData, 0, n - 1);
        end = chrono::steady_clock::now();
        long long quickTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        long long quickCount = quickComparisons;

        cout << left << setw(14) << dataset.first
             << setw(28) << (to_string(static_cast<long long>(milliseconds(insertionTime) * 1000) / 1000.0) + " ms, " + to_string(insertionCount) + " porownan")
             << setw(28) << (to_string(static_cast<long long>(milliseconds(mergeTime) * 1000) / 1000.0) + " ms, " + to_string(mergeCount) + " porownan")
             << setw(28) << (to_string(static_cast<long long>(milliseconds(quickTime) * 1000) / 1000.0) + " ms, " + to_string(quickCount) + " porownan")
             << "\n";
    }

    return 0;
}
