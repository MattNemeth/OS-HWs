#include <stack>
#include <list>
#include <queue>
#include <string>
#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int Q_count = 0;
int Qt_count = 0;
int M_count = 0;
int Mt_count = 0;

void ArrayPrint(int array[], int n) {
  int i;
  for (i = 0; i < n; i++)
    printf("%d ", array[i]);
  printf("\n");
}

void InsertionSort(int array[], int start, int end) {
  int i, key, j;
  for (i = start; i <= end; i++) {
    key = array[i];
    //cout << endl << key << endl;
    j = i - 1;

    while (j >= 0 && array[j] > key) {
      array[j + 1] = array[j];
      j = j - 1;
      Qt_count++;
      Mt_count++;
    }
    array[j + 1] = key;
  }

  //ArrayPrint(array, n);
}

void QuickSortSwap(int * x1, int * x2) {
  int t = * x1;
  * x1 = * x2;
  * x2 = t;
}

int QuickSortPartition(int array[], int low, int high) {
  int pivot = array[high]; // pivot
  int i = (low - 1); // Index of smaller element

  for (int j = low; j <= high - 1; j++) {
    // If current element is smaller than or
    // equal to pivot
    Q_count++;
    if (array[j] <= pivot) {
      i++; // increment index of smaller element
      QuickSortSwap( & array[i], & array[j]);
    }
  }
  QuickSortSwap( & array[i + 1], & array[high]);
  return (i + 1);
}

void QuickSort(int array[], int low, int high, int t) {
  if ((high - low + 1) <= t) {
    Q_count++;
    InsertionSort(array, low, high);
  } else if (low < high) {
    /* pi is partitioning index, arr[p] is now
      at right place */
    Q_count++;
    int pi = QuickSortPartition(array, low, high);

    // Separately sort elements before
    // partition and after partition
    QuickSort(array, low, pi - 1, t);
    QuickSort(array, pi + 1, high, t);
  }
}

