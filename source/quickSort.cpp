#include "quickSort.h"

static void printData(int* data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}

static bool checkData(int* data, size_t size) {
	for (size_t i = 0; i < size - 1; i++) {
		if (data[i] > data[i + 1]) {
			return false;
		}
	}
	return true;
}

static int getPivotIndex(size_t size) {
	return static_cast<int>(getRandomNumber(0, size));
}

static void partition(int* elems, size_t size) {
	if (size < 2) {
		// This list is already sorted
		return;
	}
	int pivot = elems[rand() % size];
	int low = 0;
	int high = size - 1;
	while (low < high) {
		// If the two values are equal, we need to make sure we aren't also
		// equal to the pivot, otherwise that's bad news bears (infinite looping).
		if (elems[low] == elems[high]) {
			if (elems[low] < pivot) {
				low++;
			}
			else {
				high--;
			}
		}
		while (elems[low] < pivot) {
			low++;
		}
		while (elems[high] > pivot) {
			high--;
		}
		int temp = elems[low];
		elems[low] = elems[high];
		elems[high] = temp;
	}
	partition(elems, low);
	partition(elems + low + 1, size - low - 1);
}

static void quickSort(int* elems, size_t size) {
	partition(elems, size);
}

void test_quickSort() {
	const int DATA_SIZE = 20;
	const int NUM_TESTS = 10;
	int elems[DATA_SIZE] = { 0 };
	
	// Loop through some arbitrary amount of times just to verify
	for (int j = 0; j < NUM_TESTS; j++) {
		for (size_t i = 0; i < DATA_SIZE; i++) {
			elems[i] = static_cast<int>(getRandomNumber(0, 100));
		}
		quickSort(elems, DATA_SIZE);
		if (!checkData(elems, DATA_SIZE)) {
			std::cout << "Quicksort failed to sort: ";
			printData(elems, DATA_SIZE);
			return;
		}
	}
	std::cout << "Quicksort successfully tested " << NUM_TESTS << " times." << std::endl;
}