#include "SortAlgo.h"

void bubblesort (vector<int> &a, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (a[j] > a[j+1])
                swap(a[j], a[j+1]);
}

void insertionsort (vector<int> &a, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && key <= a[j])
        {
            a[j+1] = a[j];
            j--; 
        }
        a[j+1] = key;
    }
}

void selectionsort (vector<int> &a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int min_idx = i;
        for (int j = i; j < n; ++j)
        {
            if (a[i] > a[j])
                min_idx = j;
        }
        if (min_idx != i)
            swap (a[i], a[min_idx]);
    }
}

void merge (vector<int> &a, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int [n1];
    int* R = new int [n2];

    for (int i = 0; i < n1; ++i)
        L[i] = a[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = a[mid + j + 1];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        a[k] = R[j];
        k++;
        j++;
    }
    delete[] L;
    delete[] R;
}

void mergesort (vector<int> &a, int left, int right)
{
    if (left >= right)
        return;

    int mid = (left + right)/2;
    mergesort(a, left, mid);
    mergesort(a, mid+1, right);
    merge(a, left, mid, right);
}

// Ascending order //
void sift (vector <int> &a, int left, int right)
{
    int i = left;
    int j = i*2 + 1;
    int x = a[i];
    while (j <= right)
    {
        if (j < right)
            if (a[j] < a[j+1])
                j++;
        
        if (x >= a[j]) // > for ascending order | < for descending order 
            break;
        
        a[i] = a[j];
        i = j;
        j = i*2 +1;
    }
    a[i] = x;
}

void heapsort (vector<int> &a, int n)
{
    int left = n/2;
    while (left >= 0)
    {
        sift(a, left, n-1);
        left--;
    }
    int right = n-1;
    while (right > 0)
    {
        swap(a[0], a[right]);
        right--;
        sift(a, 0, right);
    }
}
// End of function

int partition (vector<int> &a, int left, int right)
{
    int i = left;
    int j = right + 1;
    int x = a[left];
    do
    {  
        do i++; while(a[i] < x);
        do j--; while(a[j] > x);
        swap(a[i], a[j]);
    } while (i < j);
    swap(a[i], a[j]);
    swap(a[j], a[left]);
    return j;
}

void quicksort (vector<int> &a, int left, int right)
{
    if (left >= right)
        return;

    int p = partition(a, left, right);
    quicksort (a, left, p-1);
    quicksort (a, p+1, right);
}

void countingsort (vector<int> &a, int n)
{
    int* b = new int [n];
    int max, min, i;
    max = a[0];
    min = a[0];
    for (int i = 0; i < n; ++i)
    {
        if (a[i] > max)
            max = a[i];
        if (a[i] < min)
            min = a[i];
    }
    int k = max - min + 1;
    int* count = new int[k];
    for (int i = 0; i < k; ++i)
        count[i] = 0;

    for (int i = 0; i < n; ++i)
        count[a[i] - min]++;
    
    for (int i = 1; i <= k; ++i)
        count[i] += count[i-1];

    for (int i = 0; i < n; ++i)
    {
        b[count[a[i] - min]-1] = a[i];
        count[a[i] - min]--;
    }

    for (int i = 0; i < n; ++i)
        a[i] = b[i];
        
    delete[] b;
    delete[] count;
}

int getmax (vector<int> &a, int n)
{
    int max_idx = 0;
    for (int i = 0; i < n; ++i)
        if (a[max_idx] < a[i])
            max_idx = i;

    return max_idx;
}

void count (vector<int> &a, int n, int exp)
{
    int *b = new int[n];
    int i, count[10] = {0};

    for (int i = 0; i < n; ++i)
        count[(a[i]/exp) % 10]++;

    for (int i = 0; i < 10; ++i)
        count[i] += count[i-1];

    for (int i = 0; i < n; ++i)
    {
        b[count[(a[i]/exp) % 10]-1] = a[i];
        count[(a[i]/exp) % 10]--;
    }

    for (int i = 0; i < n; ++i)
        a[i] = b[i];

    delete[] b;
}

void radixsort (vector<int> &a, int n)
{
    int i = getmax(a, n);
    for (int exp = 1; a[i]/exp > 0; exp*=10)
    {
        count(a, n, exp);
    }
}