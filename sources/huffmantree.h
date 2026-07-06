#ifndef huffmantree_h
#define huffmantree_h

#include <string>
#include <fstream>
#include "huffman_node.h"
using namespace std;

class Huffman_tree
{
private:
    Huffman_node *root;
    string ascii[256];
    void make_ascii(Huffman_node *node, string current);
    void delete_tree(Huffman_node *node);
    int print_node(ofstream& out , Huffman_node* node , int& id);
    string label(Huffman_node* node);
public:
    Huffman_tree();
    ~Huffman_tree();
    void build(int number_of_datas[]);
    void make();
    string get_ascii(char c);
    string encode(string& text);
    string decode(string& encoded);
    Huffman_node* get_root();
    void convertor(const string& f_name);
};
#endif
