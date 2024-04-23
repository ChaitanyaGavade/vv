#include<bits/stdc++.h>

using namespace std;

// Sequential Bubble Sort
void s_bubble(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
        for (int j = first; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

// Parallel Bubble sort using shared directive and user-defined number of threads
void p_bubble(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
        // Starting the parallel thread for loop
        // Number of threads are 2 due to the number of CPU cores
#pragma omp parallel for shared(a, first) num_threads(2)
        for (int j = first; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

string timeCalculator(function<void()> sort_fn) {
    auto start = chrono::high_resolution_clock::now();
    sort_fn();
    auto stop = chrono::high_resolution_clock::now();
    auto result = stop - start;
    auto duration = chrono::duration_cast<chrono::milliseconds>(result);
    return to_string(duration.count());
}

int main() {
    int *a, n;
    cout << "Specify array length." << endl;
    cin >> n;
    a = new int[n];
    // Creating array of random numbers for testing purpose
    for (int i = 0; i < n; i++) {
        a[i] = rand() % n;
    }
    cout << "Generated random array of length " << n << endl << endl;

    // Calling the function and calculating the time for sequential sort
   cout << "Sequential Bubble sort: " << timeCalculator([&] { s_bubble(a, n); }) << "ms" << endl;

    // Calling the function and calculating the time for parallel sort
    // Setting the number of threads before executing parallel programming
   // omp_set_num_threads(2);
   cout << "Parallel (2) Bubble sort: " << timeCalculator([&] { p_bubble(a, n); }) << "ms" << endl;

    return 0;
}

