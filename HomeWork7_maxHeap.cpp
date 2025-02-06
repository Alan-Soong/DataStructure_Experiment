#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

template<typename T>
class maxHeap {
	vector<T> heap;
	int maxElement;
	int minElement;
	int arrayLength;
	int heapSize;

	/*//insert a element to keep
	void percolateUp(int hole) {
		int x = heap[hole];
		for (; hole > 1 && x > heap[hole / 2]; hole >>= 1) {
			heap[hole] = heap[hole / 2];
		}
		heap[hole] = x;
	}*/

	// 将元素向上调整以维护最大堆性质，充分利用最大值和最小值边界
	void percolateUp(int hole) {
		int x = heap[hole];
		while (hole > 1 && x > heap[hole / 2]) {
			// 与最大值比较，如果当前元素已经达到最大值，无需继续向上调整
			if (x == maxElement) {
				break;
			}
			heap[hole] = heap[hole / 2];
			hole >>= 1;
		}
		heap[hole] = x;
	}

	/*//romove a element to keep
	void percolataDown(int hole) {
		int x = heap[hole];
		int child = 0;
		for (; hole * 2 <= heapSize; hole = child) {
			child = hole * 2;
			if (child != heapSize && heap[child + 1] > heap[child]) {
				child++;
			}
			if (x < heap[child]) {
				heap[hole] = heap[child];
			}
			else { break; }
		}
		heap[hole] = x;
	}*/

	// 将元素向下调整以维护最大堆性质，充分利用最大值和最小值边界
	void percolataDown(int hole) {
		int x = heap[hole];
		int child = 0;
		while (hole * 2 <= heapSize) {
			child = hole * 2;
			if (child != heapSize && heap[child + 1] > heap[child]) {
				child++;
			}
			// 与最小值比较，如果当前节点的值已经小于等于最小值，无需继续向下调整
			if (x <= minElement) {
				break;
			}
			// 正常比较交换逻辑，若子节点大于当前节点则交换
			if (heap[child] > x) {
				heap[hole] = heap[child];
				hole = child;
			}
			else {
				break;
			}
		}
		heap[hole] = x;
	}

public:
	maxHeap(int max, int min, int len) {
		maxElement = max;
		minElement = min;
		heapSize = 0;
		arrayLength = len;
		heap.resize(2 * arrayLength + 2);
		heap[0] = maxElement;
		heap[arrayLength + 1] = minElement;
	}
	bool isEmpty() {
		return heapSize == 0;
	}
	bool isFull() {
		return heapSize == 2 * arrayLength + 2;
	}
	T top();
	void push(const T& mem);
	T pop();
	int size() {
		return heapSize;
	}
	void printf();
};

template<typename T>
T maxHeap<T>::top()
{
	if (isEmpty()) {
		cout << "Heap is empty!" << endl;
		return -1;
	}
	int maxVal = heap[1];
	return maxVal;
}

template<typename T>
void maxHeap<T>::push(const T& mem)
{
	if (mem >= maxElement || mem <= minElement) {
		cout << "Invalid input! Out of range!" << endl;
		return;
	}
	if (find(heap.begin(), heap.end(), mem) != heap.end()) {
		cout << "Repeated input!" << endl;
		return;
	}
	//heapSize++;
	heap[++heapSize] = mem;
	percolateUp(heapSize);
}

template<typename T>
T maxHeap<T>::pop()
{
	if (heapSize == 0) {
		cout << "Pop is invalid! Heap is empty!" << endl;
		return minElement;
	}
	int maxVal = heap[1];
	heap[1] = heap[heapSize];
	heapSize--;
	percolataDown(1);
	return maxVal;
}

template<typename T>
void maxHeap<T>::printf()
{
	for (int index = 0; index < heapSize + 2; index++) {
		cout << heap[index] << " ";
	}
	cout << endl;
	return;
}

int main() {
	int n = 0;
	cin >> n;

	srand(static_cast<unsigned int>(time(nullptr)));

	maxHeap<int> mH(100, 0, n);
	for (int i = 0; i < n; i++) {
		mH.push(rand() % 101);
	}

	cout << "排序前（含max和min）：";
	mH.printf();
	cout << endl;

	int add = 0;
	cout << "输入添加的数量：" << endl;
	cin >> add;
	for (int i = 0; i < add; i++) {
		mH.push(rand() % 101);
	}

	cout << "排序前（含max和min）：";
	mH.printf();
	cout << endl;

	cout << "排序后（不含max和min）：";
	while (mH.size() > 0) {
		cout << mH.pop() << " ";
	}
	cout << endl;

	return 0;
}