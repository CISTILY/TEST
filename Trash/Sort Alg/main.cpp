#include <iostream>
#include <fstream>

using namespace std;

void SelectionSort(int* a, int n) 
// find the smallest element and swap it with the left-end element (ascending order)
{ 
    int min_idx, min_val;
    for (int i = 0; i < n - 1; i++) {
        min_idx = i;
        min_val = a[i];
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) { 
                min_idx = j; // find the minimum element in the unsorted array
                min_val = a[j];
            }
        }
        swap(a[i], a[min_idx]);// swap the found element with the left-end element
    }
}

void InsertionSort(int* a, int n) { 
    for (int i = 1; i < n; i++) {
        int key = a[i]; // take the value of array member to a temporary variable
        int j = i - 1;
        // Move elements of arr[0..i-1],
        // that are smaller than tmp,
        // to one position ahead of their
        // current position
        while (j >= 0 && key < a[j]) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key; // insert the element into the right position
    }
}

void BubbleSort(int* a, int n) // bring the bigger element forward the right-end element
{ 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) { 
                swap(a[j], a[j+1]); // if the left element is bigger, swap them
            }
        }
    }
}

void ShakerSort(int* a, int n) // an improvement of Bubble Sort
{ 
    int left = 0, right = n - 1, k = 0;
     while (left < right) // move 2 elements at 1 loop
    {
        for (int i = right; i > left; i--) 
        {
            if (a[i - 1] > a[i]) 
            {
                swap(a[i], a[i - 1]); // move the smaller element toward the left-end
                k = i;
            }
        }
        left = k;
        for (int i = left; i < right; i++) 
        {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]); // move the bigger element toward the right-end
                k = i;
            }
        }
        right = k;
    }
}

void ShellSort(int* a, int n)
{
	int gap, i, j, temp;
	for (gap = n / 2; gap > 0; gap /= 2) // start with a large gap and reduce it
	{
		for (i = gap; i < n; i++) // perform insertion sort for the current gap
		{
			temp = a[i];
			for (j = i; j >= gap && a[j - gap] > temp; j -= gap) // shift elements that are greater than temp and are in the same gap
				a[j] = a[j - gap];
			a[j] = temp; // place the current element (temp) in its correct position
		}
	}
}

void Sift(int* a, int left, int right) // to satisfy the max-heap property: a[i] >= a[2 * i + 1] and a[i] >= a[2 * i + 2]
{
	int i, j, x;
	i = left;
	j = 2 * i + 1; // initialize 'j' to the left child of 'i'
	x = a[i]; // store the value of the element to be sifted
	while (j <= right)
	{
		if (j < right)
			if (a[j] < a[j + 1]) // if there are two children, choose the large one
				j++;
		if (x >= a[j]) // if the current element 'x' is greater than 'a[j]', then it satisfies the max-heap property
			break;
		a[i] = a[j]; // otherwise move the larger child 'a[j]' up in the heap and continue sifting
		i = j;
		j = 2 * i + 1; // update 'j' to the left child of the new 'i'
	}
	a[i] = x; // placce the element 'x' in its correct position in the max-heap
}

void HeapSort(int* a, int n)
{
	int left = n / 2; // initialize 'left' to the parent of the last element
	while (left >= 0) // convert the input array into a max-heap
	{
		Sift(a, left, n - 1); // call sift to adjust the heap
		left--; // move to the previous parent
	}
	int right = n - 1; // 'right' is the last element int the array
	while (right > 0) // extract elements from the max-heap and build the sorted array
	{
		swap(a[0], a[right]); // swap the largest element with the right-end element
		right--; // exclude the last element from further consideration
		Sift(a, 0, right); // restore the max-heap property for the remaining elements
	}
}

