#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

// Generate random integers between 0-99
void generateRandomArray(int arr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

// Print array elements
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;
}

// Quick Sort implementation
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort implementation
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int* L = new int[n1];
    int* R = new int[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
        
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Binary Search implementation
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Exponential Search implementation
int exponentialSearch(int arr[], int size, int target) {
    if (arr[0] == target) return 0;
    
    int i = 1;
    while (i < size && arr[i] <= target)
        i *= 2;
    
    int left = i / 2;
    int right = min(i, size - 1);
    return binarySearch(arr + left, right - left + 1, target) + left;
}

int main() {
    int n, searchNum, sortChoice, searchChoice;
    
    // Get array size
    cout << "Enter number of random integers to generate: ";
    cin >> n;
    
    int* arr = new int[n];
    
    // Generate and display array
    generateRandomArray(arr, n);
    cout << "\nGenerated Array:\n";
    printArray(arr, n);
    
   // Sorting selection
cout << "Choose Sorting Algorithm:\n";
cout << "1. Quick Sort\n2. Merge Sort\nEnter choice: ";
cin >> sortChoice;

// Sort with timing in nanoseconds
auto sortStart = high_resolution_clock::now();
switch(sortChoice) {
    case 1: 
        quickSort(arr, 0, n - 1);
        break;
    case 2:
        mergeSort(arr, 0, n - 1);
        break;
    default:
        cout << "Invalid choice! Using Merge Sort by default\n";
        mergeSort(arr, 0, n - 1);
}
auto sortEnd = high_resolution_clock::now();
auto sortDuration = duration_cast<nanoseconds>(sortEnd - sortStart);

// Display sorted array
cout << "\nSorted Array:\n";
printArray(arr, n);

// Get search number
cout << "Enter the number to search: ";
cin >> searchNum;

// Search algorithm selection
cout << "Choose Search Algorithm:\n";
cout << "1. Binary Search\n2. Exponential Search\nEnter choice: ";
cin >> searchChoice;

// Search with timing in nanoseconds
auto searchStart = high_resolution_clock::now();
int index = -1;
switch(searchChoice) {
    case 1:
        index = binarySearch(arr, n, searchNum);
        break;
    case 2:
        index = exponentialSearch(arr, n, searchNum);
        break;
    default:
        cout << "Invalid choice! Using Binary Search by default\n";
        index = binarySearch(arr, n, searchNum);
}
auto searchEnd = high_resolution_clock::now();
auto searchDuration = duration_cast<nanoseconds>(searchEnd - searchStart);

// Display search results
if (index != -1) {
    cout << "Element found at index: " << index << endl;
} else {
    cout << "Element not found!" << endl;
}

// Display execution times in nanoseconds
cout << "\nExecution Times:";
cout << "\nSorting (" << (sortChoice == 1 ? "Quick Sort" : "Merge Sort") 
     << "): " << sortDuration.count() << " nanoseconds";
cout << "\nSearching (" << (searchChoice == 1 ? "Binary Search" : "Exponential Search")
     << "): " << searchDuration.count() << " nanoseconds" << endl;


    delete[] arr;
    return 0;
}