#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void merge(vector<int>& data, int left, int middle, int right) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    vector<int> leftPart(leftSize);
    vector<int> rightPart(rightSize);

    for (int i = 0; i < leftSize; i++) {
        leftPart[i] = data[left + i];
    }

    for (int i = 0; i < rightSize; i++) {
        rightPart[i] = data[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int position = left;

    while (i < leftSize && j < rightSize) {
        if (leftPart[i] <= rightPart[j]) {
            data[position] = leftPart[i];
            i++;
        } else {
            data[position] = rightPart[j];
            j++;
        }
        position++;
    }

    while (i < leftSize) {
        data[position] = leftPart[i];
        i++;
        position++;
    }

    while (j < rightSize) {
        data[position] = rightPart[j];
        j++;
        position++;
    }
}

void mergeSort(vector<int>& data, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = (left + right) / 2;
    mergeSort(data, left, middle);
    mergeSort(data, middle + 1, right);
    merge(data, left, middle, right);
}

int partition(vector<int>& data, int left, int right) {
    int pivot = data[right];
    int smallerPosition = left - 1;

    for (int i = left; i < right; i++) {
        if (data[i] < pivot) {
            smallerPosition++;
            swap(data[smallerPosition], data[i]);
        }
    }

    swap(data[smallerPosition + 1], data[right]);
    return smallerPosition + 1;
}

int quickSelect(vector<int>& data, int left, int right, int k) {
    int dataSize = data.size();

    if (k < 1 || k > dataSize) {
        cout << "Niepoprawne k\n";
        return -1;
    }

    if (left < 0 || right >= dataSize || left > right) {
        cout << "Niepoprawny zakres tablicy\n";
        return -1;
    }

    int wantedPosition = k - 1;

    while (left <= right) {
        int pivotPosition = partition(data, left, right);

        if (pivotPosition == wantedPosition) {
            return data[pivotPosition];
        }

        if (pivotPosition > wantedPosition) {
            right = pivotPosition - 1;
        } else {
            left = pivotPosition + 1;
        }
    }

    return -1;
}

int main() {
    vector<int> data = {8, 3, 1, 7, 4, 9, 2};
    int k = 7;
    int n = data.size();

    vector<int> sortedData = data;
    mergeSort(sortedData, 0, n - 1);

    cout << "Merge Sort: " << sortedData[k - 1] << "\n";

    vector<int> selectedData = data;
    int result = quickSelect(selectedData, 0, n - 1, k);

    if (result != -1) {
        cout << "Quick Select: " << result << "\n";
    }

    return 0;
}