void Merge(int* a, int left, int mid, int right) // merge 2 sorted subarrays into one array
{
	int i, j, k = left;
	int n1 = mid - left + 1; // size of the left subarray
	int n2 = right - mid; // size of the right subarray
	int* L = new int[n1]; // temporary araray to hold the left subarray
	int* R = new int[n2]; // temporary araray to hold the right subarray

	// copy data to the temporary arrays
	for (i = 0; i < n1; i++)
		L[i] = a[i + left];
	for (i = 0; i < n2; i++)
		R[i] = a[i + 1 + mid];

	i = 0; // index of the left subarray
	j = 0; // index of the right subarray
	while (i < n1 && j < n2) // merge the temporary arrays back into 'a'
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
	while (i < n1) // copy the remaining elements of the left subarray (if any)
	{
		a[k] = L[i];
		k++; i++;
	}
	while (j < n2) // copy the remaining elements of the right subarray (if any)
	{
		a[k] = R[j];
		k++; j++;
	}

	// free the dynamically allocated temporary arrays
	delete[] L;
	delete[] R;
}

void MergeSort(int* a, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2; // calculate the middle index
		MergeSort(a, left, mid); // spliting left array and sort from the innest
		MergeSort(a, mid + 1, right); // spliting right array and sort from the innest
		Merge(a, left, mid, right); // merge the two sorted subarrays
	}
}

int Partition(int a[], int low, int high)
{
	int i, j, p;
	i = low;
	j = high + 1;
	p = a[low]; // set a pivot (left-end element) for comparison
	do
	{
		do i++; while (a[i] < p); // find the position which a[left..i] < p < a[j..right]
		do j--; while (a[j] > p);
		swap(a[i], a[j]); // swap the elements at positon i and j if i < j
	} while (i < j);
	swap(a[i], a[j]); // undo the last swap between a[i] and a[j]
	swap(a[j], a[low]); // swap the pivot to its right position
	return j; // return the pivot position
}   

void QuickSort(int* a, int left, int right)
{
	int p;
	if (left < right)
	{
		p = Partition(a, left, right); // get the new position of the pivot
		QuickSort(a, left, p - 1); // recursively sort the left subarray
		QuickSort(a, p + 1, right); // recursively sort the right subarray
	}
}

void CountingSort(int* a, int n)
{
	int* b = new int[n]; // temporary array to store the sorted elements
	int max, min, i;
	max = a[0];
	min = a[0];
	for (i = 1; i < n; i++) // find the maximum and minimum values in the array
	{
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}

	int k = max - min + 1; // calculate the range of values in the array
	int* count = new int[k]; // create a new array of the value range to count
	for (i = 0; i < k; i++)
		count[i] = 0; // set all count element value to 0

	for (i = 0; i < n; i++)
		count[a[i] - min]++; // count the appearance of each element

	for (i = 1; i < k; i++)
		count[i] += count[i - 1]; // find the last position of each element

	for (i = 0; i < n; i++)
	{
		b[count[a[i] - min] - 1] = a[i]; // sorting the array in a new array
		count[a[i] - min]--; // update new position
	}

	for (i = 0; i < n; i++)
		a[i] = b[i]; // copy the sorted array to the original one

	delete[] b; // free the dynamically allocated memory
}

int GetMax(int* a, int n)
{
	int max = a[0];
	for (int i = 1; i < n; i++) // find the maximum value in the array
	{
		if (a[i] > max)
			max = a[i];
	}
	return max;
}

