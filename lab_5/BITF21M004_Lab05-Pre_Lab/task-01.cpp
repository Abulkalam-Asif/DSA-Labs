#include <iostream>
using namespace std;

template <typename T>
class MyQueue {
private:
	int frontIndex;
	int rearIndex;
	int queueCapacity;
	int numberOfElements;
	T* queueData;
	void resize() {
		if (queueCapacity == 0) {
			queueCapacity = 1;
			queueData = new T[queueCapacity];
		} else if (numberOfElements == queueCapacity) {
			queueCapacity *= 2;
			T* temp = new T[queueCapacity];
			for (size_t i = 0; i < numberOfElements; i++) {
				temp[i] = queueData[i];
			}
			delete[] queueData;
			queueData = temp;
		}
	}

public:
	MyQueue() {
		rearIndex = frontIndex = numberOfElements = queueCapacity = 0;
		queueData = nullptr;
	}
	MyQueue(const MyQueue<T>& obj) : frontIndex(obj.frontIndex), rearIndex(obj.rearIndex), queueCapacity(obj.queueCapacity), numberOfElements(obj.numberOfElements) {
		if (obj.queueCapacity == 0) {
			queueData = nullptr;
		} else {
			queueData = new T[queueCapacity];
			for (size_t i = 0; i < numberOfElements; i++) {
				queueData[i] = obj.queueData[i];
			}
		}
	}
	MyQueue<T>& operator=(const MyQueue<T>& obj) {
		if (this != &obj) {
			delete[] queueData;

			frontIndex = obj.frontIndex;
			rearIndex = obj.rearIndex;
			queueCapacity = obj.queueCapacity;
			numberOfElements = obj.numberOfElements;

			if (queueCapacity == 0) {
				queueData = nullptr;
			} else {
				queueData = new T[queueCapacity];
				for (size_t i = 0; i < numberOfElements; i++) {
					queueData[i] = obj.queueData[i];
				}
			}
		}
		return *this;
	}

	~MyQueue() {
		delete[] queueData;
		queueData = nullptr;
	}
	void enqueue(const T element) {
		this->resize();
		queueData[rearIndex] = element;
		++numberOfElements;
		++rearIndex;
	}
	T dequeue() {
		if (numberOfElements != 0) {
			--numberOfElements;
			return queueData[frontIndex++];
		} else {
			throw runtime_error("Exception! Dequeue from an empty array!");
		}
	}
	T getFront() const {
		if (numberOfElements != 0) {
			return queueData[frontIndex];
		} else {
			throw runtime_error("Exception! Getting front from an empty queue!");
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
	void printQueue() {
		for (size_t i = frontIndex; i < rearIndex; i++) {
			cout << queueData[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	// Driver program with and integers queue
	MyQueue<int> queue;

	while (true) {
		cout << "\n---------------------\nChoose an action:\n"
			<< "1. Enqueue an element\n"
			<< "2. Dequeue an element\n"
			<< "3. Get the front element\n"
			<< "4. Check if the queue is empty\n"
			<< "5. Check if the queue is full\n"
			<< "6. Get the number of elements in the queue\n"
			<< "7. Get the queue capacity\n"
			<< "8. Copy and print\n"
			<< "9. Print the queue\n"
			<< "10. Exit\n";

		int choice;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) {
			int element;
			cout << "Enter an element to enqueue: ";
			cin >> element;
			queue.enqueue(element);
			cout << "Element enqueued successfully!" << endl;
		} else if (choice == 2) {
			try {
				int dequeuedElement = queue.dequeue();
				cout << "Element dequeued successfully!\nDequeued element: " << dequeuedElement << endl;
			} catch (exception& e) {
				cout << e.what() << endl
					<< endl;
			}
		} else if (choice == 3) {
			try {
				int frontElement = queue.getFront();
				cout << "Front element: " << frontElement << endl;
			} catch (exception& e) {
				cout << e.what() << endl
					<< endl;
			}
		} else if (choice == 4) {
			cout << "Is the queue empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;
		} else if (choice == 5) {
			cout << "Is the queue full? " << (queue.isFull() ? "Yes" : "No") << endl;
		} else if (choice == 6) {
			cout << "Number of elements in the queue: " << queue.size() << endl;
		} else if (choice == 7) {
			cout << "Queue capacity: " << queue.getCapacity() << endl;
		} else if (choice == 8) {
			MyQueue<int> queue2(queue);
			queue2.printQueue();
		} else if (choice == 9) {
			cout << "Queue contents: ";
			queue.printQueue();
		} else if (choice == 10) {
			return 0;
		} else {
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}