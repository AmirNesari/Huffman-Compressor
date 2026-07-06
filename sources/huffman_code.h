#ifndef Huffman_code_h
#define Huffman_code_h

#include <string>
#include <vector>
#include "huffmantree.h"

class Huffman_code
{
private:
    int number_of_data[256];
    Huffman_tree h;
    void reset_number_of_datas();
    void datas_count(string& text);
    string get_chars(char c);
    void nums_of_data_table();
    void code_table();
    void information_table(int org_size, int compressed);
    string read(string& name);
    void write(string& f_name, string& content);

public:
    Huffman_code();
    vector <unsigned char> bit_to_byte(const string& bit);
    string byte_to_bit(vector <unsigned char> &bytes , int count);
    void compress(string& input, string& output);
    void decompress(string& input, string& output);
};
#endif