void CountSort(int* a, int n, int exp) // like counting sort, but sort with the unit (just 10 element each)
{
	int* b = new int[n];
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)
		count[(a[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n-1; i >= 0; i--)
	{
		b[count[(a[i] / exp) % 10] - 1] = a[i];
		count[(a[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
		a[i] = b[i];

	delete[]b;
}

void RadixSort(int* a, int n)
{
	int max = GetMax(a, n); // get the maximum value of the array
	for (int exp = 1; max / exp > 0; exp *= 10) // sort the array in each units
	{
		CountSort(a, n, exp);
	}
}

void FlashSort(int* a, int n) {
	// Stage 1: Classification

	// Find the minimum value in the array
    	int minVal = a[0];

    	// Find the maximum value and its index in the array
    	int max = 0;
    	for (int i = 1; i < n; i++) {
		if (a[i] < minVal)
			minVal = a[i];
		if (a[i] > a[max])
			max = i;
    	}

    	// If all elements are the same, no sorting is needed
    	if (a[max] == minVal)
        	return;

    	// Determine the number of classes and calculate a constant for classifying elements
    	int m = int(0.45 * n); // Split the array into m classes
    	double c1 = (double)(m - 1) / (a[max] - minVal); // Constant for finding the class of an element

    	// Initialize an array to store the number of elements in each class
    	int* l = new int[m];
    	for (int i = 0; i < m; i++)
        	l[i] = 0;

    	// Count the number of elements in each class
    	for (int i = 0; i < n; i++) {
        	int k = int(c1 * (a[i] - minVal)); // k is the class of the element
        	++l[k]; // Increase the count of elements in the class
    	}

    	// Compute the last position of each class in the array
    	for (int i = 1; i < m; i++)
       		l[i] += l[i - 1];

    	// Stage 2: Partition

    	// Swap the maximum value with the first element of the array
    	swap(a[max], a[0]);

    	int nmove = 0; // Count the number of swaps
    	int j = 0;
    	int k = m - 1;
    	int t = 0;
    	int flash;

    	// Perform partitioning and swapping until all elements are in their correct classes
    	while (nmove < n - 1) {
        	while (j > l[k] - 1) {
           		// Move to the next class if the current element is in its correct position
            		j++;
            		k = int(c1 * (a[j] - minVal));
        	}

        	// Store the element to be swapped
        	flash = a[j];

        	if (k < 0)
            	break;

        	// Swap elements until the current element is in its correct class
        	while (j != l[k]) {
            		k = int(c1 * (flash - minVal));
            		int hold = a[t = --l[k]];
            		a[t] = flash;
            		flash = hold;
            		++nmove;
        	}
    	}

    	// Clean up the memory allocated for counting array
    	delete[] l;

    	// Perform insertion sort on each small range
    	InsertionSort(a, n);
}

void SortAl(int a[], int n, int type) 
{
    switch (type) 
    {
    case 0:
     	SelectionSort(a, n);
     	break;
    case 1:
        InsertionSort(a, n);
        break;
    case 2:
        BubbleSort(a, n);
        break;
    case 3:
        ShakerSort(a, n);
        break;
    case 4:
        ShellSort(a, n);
        break;
    case 5:
        HeapSort(a, n);
        break;
    case 6:
        int left, right;
        left = 0;
        right = n - 1;
        MergeSort(a, left, right);
        break;
    case 7:
        int low, high;
        low = 0;
        high = n - 1;
        QuickSort(a, low, high);
        break;
    case 8:
        CountingSort(a, n);
        break;
    case 9:
        RadixSort(a, n);
        break;
    case 10:
        FlashSort(a, n);
        break;
    default:
        printf("Error: unknown data type!\n");
    }
}

void printArray(int *a, int n)
{
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
}

void Count_SelectionSort(int* a, int n, long long int& comparison) 
{
    int min_idx, min_val;
    for (int i = 0; ++comparison, i < n - 1; i++) 
    {
        min_idx = i;
        min_val = a[i];
        for (int j = i + 1; ++comparison, j < n; j++) 
        {
            if (++comparison, a[j] < a[min_idx]) 
            {
                min_idx = j; 
                min_val = a[j];
            }
        }
        swap(a[i], a[min_idx]);
    }
}

void Count_InsertionSort(int* a, int n, long long int& comparison) 
{ 
    for (int i = 1; ++comparison, i < n; i++) 
    {
        int key = a[i]; 
        int j = i - 1;
        while ((++comparison, j >= 0) && (++comparison, key < a[j])) 
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void Count_BubbleSort(int* a, int n, long long int& comparison) 
{
    for (int i = 0; ++comparison, i < n - 1; i++) 
    {
        for (int j = 0; ++comparison, j < n - i - 1; j++) 
        {
            if (++comparison, a[j] > a[j + 1]) 
            {
                swap(a[j], a[j+1]);
            }
        }
    }
}

void Count_ShakerSort(int* a, int n, long long int& comparison) {
    int left = 0, right = n - 1, k = 0;
     while (++comparison, left < right)
    {
        for (int i = right; ++comparison, i > left; i--) 
        {
            if (++comparison, a[i - 1] > a[i]) 
            {
                swap(a[i], a[i - 1]); 
                k = i;
            }
        }
        left = k;
        for (int i = left; ++comparison, i < right; i++) 
        {
            if (++comparison, a[i] > a[i + 1]) 
            {
                swap(a[i], a[i + 1]);
                k = i;
            }
        }
        right = k;
    }
}

void Count_ShellSort(int* a, int n, long long int& comparison)
{
    int gap, i, j, temp;
    for (gap = n / 2; comparison++, gap > 0; gap /= 2)
    {
        for (i = gap; comparison++, i < n; i++)
        {
            temp = a[i];
            for (j = i; (comparison++, j >= gap) && (comparison++, a[j - gap] > temp); j -= gap)
                a[j] = a[j - gap];

            a[j] = temp;
        }
    }
}

void Count_Sift(int* a, int left, int right, long long int& comparison)
{
    int i, j, x;
    i = left;
    j = 2 * i + 1;
    x = a[i];
    while (comparison++, j <= right)
    {
        if (comparison++, j < right)
            if (comparison++, a[j] < a[j + 1])
                j++;
        if (comparison++, x >= a[j])
            break;
        a[i] = a[j];
        i = j;
        j = 2 * i + 1;
    }
    a[i] = x;
}

void Count_HeapSort(int* a, int n, long long int& comparison)
{
    int left = n / 2;
    while (comparison++, left >= 0)
    {
        Count_Sift(a, left, n - 1, comparison);
        left--;
    }
    int right = n - 1;
    while (comparison++, right > 0)
    {
        swap(a[0], a[right]);
        right--;
        Count_Sift(a, 0, right, comparison);
    }
}

void Count_Merge(int* a, int left, int mid, int right, long long int& comparison)
{
    int i, j, k = left;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (i = 0; comparison++, i < n1; i++)
        L[i] = a[i + left];
    for (i = 0; comparison++, i < n2; i++)
        R[i] = a[i + 1 + mid];

    i = 0; j = 0;
    while ((comparison++, i < n1) && (comparison++, j < n2))
    {
        if (comparison++, L[i] < R[j])
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
    while (comparison++, i < n1)
    {
        a[k] = L[i];
        k++; i++;
    }
    while (comparison++, j < n2)
    {
        a[k] = R[j];
        k++; j++;
    }
    delete[] L;
    delete[] R;
}

void Count_MergeSort(int* a, int left, int right, long long int& comparison)
{
    if (comparison++, left < right)
    {
        int mid = left + (right - left) / 2;
        Count_MergeSort(a, left, mid, comparison);
        Count_MergeSort(a, mid + 1, right, comparison);
        Count_Merge(a, left, mid, right, comparison);
    }
}

int Count_Partition(int a[], int low, int high, long long int& comparison)
{
	int i, j, p;
	i = low;
	j = high + 1;
	p = a[low]; // set a pivot (left-end element) for comparison
	do
	{
		do i++; while (++comparison, a[i] < p); // find the position which a[left..i] < p < a[j..right]
		do j--; while (++comparison, a[j] > p);
		swap(a[i], a[j]); // swap the elements at positon i and j if i < j
	} while (++comparison, i < j);
	swap(a[i], a[j]); // undo the last swap between a[i] and a[j]
	swap(a[j], a[low]); // swap the pivot to its right position
	return j; // return the pivot position
}   

void Count_QuickSort(int* a, int left, int right, long long int& comparison)
{
    int p;
    if (comparison++, left < right)
    {
        p = Count_Partition(a, left, right, comparison);
        Count_QuickSort(a, left, p - 1, comparison);
        Count_QuickSort(a, p + 1, right, comparison);
    }
}

void Count_CountingSort(int* a, int n, long long int& comparison)
{
    int* b = new int[n];
    int max, min, i;
    max = a[0];
    min = a[0];
    for (i = 1; comparison++, i < n; i++)
    {
        if (comparison++, a[i] > max)
            max = a[i];
        if (comparison++, a[i] < min)
            min = a[i];
    }

    int k = max - min + 1;
    int* count = new int[k];
    for (i = 0; comparison++, i < k; i++)
        count[i] = 0;

    for (i = 0; comparison++, i < n; i++)
        count[a[i] - min]++;

    for (i = 1; comparison++, i < k; i++)
        count[i] += count[i - 1];

    for (i = 0; comparison++, i < n; i++)
    {
        b[count[a[i] - min] - 1] = a[i];
        count[a[i] - min]--;
    }

    for (i = 0; comparison++, i < n; i++)
        a[i] = b[i];
    delete[] b;
    delete[] count;
}

int Count_GetMax(int* a, int n, long long int& comparison)
{
    int max = a[0];
    for (int i = 1; comparison++, i < n; i++)
    {
        if (comparison++, a[i] > max)
            max = a[i];
    }
    return max;
}

void Count_CountSort(int* a, int n, int exp, long long int& comparison)
{
    int* b = new int[n];
    int i, count[10] = { 0 };

    for (i = 0; comparison++, i < n; i++)
        count[(a[i] / exp) % 10]++;

    for (i = 1; comparison++, i < 10; i++)
        count[i] += count[i - 1];

    for (i = n-1; comparison++, i >= 0; i--)
    {
        b[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }

    for (i = 0; comparison++, i < n; i++)
        a[i] = b[i];

    delete[] b;
}

void Count_RadixSort(int* a, int n, long long int& comparison)
{
    int max = Count_GetMax(a, n, comparison);
    for (int exp = 1; comparison++, max / exp > 0; exp *= 10)
    {
        Count_CountSort(a, n, exp, comparison);
    }
}

void Count_FlashSort(int* a, int n, long long int& comparison) 
{
    int minVal = a[0];
    int max = 0;
    int m = int(0.45 * n);
    int* l = new int[m];
    for (int i = 0; ++comparison, i < m; i++)
        l[i] = 0;
    for (int i = 1; ++comparison, i < n; i++)
    {
        if (++comparison, a[i] < minVal)
            minVal = a[i];
        if (++comparison, a[i] > a[max])
            max = i;
    }
    if (++comparison, a[max] == minVal)
        return;
    double c1 = (double)(m - 1) / (a[max] - minVal);
    for (int i = 0; ++comparison, i < n; i++)
    {
        int k = int(c1 * (a[i] - minVal));
        ++l[k];
    }
    for (int i = 1; ++comparison, i < m; i++)
        l[i] += l[i - 1];
    swap(a[max], a[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (++comparison, nmove < n - 1)
    {
        while (++comparison, j > l[k] - 1)
        {
            j++;
            k = int(c1 * (a[j] - minVal));
        }
        flash = a[j];
        if (++comparison, k < 0) break;
        while (++comparison, j != l[k])
        {
            k = int(c1 * (flash - minVal));
            int hold = a[t = --l[k]];
            a[t] = flash;
            flash = hold;
            ++nmove;
        }
    }
    delete[] l;
    Count_InsertionSort(a, n, comparison);
}

void Count_SortAl(int a[], int n, int type, long long int& comparison) 
{
    switch (type) 
    {
    case 0:
        Count_SelectionSort(a, n, comparison);
        break;
    case 1:
        Count_InsertionSort(a, n, comparison);
        break;
    case 2:
        Count_BubbleSort(a, n, comparison);
        break;
    case 3:
        Count_ShakerSort(a, n, comparison);
        break;
    case 4:
        Count_ShellSort(a, n, comparison);
        break;
    case 5:
        Count_HeapSort(a, n, comparison);
        break;
    case 6:
        int left, right;
        left = 0;
        right = n - 1;
        Count_MergeSort(a, left, right, comparison);
        break;
    case 7:
        int low, high;
        low = 0;
        high = n - 1;
        Count_QuickSort(a, low, high, comparison);
        break;
    case 8:
        Count_CountingSort(a, n, comparison);
        break;
    case 9:
        Count_RadixSort(a, n, comparison);
        break;
    case 10:
        Count_FlashSort(a, n, comparison);
        break;
    default:
        printf("Error: unknown data type!\n");
    }
}

int main ()
{
    for (int i = 0; i < 11; i++)
    {
        int * a = new int [30];
        ifstream fIn;
        fIn.open("data.txt");
        int temp, j = 0;
        long long int compare = 0;
        while (fIn >> temp)
        {
            a[j] = temp;
            j++;
            if (fIn.eof())
                break;
        }
        fIn.close();
        cout << "ALG: " << i << endl;
        printArray(a, 30);

        Count_SortAl(a, 30, i, compare);
        printArray(a, 30);
        delete[] a;
    }
    return 0;
}

