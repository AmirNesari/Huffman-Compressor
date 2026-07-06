#include "minheap.h"
#include "huffmantree.h"
#include "huffman_node.h"

Huffman_tree::Huffman_tree()
{
    root = NULL;

    for (int i = 0; i < 256; i++)
    {
        ascii[i] = "";
    }
}

Huffman_tree::~Huffman_tree()
{
    delete_tree(root);
}

void Huffman_tree::delete_tree(Huffman_node *node)
{
    if (node == NULL)
    {
        return;
    }
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

void Huffman_tree::build(int number_of_datas[])
{
    if (root != NULL)
    {
        delete_tree(root);
        root = NULL;
    }

    for (int i = 0; i < 256; i++)
    {
        ascii[i] = "";
    }

    int count = 0;

    for (int i = 0; i < 256; i++)
    {
        if (number_of_datas[i] > 0)
        {
            count++;
        }
    }

    if (count == 0)
    {
        throw Run_Time_Error("No data to build tree\n");
    }

    Minheap min(count * 2);

    for (int i = 0; i < 256; i++)
    {
        if (number_of_datas[i] > 0)
        {
            char ch = (char)i;
            Huffman_node *node = new Huffman_node(ch, number_of_datas[i]);
            min.insert(node);
        }
    }

    while (min.get_size() > 1)
    {
        Huffman_node *left = min.extract();
        Huffman_node *right = min.extract();

        int l_r_sum = left->number_of_data + right->number_of_data;
        Huffman_node *parent = new Huffman_node('\0', l_r_sum, left, right);
        min.insert(parent);
    }
    root = min.extract();
    make();
}

void Huffman_tree::make()
{
    for (int i = 0; i < 256; i++)
    {
        ascii[i] = "";
    }
    if (root == NULL)
    {
        return;
    }
    if (root->leaf())
    {
        ascii[(unsigned char)root->data] = "0";
        return;
    }

    make_ascii(root, "");
}

void Huffman_tree::make_ascii(Huffman_node *node, string current)
{
    if (node == NULL)
    {
        return;
    }
    if (node->leaf())
    {
        ascii[(unsigned char)node->data] = current;
        return;
    }
    make_ascii(node->left, current + "0");
    make_ascii(node->right, current + "1");
}

string Huffman_tree::get_ascii(char c)
{
    int i = (unsigned char)c;
    return ascii[i];
}

string Huffman_tree::encode(string &text)
{
    if (root == NULL)
    {
        throw Run_Time_Error("Huffman Tree is empty\n");
    }

    string encoded = "";
    for (int i = 0; i < (int)text.length(); i++)
    {
        unsigned char c = text[i];
        if (ascii[c].empty())
        {
            throw Run_Time_Error("Character not in Huffman tree\n");
        }
        encoded += ascii[c];
    }
    return encoded;
}

string Huffman_tree::decode(string &encoded)
{
    if (root == NULL)
    {
        throw Run_Time_Error("Huffman Tree is empty\n");
    }

    string decoded = "";

    if (root->leaf())
    {
        for (int i = 0; i < (int)encoded.length(); i++)
        {
            decoded += root->data;
        }
        return decoded;
    }

    Huffman_node *current = root;

    for (int i = 0; i < (int)encoded.length(); i++)
    {
        char node = encoded[i];

        if (node == '0')
        {
            current = current->left;
        }
        else if (node == '1')
        {
            current = current->right;
        }
        else
        {
            throw Run_Time_Error("Invalid character in encoded text\n");
        }

        if (current == NULL)
        {
            throw Run_Time_Error("Invalid encoded data: null node reached\n");
        }
        if (current->leaf())
        {
            decoded += current->data;
            current = root;
        }
    }

    if (current != root)
    {
        throw Run_Time_Error("Encoded data ended mid-path (incomplete code)\n");
    }
    return decoded;
}

Huffman_node *Huffman_tree::get_root()
{
    return root;
}

string Huffman_tree::label(Huffman_node *node)
{
    if (node == NULL)
    {
        return "";
    }

    string label = "";

    if (node->left == NULL && node->right == NULL)
    {
        unsigned char c = node->data;

        if (c == ' ')
        {
            label = "space";
        }
        else if (c == '\n')
        {
            label = "\\n";
        }
        else if (c == '\t')
        {
            label = "\\t";
        }
        else if (c < 32 || c > 126)
        {
            label = "byte " + to_string((int)c);
        }
        else
        {
            label += node->data;
        }
        label += "\\nnum: " + to_string(node->number_of_data);
    }
    else
    {
        label = "num: " + to_string(node->number_of_data);
    }
    return label;
}

void Huffman_tree::convertor(const string &f_name)
{
    ofstream out(f_name);

    if (!out)
    {
        throw Run_Time_Error("Can't creat file \n");
    }
    out << "digraph HuffmanTree {\n";
    out << "    bgcolor=\"black\";\n";
    out << "    node [shape=circle, style=filled, fillcolor=\"#00FF00\", color=\"#00FF00\", fontcolor=\"white\", fontname=\"Arial-Bold\"];\n";
    out << "    edge [color=\"#00FF00\", penwidth=2, fontcolor=\"white\", fontname=\"Arial\"];\n\n";

    int id = 0;

    if (root == NULL)
    {
        out << "empty [label=\"Empty Tree\"];\n";
    }
    else
    {
        print_node(out, root, id);
    }
    out << "}\n";
    out.close();
}

int Huffman_tree::print_node(ofstream &out, Huffman_node *node, int &id)
{
    if (node == NULL)
    {
        return -1;
    }

    int current = id;
    id++;
    out << "    node" << current << " [label=\"" << label(node) << "\"];\n";
    if (node->left != NULL)
    {
        int l_id = print_node(out, node->left, id);
        out << "    node" << current << " -> node" << l_id << " [label=\"0\"];\n";
    }

    if (node->right != NULL)
    {
        int r_id = print_node(out, node->right, id);
        out << "    node" << current << " -> node" << r_id << " [label=\"1\"];\n";
    }
    return current;
}