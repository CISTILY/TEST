#include "SortAlgo.h"

using namespace std;

void printArray (vector<int> a, int n)
{
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
}

int main ()
{
    srand(time(NULL));
    vector<int> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        a.push_back(rand()%100);

    printArray(a, n);
    countingsort(a, n);
    printArray(a, n);
    return 0;
}