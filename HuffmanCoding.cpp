/*
Naman Madharia

Prefix Codes, means the codes (bit sequences) are assigned in such a way that the code
assigned to one character is not the prefix of code assigned to any other character. 
This is how Huffman Coding makes sure that there is no ambiguity when decoding the 
generated bitstream.
*/
#include<bits/stdc++.h>


typedef long long lld;
typedef unsigned long long llu;
using namespace std;

string str;
map<char, double> P;

// Tree
struct HuffTreeNode
{
    double p;
    bool leaf;
    char letter;
    
    HuffTreeNode *parent;
    HuffTreeNode *l;
    HuffTreeNode *r;
    
    // nonleaf node
    HuffTreeNode(double p, HuffTreeNode *l, HuffTreeNode *r)
    {
        this -> p = p;
        this -> leaf = false;
        this -> letter = '\0';
        
        this -> parent = NULL;
        this -> l = l;
        this -> r = r;
        l -> parent = this;
        r -> parent = this;
    }
    
    // leaf node
    HuffTreeNode(double p, char c)
    {
        this -> p = p;
        this -> leaf = true;
        this -> letter = c;
        this -> parent = this -> l = this -> r = NULL;
    }
};

// Comparator of two node pointers
struct CmpNodePtrs
{
    bool operator()(const HuffTreeNode* lhs, const HuffTreeNode* rhs) const
    {
        return (lhs -> p) > (rhs -> p);
    }
};

// the root of the tree
HuffTreeNode *root;

// mapping each character to its leaf node (for quick encoding)
map<char, HuffTreeNode*> leaf;

// Produces the probability distribution (may be omitted if known in advance)
inline void analyse()
{
    for (int i=0;i<str.length();i++)
    {
        P[str[i]]++;
    }
    for (auto it = P.begin();it!=P.end();it++)
    {
        P[it -> first] = it -> second / str.length();
    }
}

// Construct the Huffman Tree using the probability distribution
inline void build_tree()
{
    priority_queue<HuffTreeNode*, vector<HuffTreeNode*>, CmpNodePtrs> pq;
    
    // First construct the leaves, and fill the priority queue
    for (auto it = P.begin();it!=P.end();it++)
    {
        leaf[it -> first] = new HuffTreeNode(it -> second, it -> first);
        pq.push(leaf[it -> first]);
    }
    
    while (pq.size() > 1)
    {
        HuffTreeNode* L = pq.top(); pq.pop();
        HuffTreeNode* R = pq.top(); pq.pop();
        
        // Spawn a new node generating the children
        HuffTreeNode* par = new HuffTreeNode((L -> p) + (R -> p), L, R);
        pq.push(par);
    }
    
    root = pq.top(); pq.pop();
}

// Huffman-encode a given character
inline string encode(char c)
{
    string ret = "";
    
    HuffTreeNode* curr = leaf[c];
    while (curr -> parent != NULL)
    {
        if (curr == curr -> parent -> l) ret += "0";
        else if (curr == curr -> parent -> r) ret += "1";
        
        curr = curr -> parent;
    }
    
    reverse(ret.begin(), ret.end());
    return ret;
}

// Huffman-encode the given string
inline string encode(string s)
{
    string ret = "";
    
    for (int i=0;i<s.length();i++)
    {
        ret += encode(s[i]);
    }
    
    return ret;
}

// Huffman-decode the given string
inline string decode(string s)
{
    string ret = "";
    
    int i = 0;
    HuffTreeNode* curr;
    
    while (i < s.length())
    {
        curr = root;
        while (!(curr -> leaf))
        {
            if (s[i++] == '0') curr = curr -> l;
            else curr = curr -> r;
        }
        ret += curr -> letter;
    }
    return ret;
}

int main()
{
    str = " abcdefghijklmnopqrstuvwxyz";
    
    analyse();
    build_tree();
    
    string test = " abcdefijmostu";

    for (int i=0;i<test.length();i++)
    {
        cout << "Encode(" << test[i] << ") = " << encode(test[i]) << endl;
    }
    
   string enc=encode("this is from daa subject");
   string dec=decode(enc);
   cout<< "\nEncoded-> "<<enc<<"\nDecoded-> "<<dec<<"\n";
   //cout << decode("10010110100000101111000001011110111100100111110100110") << endl;
     
    return 0;
}

/*
----------------------------------------OUTPUT---------------------------------------------


Encode( ) = 01010
Encode(a) = 0000
Encode(b) = 01011
Encode(c) = 10111
Encode(d) = 0001
Encode(e) = 11001
Encode(f) = 11010
Encode(i) = 0010
Encode(j) = 11110
Encode(m) = 10010
Encode(o) = 01111
Encode(s) = 11101
Encode(t) = 11100
Encode(u) = 10101

Encoded-> 1110001110001011101010100010111010101011010111110111110010010100001000000000101011101101010101111110110011011111100
Decoded-> this is from daa subject



*/