void MergeSortMerge(int array[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int * L = new int[n1];
  int * R = new int[n2];

  for (i = 0; i < n1; i++)
    L[i] = array[l + i];
  for (j = 0; j < n2; j++)
    R[j] = array[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    M_count++;
    if (L[i] <= R[j]) {
      array[k] = L[i];
      i++;
    } else {
      array[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    array[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    array[k] = R[j];
    j++;
    k++;
  }

  delete L, R;
}

void MergeSort(int array[], int l, int r, int t) {
  if (l < r) {
    int m = (l + (r - 1)) / 2;
    if ((r - l) <= t) {
      //std::cout << "Using Insertion " << l << "," << r << std::endl;
      InsertionSort(array, l, r);
    } else if (l < r) {
      MergeSort(array, l, m, t);
      MergeSort(array, m, r, t);
      MergeSortMerge(array, l, m, r);
    }
  }
}

int main() {
  int size = 1;
  int Thres = 1;

  int Qt_ct = 0;
  int Mt_ct = 0;
  int Q_ct = 0;
  int M_ct = 0;

  char RM_sel;
  char Sort_sel;
  char Comp_sel;
  int * Unsorted;
  int * Quick;
  int * Merge;
  
	cout << "This program will allow you, the user, to compare two sorting algorithms: (MergeSort and QuickSort)." << endl
    << "You will be asked for a few inputs. The first will be the size of the array." << endl
    << "You will then be asked for a threshold value which determines the point at which insertionsort is used." << endl
    << "If the array is larger then 15          >> the array will be automatically created with random numbers" << endl
    << "If the size is less than or equal to 15 >> you can either enter in your own values manually, or select to have the list randomized." << endl
    << "If the size is less than or equal to 15 >> you may also select to display both the unsorted and sorted lists. from the two algorithms" << endl << endl;

  while (size > 0) {

    Q_count = 0;
    M_count = 0;
	

    cout << "Enter list size: ";
    cin >> size;

    if (size <= 15 && size > 0) {
      Unsorted = new int[size];
      Quick = new int[size];
      Merge = new int[size];

      cout << "Enter the threshold size: ";
      cin >> Thres;

      cout << "Are you going to manually enter the list? (Y/N)" << endl;
      cin >> RM_sel;

      if (std::toupper(RM_sel) == 'N') {
        for (int i = 0; i < size; i++) {
          Unsorted[i] = rand() % (size * 10);
          Quick[i] = Unsorted[i];
          Merge[i] = Unsorted[i];
        }

      } else {
        Unsorted = new int[size];
        Quick = new int[size];
        Merge = new int[size];
        cout << "Enter your list one number at a time." << endl;

        for (int k = 0; k < size; k++) {
          cout << "Enter number " << k + 1 << ": ";
          cin >> Unsorted[k];
          Quick[k] = Unsorted[k];
          Merge[k] = Unsorted[k];
        }

      }

      Qt_count = 0;
      Q_count = 0;

      QuickSort(Quick, 0, size - 1, Thres);
      Qt_ct = Qt_count;
      Q_ct = Q_count;

      Mt_count = 0;
      M_count = 0;

      MergeSort(Merge, 0, size - 1, Thres);
      Mt_ct = Mt_count;
      M_ct = M_count;

      cout << "Do you want to display the number of comparisons for each sort? (Y/N)" << endl;
      cin >> Comp_sel;

      cout << "Do you want to display the sorted lists? (Y/N)" << endl;
      cin >> Sort_sel;

      if (std::toupper(Sort_sel) == 'Y' && std::toupper(Comp_sel) == 'Y') {
        std::cout << "Unsorted: " << endl;
        ArrayPrint(Unsorted, size);
        std::cout << "Quick Comparisons: " << Q_ct << "   Threshold Comparisons: " << Qt_ct << endl;
        ArrayPrint(Quick, size);
        std::cout << "Merge Comparisons: " << M_ct << "   Threshold Comparisons: " << Mt_ct << endl;
        ArrayPrint(Merge, size);

      } else if (std::toupper(Sort_sel) == 'Y' && std::toupper(Comp_sel) == 'N') {
        std::cout << "Unsorted: " << endl;
        ArrayPrint(Unsorted, size);
        std::cout << "Quick: " << endl;
        ArrayPrint(Quick, size);
        std::cout << "Merge: " << endl;
        ArrayPrint(Merge, size);

      } else if (std::toupper(Sort_sel) == 'N' && std::toupper(Comp_sel) == 'Y') {
        std::cout << "Quick Comparisons: " << Q_ct << "   Threshold Comparisons: " << Qt_ct << endl;
        std::cout << "Merge Comparisons: " << M_ct << "   Threshold Comparisons: " << Mt_ct << endl;

      } else {

      }

    } else if (size > 15) {
      //merge or quick or both
      Unsorted = new int[size];
      Quick = new int[size];
      Merge = new int[size];

      cout << "Enter the threshold size: ";
      cin >> Thres;

      for (int i = 0; i < size; i++) {
        Unsorted[i] = rand() % (size * 10);
        Quick[i] = Unsorted[i];
        Merge[i] = Unsorted[i];
      }

      Qt_count = 0;
      Q_count = 0;

      QuickSort(Quick, 0, size - 1, Thres);
      Qt_ct = Qt_count;
      Q_ct = Q_count;

      Mt_count = 0;
      M_count = 0;

      MergeSort(Merge, 0, size - 1, Thres);
      Mt_ct = Mt_count;
      M_ct = M_count;

      cout << "Do you want to display the number of comparisons for each sort? (Y/N)" << endl;
      cin >> Comp_sel;

      if (std::toupper(Comp_sel) == 'Y') {
        std::cout << "Quick Comparisons: " << Q_ct << "   Threshold Comparisons: " << Qt_ct << endl;
        std::cout << "Merge Comparisons: " << M_ct << "   Threshold Comparisons: " << Mt_ct << endl;

      } else {

      }

    } else {
      cout << "Program has ended due to improper array size." << endl;
    }

  } // end of while

  return 0;
}