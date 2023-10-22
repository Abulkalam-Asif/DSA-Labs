#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
	int frontIndex;
	int rearIndex;
	int queueCapacity;
	int numberOfElements;
	T* queueData;

public:
	Queue() {
		rearIndex = frontIndex = -1;
		numberOfElements = queueCapacity = 0;
		queueData = nullptr;
	}
	Queue(int queueCapacity) : queueCapacity(queueCapacity) {
		rearIndex = frontIndex = -1;
		numberOfElements = 0;
		if (queueCapacity > 0) {
			queueData = new T[queueCapacity];
		} else {
			queueData = nullptr;
		}
	}
	~Queue() {
		delete[] queueData;
		queueData = nullptr;
	}
	void insertFront(const T element) {
		if (isEmpty()) {
			frontIndex = 0;
			rearIndex = 0;
		} else if (frontIndex == 0) {
			frontIndex = queueCapacity - 1;
		} else {
			--frontIndex;
		}
		queueData[frontIndex] = element;
		++numberOfElements;
	}
	T removeRear() {
		if (isEmpty()) {
			throw runtime_error("Exception! Removing element from empty queue!");
		} else {
			T toReturn = queueData[rearIndex];
			if (numberOfElements == 1) {
				frontIndex = -1;
				rearIndex = -1;
			} else {
				rearIndex = (--rearIndex + queueCapacity) % queueCapacity;
			}
			--numberOfElements;
			return toReturn;
		}
	}
	T getRear() {
		return queueData[rearIndex];
	}
	T getFront() {
		return queueData[frontIndex];
	}
	bool isEmpty() const {
		return numberOfElements == 0;
	}
	bool isFull() const {
		return numberOfElements == queueCapacity;
	}
	int size() const {
		return numberOfElements;
	}
	bool serach(T key) {
		int i = frontIndex;
		while (true) {
			if (queueData[i] == key) {
				return true;
			}
			if (i == rearIndex) {
				break;
			}
			i = ++i % queueCapacity;
		}
		return false;
	}
	int getCapacity() const {
		return queueCapacity;
	}
	template <typename U>
	friend void printLRUCache(const Queue<U>&);
};

template <typename T>
void printLRUCache(const Queue<T>& queue) {
	if (!queue.isEmpty()) {
		int i = queue.frontIndex;
		while (true) {
			cout << queue.queueData[i] << " ";
			if (i == queue.rearIndex) {
				break;
			}
			i = ++i % queue.queueCapacity;
		}
		cout << endl;
	}
}

int main() {
	int memorySpace = 0;
	do {
		cout << "Enter memory space (> 0): ";
		cin >> memorySpace;
	} while (memorySpace < 1);
	int pageNumber = -1;

	Queue<int> queue(memorySpace);
	while ((true)) {
		cout << "Enter page number (-1 to exit): ";
		cin >> pageNumber;
		if (pageNumber == -1) {
			break;
		}
		if (queue.serach(pageNumber)) {
			if (queue.getFront() != pageNumber) {
				// If the page not at front, do this, else, do nothing
				if (queue.getRear() == pageNumber) {
					// If the page is at the rear, simply bring it to front
					queue.insertFront(queue.removeRear());
				} else {
					// If the page is somewhere in the middle, create a temp queue
					Queue<int> tempQueue(queue.size() - 1);
					// Shift all the pages to the temp queue, except the page number entered by the user
					while (queue.size() != 0) {
						int temp = queue.removeRear();
						if (temp == pageNumber) {
							continue;
						}
						tempQueue.insertFront(temp);
					}
					// Shift them back to the original queue
					while (tempQueue.size() != 0) {
						queue.insertFront(tempQueue.removeRear());
					}
					// Insert the user entered page to the front
					queue.insertFront(pageNumber);
				}
			}
		} else {
			if (queue.isFull()) {
				queue.removeRear();
			}
			queue.insertFront(pageNumber);
		}
		printLRUCache(queue);
	}

	return 0;
}