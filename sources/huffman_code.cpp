#include "huffman_code.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
using namespace std;

Huffman_code::Huffman_code()
{
    reset_number_of_datas();
}

void Huffman_code::reset_number_of_datas()
{
    for (int i = 0; i < 256; i++)
    {
        number_of_data[i] = 0;
    }
}

void Huffman_code::datas_count(string &text)
{
    reset_number_of_datas();

    for (int i = 0; i < (int)text.length(); i++)
    {
        unsigned char c = text[i];
        number_of_data[c]++;
    }
}

string Huffman_code::get_chars(char c)
{
    unsigned char cc = (unsigned char)c;

    if (c == ' ')
    {
        return "space\n";
    }
    else if (c == '\n')
    {
        return "new line\n";
    }
    else if (c == '\t')
    {
        return "Tab\n";
    }
    else if (cc < 32 || cc > 126)
    {
        return "byte " + to_string((int)cc);
    }
    else
    {
        string s = "";
        s += c;
        return s;
    }
}

void Huffman_code::nums_of_data_table()
{
    cout << "===================================== \n";
    cout << "Character Table \n";
    cout << "------------------------------------- \n";
    cout << left << setw(15) << "Character" << "Count" << endl;
    cout << "------------------------------------- \n";
    for (int i = 0; i < 256; i++)
    {
        if (number_of_data[i] > 0)
        {
            cout << left << setw(15) << get_chars((char)i) << number_of_data[i] << endl;
        }
    }
}

void Huffman_code::code_table()
{
    cout << "===================================== \n";
    cout << "Huffman code table \n";
    cout << "------------------------------------- \n";
    cout << left << setw(15) << "Character" << "Huffman Code" << endl;
    cout << "------------------------------------- \n";
    for (int i = 0; i < 256; i++)
    {
        if (number_of_data[i] > 0)
        {
            cout << left << setw(15) << get_chars((char)i) << h.get_ascii((char)i) << endl;
        }
    }
}

void Huffman_code::information_table(int org_size, int compressed)
{
    int compressed_size = (compressed + 7) / 8;
    double ratio = 0;
    if (compressed_size != 0)
    {
        ratio = (double)org_size / compressed_size;
    }

    cout << endl;
    cout << "Compression information \n";
    cout << "------------------------------------- \n";
    cout << "Original Size:     " << org_size << " Bytes \n";
    cout << "Compressed Size:   " << compressed_size << " Bytes \n";
    cout << "Compression Ratio: " << ratio << endl;
}

string Huffman_code::read(string &name)
{
    ifstream file(name , ios::binary);

    if (!file)
    {
        throw Run_Time_Error("Can't open file\n");
    }
    string content = "";
    char c;
    while (file.get(c))
    {
        content += c;
    }
    file.close();
    return content;
}

void Huffman_code::write(string &f_name, string &content)
{
    ofstream file(f_name , ios::binary);
    if (!file)
    {
        throw Run_Time_Error("Cannot open file\n");
    }

    file.write(content.data() , content.size());
    file.close();
}

vector<unsigned char> Huffman_code::bit_to_byte(const string &bit)
{
    vector<unsigned char> bytes;
    int size = (8 - bit.size() % 8) % 8;
    string size_of_bits = bit + string(size, '0');
    for (size_t i = 0; i < size_of_bits.size(); i += 8)
    {
        unsigned char byte = 0;
        for (int j = 0; j < 8; j++)
        {
            byte = (byte << 1) | (size_of_bits[i + j] - '0');
        }
        bytes.push_back(byte);
    }
    return bytes;
}

string Huffman_code::byte_to_bit(vector<unsigned char> &bytes, int count)
{
    string bits;
    bits.reserve(count);
    for (size_t i = 0; i < bytes.size(); i++)
    {
        unsigned char byte = bytes[i];
        for (int j = 7; j >= 0 && bits.size() < (size_t)count; j--)
        {
            if ((byte >> j) & 1)
            {
                bits += '1';
            }
            else
            {
                bits += '0';
            }
        }
    }
    return bits;
}

void Huffman_code::compress(string &input, string &output)
{
    auto start_compress = chrono::high_resolution_clock::now();
    string text = read(input);

    if (text.empty())
    {
        throw Run_Time_Error("Input file is empty\n");
    }

    datas_count(text);
    auto start_tree = chrono::high_resolution_clock::now();
    h.build(number_of_data);
    auto end_tree = chrono::high_resolution_clock::now();
    h.convertor("Huffman_tree.dot");

    string encoded = h.encode(text);
    vector<unsigned char> bytes = bit_to_byte(encoded);

    nums_of_data_table();
    code_table();
    int org_size = (int)text.length();
    int compressed = (int)encoded.length();

    ofstream out(output, ios::binary);
    if (!out)
    {
        throw Run_Time_Error("Cannot write to output file\n");
    }

    int count = 0;
    for (int i = 0; i < 256; i++)
    {
        if (number_of_data[i] > 0)
        {
            count++;
        }
    }

    out << count << '\n';
    for (int i = 0; i < 256; i++)
    {
        if (number_of_data[i] > 0)
        {
            out << i << ' ' << number_of_data[i] << '\n';
        }
    }
    out << encoded.length() << "\nDATA\n";

    out.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
    out.close();
    auto end_compress = chrono::high_resolution_clock::now();
    information_table(org_size, compressed);
    chrono::duration<double> build_tree = end_tree - start_tree;
    cout << "Time for build tree: " << build_tree.count() << " seconds" << endl;
    chrono::duration<double> compress_time = end_compress - start_compress;
    cout << "Compress time is: " << compress_time.count() << " seconds" << endl;
    cout << "\nFile compressed succesfully to: " << output << endl;
}

void Huffman_code::decompress(string &input, string &output)
{
    auto start_decompress = chrono::high_resolution_clock::now();
    reset_number_of_datas();
    ifstream in(input, ios::binary);

    if (!in)
    {
        throw Run_Time_Error("Cannot open file\n");
    }

    int count;

    if (!(in >> count))
    {
        return;
    }

    for (int i = 0; i < count; i++)
    {
        int ascii;
        int num;
        in >> ascii >> num;
        number_of_data[ascii] = num;
    }

    long long bit_count;

    if (!(in >> bit_count))
    {
        return;
    }

    string mark;
    in >> mark;

    if (mark != "DATA")
    {
        throw Run_Time_Error("Invalid format \n");
    }

    char line;
    in.get(line);

    vector<unsigned char> bytes;
    char c;
    while (in.read(&c, 1))
    {
        bytes.push_back((unsigned char)c);
    }

    in.close();
    string encoded = byte_to_bit(bytes, (int)bit_count);

    auto start_tree = chrono::high_resolution_clock::now();
    h.build(number_of_data);
    auto end_tree = chrono::high_resolution_clock::now();

    if (encoded.empty() && bit_count > 0)
    {
        throw Run_Time_Error("Encoded is empty \n");
    }

    h.make();
    string decoded = h.decode(encoded);
    write(output, decoded);
    auto end_decompress = chrono::high_resolution_clock::now();
    chrono::duration<double> build_tree = end_tree - start_tree;
    cout << "Time for build tree is: " << build_tree.count() << " seconds" << endl;
    chrono::duration<double> decompress_time = end_decompress - start_decompress;
    cout << "Decompress Time is: " << decompress_time.count() << " seconds" << endl;
    cout << "File decompressed successfully \n";
}
