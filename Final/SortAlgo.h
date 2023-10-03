#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <time.h>

using namespace std;

void bubblesort (vector<int> &, int);
void insertionsort (vector<int> &, int);
void selectionsort (vector<int> &, int);

void merge (vector<int> &, int, int, int);
void mergesort (vector<int> &, int, int);
void sift (vector <int> &, int, int);
void heapsort (vector<int> &, int);
int partition (vector<int> &, int, int);
void quicksort (vector<int> &, int, int);

void countingsort (vector<int> &, int);
int getmax (vector<int> &, int);
void count (vector<int> &, int, int);
void radixsort (vector<int> &, int);