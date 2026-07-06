#include <iostream>
#include <string>
#include "huffman_code.h"
using namespace std;
int main()
{
    cout << "==========Huffman Compressor========== \n";
    Huffman_code huffman;
    int number;
    string input;
    string output;
    while (true)
    {
        cout << "1.Compressor \n";
        cout << "2.Decompressor \n";
        cout << "3.exit \n";
        cout << "Enter your number: \n";
        cin >> number;
        if (number == 1)
        {
            cout << "Enter input file name: \n";
            cin >> input;
            cout << "Enter output file name: \n";
            cin >> output;
            if (output.size() < 5 || output.substr(output.size() - 5) != ".huff")
            {
                output += ".huff";
            }
            try
            {
                huffman.compress(input, output);
            }
            catch (exception &e)
            {
                cout << "Error is: " << e.what() << endl;
            }
        }
        else if (number == 2)
        {
            cout << "Enter compressed file name: \n";
            cin >> input;
            cout << "Enter decompressed file name: \n";
            cin >> output;
            try
            {
                huffman.decompress(input , output);
            }
            catch (exception &e)
            {
                cout << "Error is: " << e.what() << endl;
            }
        }
        else if (number == 3)
        {
            cout << "program ended, \n";
            break;
        }
        else
        {
            cout << "Invalid number!!! \n";
        }
        cout << endl;
    }
    return 0;
}