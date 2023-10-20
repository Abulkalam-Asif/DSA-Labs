#include <iostream>
#include <climits>
using namespace std;

class NDArray {
private:
	int noOfDim;
	int arrSize;
	int* arr;

public:
	NDArray() {
		noOfDim = 0;
		arrSize = 0;
		arr = nullptr;
	}
	NDArray(int noOfDim, int* dimSize) {
		this->noOfDim = noOfDim;
		arrSize = 1;
		for (size_t i = 0; i < noOfDim; ++i) {
			arrSize *= dimSize[i];
		}
		arr = new int(arrSize);
		for (size_t i = 0; i < arrSize; i++) {
			arr[i] = INT_MAX;
		}
	}
	int getArrSize() {
		return arrSize;
	}
	void print() {
		for (size_t i = 0; i < arrSize; i++) {
			cout << arr[i] << " ";
		}
	}
};

int main() {
	int dimSize[4] = { 6, 7, 3, 5 };
	NDArray array(4, dimSize);
	cout << array.getArrSize() << endl;
	array.print();

	return 0;
}
