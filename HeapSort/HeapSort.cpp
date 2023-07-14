#include <iostream>

using namespace std;

void sift(int *a, int left, int right) {
    int i = left, j = 2 * i;
    int x = a[i];
    while (j <= right) {
        if (j < right)
            if (a[j] > a[j + 1]) 
                j++;
        if (x <= a[j]) 
            break;
        a[i] = a[j];
        i = j; j = 2 * i;
    }
    a[i] = x;
}

void swap (int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void HeapSort (int *a, int n)
{
    int right = n;
    while (right > 0)
    {
        swap (a[1], a[right]);
        right--;
        sift (a, 1, right);
    }
}

int main ()
{
    int* a = new int [10];
    for (int i = 1; i <= 5; ++i)
    {
        a[i] = 3*i;
        a[2*i+1] = 4*i+2;
        a[2*i] = 2*i;
    }

    for (int i = 1; i <= 10; ++i)
        cout << a[i] << " ";
    cout << endl;
    HeapSort(a, 10);
    for (int i = 1; i <= 10; ++i)
        cout << a[i] << " ";
    delete[] a;
    return 0;
}