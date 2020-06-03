/*
* This program compares the runtimes of different sorting algorithms: BubbleSort, InsertionSort, SelectionSort,
* QuickSort and two different search algorithms: LinearSearch and BinarySearch.
* Developed by Fabián Gandarilla López for the UABC's Faculty of Science 2017-2 Data Structures laboratory.
*/

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <ctime>
#include <iomanip>

using namespace std;

// Sorting class holds all the sorting algorithms. In each algorithm the time of execution is calculated
// and returned as a clock_t.
class Sorting
{
	static clock_t start_t;
public:
	static long long comparisons;
	// Bubble sort works by repeteadly swapping adjacent elements that are out of order.
	static clock_t BubbleSort(int* v, int length)
	{
	    start_t = clock();
		comparisons = 0;
		int i, j, aux;
		for (i = 0; i < length; i++)
		{
			for (j = length - 1; j > i; j--)
			{
			    comparisons++;
				if (v[j] < v[j - 1])
				{
					aux = v[j];
					v[j] = v[j - 1];
					v[j - 1] = aux;
				}
			}
		}
		return (double)(clock() - start_t)*1000.0/CLOCKS_PER_SEC;
	}
	// Insertion sort works the way people sort a hand of cards. We start with an empty left hand and the cards
	// face down in the table. We then remove one card at a time from the table and insert it into the correct
	// position in the left hand. To find a correct position for a card, we compare it with each of the cards
	// already in the hand, from right to left. At all n the cards in the left hand are sorted.
	static clock_t InsertionSort(int* v, int length)
	{
	    start_t = clock();
		comparisons = 0;
		int i, j, key;
		for (j = 1; j < length; j++)
		{
			// Key is the element to sort
			key = v[j];
			// We move on position to the left to start comparing with the "left" hand.
			// These are all the elements to the left of v[j] which are already sorted.
			i = j - 1;
			// Compare with each element in the left hand to position this elements in its
			// correct position relative to these sorted elements. When this element is in its
			// correct position the loop will end.
			while (i >= 0 && v[i] > key)
			{
				comparisons++;
				// All elements that are bigger than the compared one are displaced
				// one place to the right.
				v[i + 1] = v[i];
				i--;
			}
			// Here is where the elements is placed in its correct position in the left hand.
			v[i + 1] = key;
		}
		return (double)(clock() - start_t)*1000.0/CLOCKS_PER_SEC;
	}
	// Selection sort works by finding the smallest element in the vector and exchanging with the one in
	// the first position, then finding the second smallest and exchanging it with the second element in the 
	// vector, continuing in this manner for the first n-1 elements of the vector.
	static clock_t SelectionSort(int *v, int length)
	{
	    start_t = clock();
		comparisons = 0;
		int j, smallest, i, aux;
		for (j = 0; j < length - 1; j++)
		{
			// Find the (j+1)th smallest element
			smallest = j;
			for (i = j + 1; i < length; i++)
			{
			    comparisons++;
				if (v[i] < v[smallest])
					smallest = i;
			}
			// Swap the (j+1)th smallest element with the jth element
			aux = v[j];
			v[j] = v[smallest];
			v[smallest] = aux;
		}
		return (double)(clock() - start_t)*1000.0/CLOCKS_PER_SEC;
	}
	// Quick sort applies the divide and conquer paradigm. It partitions (divides) the vector into two subvectors
	// v[p..q-1] and v[q+1..r] such that each element in v[p..q-1] is less than or equal to v[q], which is, in turn,
	// less than or equal to each element in v[q+1..r]. The index q is computed in this partition process. 
	// The conquer part comes from sorting the subvectors v[p..q-1] and v[q+1..r] by recursive calls of quicksort.
	// At the end since each subvector is sorted, the full vector will be sorted.
	static void QuickSort(int* v, int p, int r)
	{
		int q;
		comparisons++;
		if (p < r)
		{
			// Partition this vector or subvector into two subvectors of it.
			q = Partition(v, p, r);
			// Apply quicksort to each of these new subvectors.
			QuickSort(v, p, q - 1);
			QuickSort(v, q + 1, r);
		}
	}
	// Here the vector passed is partitioned in two. A pivot element is selected, in this case the one at the end
	// if the vector passed. All elements are compared to this pivot and the ones smaller or equal are placed to the left of
	// it and the larger ones are placed to the right of it
	static int Partition(int* v, int p, int r)
	{
		int aux, j;
		// x is the element on the right end, the pivot.
		int x = v[r];
		// i is the index to that will indicate the middle of the vector.
		int i = p - 1;
		for (j = p; j < r; j++)
		{
		    comparisons++;
			// When the element is smaller than the pivot it is swaped with the adjacent one.
			if (v[j] <= x)
			{
				i++;
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
		// At the end of the loop all elements smaller than the pivot will be to the left of the ith element
		// move the pivot to this position and return the index.
		aux = v[i + 1];
		v[i + 1] = v[r];
		v[r] = aux;
		return i + 1;
	}
	// Randomized quick sort works the same way but the pivot element for the partition is taken randomly.
	static void RandomizedQuickSort(int *v, int p, int r)
	{
		int q;
		comparisons++;
		if (p < r)
		{
			q = RandomizedPartition(v, p, r);
			RandomizedQuickSort(v, p, q - 1);
			RandomizedQuickSort(v, q + 1, r);
		}
	}
	// Here a pivot is selectioned randomly.
	static int RandomizedPartition(int *v, int p, int r)
	{
		int i = (rand() % (r - p + 1)) + p;
		int aux = v[r];
		v[r] = v[i];
		v[i] = aux;
		return Partition(v, p, r);
	}
	// Randomize in place repositions the elements in a vector randomly.
	static void RandomizeInPlace(int * v, int length)
	{
		srand(time(NULL));
		int i, aux, auxIndice;
		for (i = 1; i < length; i++)
		{
			auxIndice = (rand() % (length - i + 1)) + i - 1;
			aux = v[i];
			v[i] = v[auxIndice];
			v[auxIndice] = aux;
		}
	}
};
clock_t Sorting::start_t = 0;
long long Sorting::comparisons = 0;

// Searching class holds two searching algorithms: Linear search and Binary search.
class Searching
{
public:
	static long long comparisons;
	static clock_t timeTaken;
	// Linear search works by traversint the vector completely and when the element is found it returns it.
    static int LinearSearch(int* v, int length, int element)
    {
		timeTaken = clock();
		comparisons = 0;
        for(int i=0;i < length; i++)
        {
			comparisons++;
            if(v[i] == element)
                return i;
        }
		timeTaken = (double)(clock() - timeTaken)*1000.0/CLOCKS_PER_SEC;
        return -1;
    }
	// Binary works by going to the element in the middle, if the element in the middle is smaller than the one we
	// are looking for than the left half is descarted and we apply the same procedure to the right half. If the element
	// in the middle is larger than the one we are looking for than the right half is descarted and we apply the same procedure to 
	// the left half. For this to work the vector needs to be sorted.
    static int BinarySearch(int* v, int length, int element)
    {
		timeTaken = clock();
		comparisons = 0;
        int p = 0;
        int r = length - 1;
        int mid;
        do
        {
			// Get element at the middle
            mid = floor(((double)p+r)/2);
			// Found it?
			comparisons++;
            if(v[mid] = element)
			{
				timeTaken = (double)(clock() - timeTaken)*1000.0/CLOCKS_PER_SEC;
				return mid;
			}
			// If the middle element is smaller than the one we
			// are looking for than only the right half will be
			// considered in the next iteration
            else if(v[mid] < element)
                p = mid + 1;
			// If the middle element is larger than the one we
			// are looking for than only the left half will be
			// considered in the next iteration.
            else
                r = mid - 1;
        } while (p<r);
		timeTaken = (double)(clock() - timeTaken)*1000.0/CLOCKS_PER_SEC;
        return -1;
    }
};
long long Searching::comparisons;
clock_t Searching::timeTaken;
// Draw the given char consecutively n times
void draw(int n, char charToDraw)
{
    for(int i = 0; i < n; i++)
    {
        cout << charToDraw;
    }
}
int main()
{
	cout << "Comparison of sorting and searching algorithms" << endl;
	clock_t timeBubble, timeInsertion, timeSelection, timeQuick, timeRandomQuick, timeLinear, timeBinary;
	long long bubbleComparisons, insertionComparisons, selectionComparisons, quickComparisons, randomizedComparisons;
	long long linearComparisons, binaryComparisons;
    // Size of the vector used for the comparison of algorithms.
	int n = 100000;
	cout << "The size of the vector is " << n << endl;
	// Allocate memory for the vector.
    int* v = (int*)malloc(n*sizeof(int));
	// Give each element the number of its position.
    for(int i=0; i < n; i++)
    {
        v[i] = i;
    }
    
	// Bubble sort
	cout << "Randomizing position of elements in vector" << endl;
	Sorting::RandomizeInPlace(v, n);
	cout << "Sorting with Bubble sort" << endl;
	timeBubble = Sorting::BubbleSort(v, n);
	bubbleComparisons = Sorting::comparisons;
	cout << "Done" << endl;

	// Insertion sort
	cout << "Randomizing position of elements in vector" << endl;
	Sorting::RandomizeInPlace(v, n);
	cout << "Sorting with Insertion sort" << endl;
	timeInsertion = Sorting::InsertionSort(v, n);
	insertionComparisons = Sorting::comparisons;
	cout << "Done" << endl;

	// Selection sort
	cout << "Randomizing position of elements in vector" << endl;
	Sorting::RandomizeInPlace(v, n);
	cout << "Sorting with Selection sort" << endl;
	timeSelection = Sorting::SelectionSort(v, n);
	selectionComparisons = Sorting::comparisons;
	cout << "Done" << endl;
	
	// Quick sort
	cout << "Randomizing position of elements in vector" << endl;
	Sorting::RandomizeInPlace(v, n);
	cout << "Sorting with Quick sort" << endl;
	timeQuick = clock();
	Sorting::QuickSort(v, 0, n-1);
	timeQuick = (double)(clock() - timeQuick)*1000.0/CLOCKS_PER_SEC;
	quickComparisons = Sorting::comparisons;
	cout << "Done" << endl;

	// Randomized quick sort
	cout << "Randomizing position of elements in vector" << endl;
	Sorting::RandomizeInPlace(v, n);
	cout << "Sorting with Randomized quick sort" << endl;
	timeRandomQuick = clock();
	Sorting::RandomizedQuickSort(v, 0, n-1);
	timeRandomQuick = (double)(clock() - timeRandomQuick)*1000.0/CLOCKS_PER_SEC;
	randomizedComparisons = Sorting::comparisons;
	cout << "Done" << endl;

	// Linear search
	cout << "Randomizing position of elements in vector" << endl;
	Sorting::RandomizeInPlace(v, n);
	cout << "Searching all elements with Linear search" << endl;
	timeLinear = clock();
    for(int i = 0; i < n; i++)
    {
        Searching::LinearSearch(v, n, i);
    }
    timeLinear = (double)(clock() - timeLinear)*1000.0/CLOCKS_PER_SEC;
	cout << "Done" << endl;

	// Binary search
	timeBinary = clock();
	cout << "Sorting elements with Quick sort to do Binary search" << endl;
	Sorting::QuickSort(v, 0, n-1);
	cout << "Done" << endl;
	cout << "Searching all elements with Binary search" << endl;
	for (int i = 0; i < n; i++) 
	{
		Searching::BinarySearch(v, n, i);
	}
	timeBinary = (double)(clock() - timeBinary)*1000.0/CLOCKS_PER_SEC;
	cout << "Done" << endl;

	// Printing results
    draw(63, '-'); cout << endl;
	draw(63, '-'); cout << endl;
    cout  << "| | Algorithm            | " << "Time (ms) | " << "Comparisons (sorting)| |"<< endl;
    draw(63, '-'); cout << endl;
    cout  << "| | Bubblesort           | " << timeBubble << "     | " << bubbleComparisons << "           | |" << endl;
    draw(63, '-'); cout << endl;
    cout  << "| | Insertionsort        | " << timeInsertion << "     | " << insertionComparisons << "           | |" << endl;
    draw(63, '-'); cout << endl;
	cout  << "| | Selectionsort        | " << timeSelection << "     | " << selectionComparisons << "           | |" << endl;
    draw(63, '-'); cout << endl;
	cout  << "| | Quicksort            | " << timeQuick << "        | " << quickComparisons << "           | |" << endl;
    draw(63, '-'); cout << endl;
	cout  << "| | Randomized Quicksort | " << timeRandomQuick << "        | " << randomizedComparisons << "           | |" << endl;
    draw(63, '-'); cout << endl;
	cout  << "| | Linear search        | " << timeLinear << "     |" << setw(22) << "" << "| |" << endl;
    draw(63, '-'); cout << endl;
	cout  << "| | Binary search        | " << timeBinary << "        |" << setw(22) << "" << "| |" << endl;
    draw(63, '-'); cout << endl;
	draw(63, '-'); cout << endl;
	cin;
    return 0;
}



