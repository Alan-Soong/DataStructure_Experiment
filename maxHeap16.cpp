#include<iostream>
constexpr auto INF = -858993460;
using namespace std;

template<typename T>
class maxHeap {
	T* heap;
	int arrayLength;
	int heapSize;
public:
	maxHeap() {
		heap = new T[0];
		heapSize = 0;
		arrayLength = 0;
	}
	maxHeap(int n) {
		heap = new T[2 * n + 2];
		arrayLength = 2 * n + 2;
	}
	bool isEmpty() {
		return heapSize == 0;
	}
	T* maxElement(T tmp) {
		heap[0] = tmp;
		return heap;
	}
	T* minElement(T tmp) {
		heap[heapSize + 1] = tmp;
		return heap;
	}
	T top();
	void push(const T& mem);
	void pop();
	void initialize(T* theHeap, int theSize);
	void printf();
};

template<typename T>
T maxHeap<T>::top()
{
	if (isEmpty()) {
		cout << "queueEmpty! " << endl;
		return;
	}
	return heap[1];
}

template<typename T>
void maxHeap<T>::push(const T& mem)
{
	if (heapSize == arrayLength / 2 - 1) {
		changeLengthID(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < mem) {
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}

	heap[currentNode] = mem;
}

template<typename T>
void maxHeap<T>::pop()
{
	if (heapSize == 0) {
		cout << "queueEmpty! " << endl;
		return;
	}
	heap[0] = INF;

	T lastElement = heap[heapSize--];

	int currentNode = 1, child = 2;
	while (child <= heapSize) {
		if (child < heapSize && heap[child] < heap[child + 1]) {
			child++;
		}
		if (lastElement >= heap[child]) {
			break;
		}
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template<typename T>
T* ChangeLengthID(T* array, int a, int b)
{
	T* newarray = new T[b];
	int c = (a < b) ? a : b;
	for (int i = 0; i < c; i++)
		newarray[i] = array[i];
	delete[]array;
	return newarray;
}

template<typename T>
void maxHeap<T>::initialize(T* theHeap, int theSize)
{
	delete[] heap;
	heap = theHeap;
	heapSize = theSize;

	for (int root = (heapSize - 1) / 2; root >= 0; root--) {
		T rootElement = heap[root];

		int child = 2 * root;
		while (child <= heapSize) {
			if (child < heapSize && heap[child] < heap[child + 1]) {
				child++;
			}
			if (rootElement >= heap[child]) {
				break;
			}
			heap[child / 2] = heap[child];
			child *= 2;
		}
		heap[child / 2] = rootElement;
	}
}

template<typename T>
void maxHeap<T>::printf()
{
	for (int index = 0; index < heapSize; index++) {
		cout << heap[index] << " ";
	}
	cout << endl;
	return;
}

int main() {
	int array[10] = { 1,3,4,5,3,6,2,7,9,0 };
	int size = 10;
	maxHeap<int> elements;
	elements.initialize(array, size);
	elements.printf();
	cout << "Hello, world! " << endl;
}