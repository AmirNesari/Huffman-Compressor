#ifndef minheap_h
#define minheap_h
#include "huffman_node.h"

class Minheap
{
private:
    Huffman_node** heap;
    int weight;
    int size;
    int parent(int i);
    int l_child(int i);
    int r_child(int i);
    void swap(int i , int j);
    void heapify_up(int i);
    void heapify_down(int i);
public:
    Minheap(int w);
    ~Minheap();

    void insert(Huffman_node* node);
    Huffman_node* extract();
    int get_size() const;
    bool is_empty();
};

#endif
