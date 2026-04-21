// MaxHeap code
#include <iostream>
using namespace std;
#define MAX 50
// Max Heap
class MaxHeap
{
public:
    int heap[MAX];
    int size;
    MaxHeap() { size = 0; }
    int top()
    {
        return (size > 0) ? heap[0] : -1;
    }
    void insert(int value)
    {
        if (size == MAX)
        {
            cout << "Max Heap Overflow!" << endl;
            return;
        }
        int i = size;
        heap[i] = value;
        size++;
        while (i > 0 && heap[i] > heap[(i - 1) / 2])
        {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    void heapify(int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < size && heap[left] > heap[largest])
            largest = left;
        if (right < size && heap[right] > heap[largest])
            largest = right;
        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }
    int getTop()
    {
        if (size <= 0)
            return -1;
        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);
        return root;
    }
};
// Min Heap
class MinHeap
{
public:
    int heap[MAX];
    int size;
    MinHeap() { size = 0; }
    int top()
    {
        return (size > 0) ? heap[0] : -1;
    }
    void insert(int value)
    {
        int i = size;
        heap[i] = value;
        size++;
        while (i > 0 && heap[(i - 1) / 2] > heap[i])
        {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    void heapify(int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;
        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
    int getTop()
    {
        if (size <= 0)
            return -1;
        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);
        return root;
    }
};
class FindMedian
{
    MaxHeap left;
    MinHeap right;

public:
    void insert(int num)
    {
        if (left.size == 0 || num <= left.top())
            left.insert(num);
        else
            right.insert(num);
        if (left.size > right.size + 1)
        {
            right.insert(left.getTop());
        }
        else if (right.size > left.size + 1)
        {
            left.insert(right.getTop());
        }
    }
    double getMedian()
    {
        if (left.size == right.size)
            return (left.top() + right.top()) / 2.0;
        else if (left.size > right.size)
            return left.top();
        else
            return right.top();
    }
};
int main()
{
    FindMedian ms;
    int arr[] = {50, 30, 40, 10, 5, 20, 60};
    for (int i = 0; i < 7; i++)
    {
        ms.insert(arr[i]);
        cout << "Inserted: " << arr[i] << ":"
             << "Median: " << ms.getMedian() << endl;
    }
    return 0;
}