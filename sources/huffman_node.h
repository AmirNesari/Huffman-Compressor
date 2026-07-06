#ifndef huffman_node_h
#define huffman_node_h
#include <cstddef>
#include <stdexcept>
#include <string>

class Run_Time_Error : public std::runtime_error {
public:
    Run_Time_Error(const std::string& msg) : std::runtime_error(msg) {}
};

class Huffman_node
{
public:
    char data;
    int number_of_data;
    Huffman_node *left;
    Huffman_node *right;
    Huffman_node(char d, int n)
        : data(d), number_of_data(n), left(NULL), right(NULL) {}
    Huffman_node(char d, int n, Huffman_node *l, Huffman_node *r)
        : data(d), number_of_data(n), left(l), right(r) {}
    bool leaf() const
    {
        return left == NULL && right == NULL;
    }
};
#endif
