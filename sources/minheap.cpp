#include "minheap.h"
using namespace std;

Minheap::Minheap(int w)
{
    weight = w;
    size = 0;
    heap = new Huffman_node *[weight];
}

Minheap::~Minheap()
{
    delete[] heap;
}

int Minheap::parent(int i)
{
    return (i - 1) / 2;
}

int Minheap::l_child(int i)
{
    return (2 * i) + 1;
}

int Minheap::r_child(int i)
{
    return (2 * i) + 2;
}

void Minheap::swap(int i, int j)
{
    Huffman_node *temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void Minheap::heapify_up(int i)
{
    while (i > 0 && heap[parent(i)]->number_of_data > heap[i]->number_of_data)
    {
        swap(i, parent(i));
        i = parent(i);
    }
}

void Minheap::heapify_down(int i)
{
    int small = i;
    int left = l_child(i);
    int right = r_child(i);

    if (left < size && heap[left]->number_of_data < heap[small]->number_of_data)
    {
        small = left;
    }

    if (right < size && heap[right]->number_of_data < heap[small]->number_of_data)
    {
        small = right;
    }

    if (small != i)
    {
        swap(i, small);
        heapify_down(small);
    }
}

void Minheap::insert(Huffman_node* node)
{
    if (size >= weight)
    {
        throw Run_Time_Error("Heap is full\n");
    }
    heap[size] = node;
    heapify_up(size);
    size++;
}

Huffman_node* Minheap::extract()
{
    if (size <= 0)
    {
        throw Run_Time_Error("Can't Extract: heap is empty\n");
    }
    Huffman_node* min = heap[0];
    heap[0] = heap[size - 1];
    size--;

    if (size > 0)
    {
        heapify_down(0);
    }
    return min;
}

int Minheap::get_size() const
{
    return size;
}

bool Minheap::is_empty()
{
    return size == 0;
}
