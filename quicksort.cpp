#include <array>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>

const int COUNT=100000;

using namespace std;

array<int, COUNT> unsorted;
array<int, COUNT> sorted1;
array<int, COUNT> sorted2;

template <class T, size_t COUNT>
size_t partition(array<T, COUNT>& arr, size_t first, size_t end)
{
    assert(end - first >= 1);

    T pivot = arr[end - 1];

    size_t end_low = first; // all elements [first, end_low) are < pivot
    size_t first_high = end - 1; // all elements [first_high, end - 1) are >= pivot

    do {

	while((end_low != first_high) && (arr[end_low] < pivot)) {
	    end_low++;
	}

	// if end_low == first_high, then no more elements >= pivot

	if(end_low != first_high) {

	    // arr[end_low] >= pivot

	    while((first_high != end_low) && (arr[first_high] >= pivot)) {
		first_high--;
	    }

	    // if first_high == "end_low" (no more elements < pivot)

	    if(end_low != first_high) {
		// arr[end_low] >= pivot and arr[first_high] < pivot
		// so swap those
		std::swap(arr[end_low], arr[first_high]);
	    }
	}

    } while(end_low != first_high);

    std::swap(arr[first_high], arr[end - 1]);

    return end_low;
}


template <class T, size_t COUNT>
void quicksort(array<T, COUNT>& arr, size_t first, size_t end)
{
    if(end - first <= 1)
	return;

    size_t pivot = partition(arr, first, end);
    quicksort(arr, first, pivot);
    quicksort(arr, pivot + 1, end);
}

int main(int argc, char **argv)
{
    srand(time(0));
    generate(unsorted.begin(), unsorted.end(), [](){return rand();});

    copy(unsorted.begin(), unsorted.end(), sorted1.begin());

    quicksort(sorted1, 0, sorted1.size());

    for(size_t i = 1; i < sorted1.size(); i++)
	if(sorted1[i - 1] > sorted1[i]) {
	    cerr << "elements " << sorted1[i - 1] << " and " << sorted1[i] << " out of order.\n";
	    return(EXIT_FAILURE);
	}
}
