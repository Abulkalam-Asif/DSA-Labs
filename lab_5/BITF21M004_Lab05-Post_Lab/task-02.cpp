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
	void insertRear(const T element) {
		if (isFull()) {
			throw runtime_error("Exception! Pushing to a full stack!");
		} else if (isEmpty()) {
			frontIndex = 0;
			rearIndex = 0;
		} else if (rearIndex == queueCapacity - 1) {
			rearIndex = 0;
		} else {
			++rearIndex;
		}
		queueData[rearIndex] = element;
		++numberOfElements;
	}
	T removeFront() {
		if (isEmpty()) {
			throw runtime_error("Exception! Popping from an empty stack!");
		} else {
			T toReturn = queueData[frontIndex];
			if (numberOfElements == 1) {
				frontIndex = -1;
				rearIndex = -1;
			} else {
				frontIndex = ++frontIndex % queueCapacity;
			}
			--numberOfElements;
			return toReturn;
		}
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
	int getCapacity() const {
		return queueCapacity;
	}
	template <typename U>
	friend void printStack(const Queue<U>&);
};

template <typename T>
void printStack(const Queue<T>& queue) {
	if (!queue.isEmpty()) {
		int i = queue.rearIndex;
		while (true) {
			cout << queue.queueData[i] << " ";
			if (i == queue.frontIndex) {
				break;
			}
			i = (--i + queue.queueCapacity) % queue.queueCapacity;
		}
		cout << endl;
	} else {
		cout << "(stack in empty)" << endl;
	}
}

int main() {
	int stackSize = 0;
	while (stackSize < 1) {
		cout << "Enter the size of the stack (>0): ";
		cin >> stackSize;
	}
	Queue<int> stack(stackSize);
	cout << "\n---------------\n1- Push" << endl;
	cout << "2- Pop" << endl;
	cout << "3- Print" << endl;
	cout << "4- Exit" << endl;
	cout << "Your choice: ";
	int option;
	cin >> option;
	cout << "---" << endl;
	while (true) {
		if (option == 1) {
			if (stack.isFull()) {
				cout << "Exception! Pushing to a full stack" << endl;
			} else {
				int element;
				cout << "Enter an element to push: ";
				cin >> element;
				stack.insertRear(element);
				cout << element << " pushed successfully!" << endl;
			}
		} else if (option == 2) {
			if (stack.isEmpty()) {
				cout << "Exception! Popping from an empty stack" << endl;
			} else if (stack.size() == 1) {
				int poppedElement = stack.removeFront();
				cout << poppedElement << " popped successfully!" << endl;
			} else {
				Queue<int> temp(stack.size() - 1);
				while (stack.size() != 1) {
					temp.insertRear(stack.removeFront());
				}
				int poppedElement = stack.removeFront();
				while (temp.size() != 0) {
					stack.insertRear(temp.removeFront());
				}
				cout << poppedElement << " popped successfully!" << endl;
			}
		} else if (option == 3) {
			cout << "Displaying stack (top to bottom): ";
			printStack(stack);
		} else if (option == 4) {
			return 0;
		} else {
			cout << "Invalid option!" << endl;
		}
		cout << "\n---------------\n1- Push" << endl;
		cout << "2- Pop" << endl;
		cout << "3- Print" << endl;
		cout << "4- Exit" << endl;
		cout << "Your choice: ";
		cin >> option;
		cout << "---" << endl;
	}

	return 0;
}