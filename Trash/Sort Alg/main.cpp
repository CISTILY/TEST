#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

void swap (int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort (vector<int> &a)
{
    for (int i = 1; i < a.size(); ++i)
        for (int j = a.size()-1; j > i; --j)
            if (a[j] < a[j-1])
                swap(a[j], a[j-1]);
}

void insertionSort (vector <int> &a)
{
    int key;
    for (int i = 1; i < a.size(); ++i)
    {
        key = a[i];
        int j = i - 1;
        while (j > 0 && a[j] > key)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

void selectionSort (vector <int> &a)
{
    int min_val, min_idx;
    for (int i = 0; i < a.size(); ++i)
    {
        min_val = a[i];
        min_idx = i;
        for (int j = i+1; j < a.size(); ++j)
        {
            if (a[j] < min_val)
            {
                min_val = a[j];
                min_idx = j;
            }
        }
        if (min_idx != i)
            swap(a[i], a[min_idx]);
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
        k++;
        i++;
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

void mergeSort (vector <int> &a, int left, int right)
{
    if (left >= right)
        return;

    int mid = (left + right)/2;
    mergeSort (a, left, mid);
    mergeSort (a, mid+1, right);
    merge(a, left, mid, right);
}

void sift (vector <int> &a, int left, int right)
{
    int i = left, j = 2*i, x = a[i];
    while (j <= right)
    {
        if (j < right)
            if (a[j] > a[j+1])
                j++;
        if (x <= a[j])
            break;
        
        a[i] = a[j];
        i = j; 
        j = 2*i;
    }
    a[i] = x;
}

void contructHeap (vector<int>&a)
{
    int left = a.size()/2;
    while (left > 0)
    {
        sift(a, left, a.size()-1);
        left--;
    }
}

void heapSort (vector<int>&a)
{
    int right = a.size();
    while (right > 0)
    {
        swap(a[0], a[right]);
        right--;
        sift(a, 0, right);
    }
}

int partition (vector<int> &a, int left, int right)
{
    int i = left, j = right+1, p = a[left];
    do
    {
        do i++; while (a[i] < p);
        do j--; while (a[j] > p);
        swap(a[i], a[j]);
    } while (i < j);
    swap(a[i], a[j]);
    swap(a[left], a[j]);
    return j;
}

void quickSort (vector<int> &a, int left, int right)
{
    if (left >= right)
        return;

    int p = partition(a, left, right);
    quickSort (a, left, p-1);
    quickSort (a, p+1, right);
}

void countingSort (vector<int> &a)
{
    int* output = new int[a.size()];
    int min = a[0] , max = a[0];

    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i] > max)
            max = a[i];
        if (a[i] < min)
            min = a[i];
    }

    int k = max-min+1;
    int* count = new int [k];

    for (int i = 0; i < k; ++i)
        count[i] = 0;

    for (int i = 0; i < a.size(); ++i)
        count[a[i]-min]++;

    for (int i = 1; i < k; ++i)
    {
        count[i] += count[i-1];
    }

    for (int i = 0; i < a.size(); ++i)
    {
        output[count[a[i]-min]-1] = a[i];
        count[a[i]-min]--;
    }
    for (int i = 0; i < a.size(); ++i)
        a[i] = output[i];
}

int findLargest (vector <int> a)
{
    int max = -999, max_idx;
    for (int i = 0; i < a.size(); ++i)
        if (a[i] > max)
        {
            max = a[i];
            max_idx = i;
        }
    return max_idx;
}

int findDigit (int a)
{
    int count;
    while (a != 0)
    {
        a /= 10;
        count++;
    }
    return count;
}

int digit (int a, int k)
{
    while (k != 0)
    {
        a /= 10;
        k--;
    }
    return a % 10;
}

void sort (vector <int> &a, int k)
{
    int*b = new int [a.size()];
    int f[10] = {0};
    for (int i = 0; i < a.size(); ++i) f[digit(a[i], k)]++;
    for (int i = 1; i <= 9; ++i) f[i] += f[i-1];
    for (int i = a.size()-1; i >= 0; i--) 
    {
        int j = digit(a[i], k);
        b[f[j]-1] = a[i];
        f[j]--;
    }
    for (int i = 0; i < a.size(); ++i)
        a[i] = b[i];
}

void printArray (vector<int> a)
{
    for (int i = 0; i < a.size(); ++i)
        cout << a[i] << " ";
    cout << endl;
}

void LSDradixSort (vector <int> &a, int d)
{
    for (int i = 0; i < d; ++i)
    {
        sort(a, i);
        printArray(a);
    }
        
}

int main ()
{
    vector<int> a;
    ifstream fIn;
    fIn.open("data.txt");
    int temp;
    while (fIn >> temp)
    {
        a.push_back(temp);
        if (fIn.eof())
            break;
    }
    fIn.close();

    printArray(a);
    //contructHeap(a);
    // printArray(a);
    //heapSort(a);
    // printArray(a);
    //bubbleSort(a);
    //insertionSort(a);
    //selectionSort(a);
    //mergeSort(a, 0, a.size()-1);
    //quickSort(a, 0, a.size()-1);
    //countingSort(a);
    int max_idx = findLargest(a);
    int d = findDigit(a[max_idx]);
    LSDradixSort(a, d);
    printArray(a);
    return 0;
}