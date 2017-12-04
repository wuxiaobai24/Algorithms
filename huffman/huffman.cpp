#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <sstream>
#include <queue>
#include <bitset>
#include <map>
using namespace std;

int count[256];
map<char,string> code;

void readFromFile(const string& filename,string &contents) {
    ifstream fin;
    fin.open(filename,ios::in);
    contents = string(istreambuf_iterator<char>(fin),
                        istreambuf_iterator<char>());
}

void calcCount(const string &contents) {
    for(auto c:contents)
        count[c]++;
}

class HuffmanTreeNode{
public:
    int weight;
    char data;
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;

    HuffmanTreeNode(HuffmanTreeNode *l,HuffmanTreeNode *r,char d ='\0')
        :left(l),right(r),weight(l->weight + r->weight),data(d){}
    HuffmanTreeNode(int w,char d):weight(w),data(d),left(nullptr),right(nullptr){}
    ~HuffmanTreeNode(){}
};

void pack(HuffmanTreeNode *root,ofstream &fout) {
    if (root == nullptr) {
        fout << endl;
        return ;
    }
    fout << root->weight <<" "<< root->data << endl;
    pack(root->left,fout);
    pack(root->right,fout);
}

HuffmanTreeNode *unpack(ifstream &fin) {
    string line;
    if (!getline(fin,line)) {
        cerr<<"unpack"<<endl;
        exit(1);
    }
    if (line.size() == 0) return nullptr;
    istringstream iss(line);
    auto root = new HuffmanTreeNode(0,' ');
    iss >> root->weight >> root->data;
    cout << root->weight << root->data << endl;
    root->left = unpack(fin);
    root->right = unpack(fin);
    return root;
}


HuffmanTreeNode* bulidHuffmanTree() {
    auto cmp = [](HuffmanTreeNode *p1,HuffmanTreeNode *p2) {
        return p1->weight > p2->weight;
    };
    priority_queue<HuffmanTreeNode*,
        vector<HuffmanTreeNode*>,
        decltype(cmp)> pqueue(cmp);

    for(int i = 0;i < 256;i++) {
        if (count[i] != 0) pqueue.push(new HuffmanTreeNode(count[i],(char)i));
    }

    while(pqueue.size() > 1) {
        auto p1 = pqueue.top(); pqueue.pop();
        auto p2 = pqueue.top(); pqueue.pop();
        pqueue.push(new HuffmanTreeNode(p1,p2));
    }
    return pqueue.top();
}

void genHuffmanCode(HuffmanTreeNode *root,string &str) {
    if (root == nullptr) return ;
    else if (!root->left && !root->right) {
        code[root->data] = str;
        return ;
    } 
    str.push_back('0');
    genHuffmanCode(root->left,str);
    *str.rbegin() = '1';
    genHuffmanCode(root->right,str);
    str.pop_back();
}

void encode(const string& infile,const string& outfile) {
    ofstream fhelp("help.huffman");
    ofstream fout(outfile,ios::binary);
    ifstream fin(infile); 
    string contents;
    readFromFile(infile,contents);
    calcCount(contents);
    auto root = bulidHuffmanTree();
    
    //先将huffman code 写入outfil
    fhelp << contents.size() << endl;
    pack(root,fhelp);
    string str;
    genHuffmanCode(root,str);
    //进行压缩
    char ch;
    char buffer;
    int k = 0;
    int count = 0,byte = 0;
    while(fin >> ch) {
        const string &str = code[ch];
        count += str.size();
        for(auto c:str) {
            if (c == 1) buffer | 1;
            buffer << 1;
            k = (k + 1) % 8;
            if (!k) {
                fout.write(&buffer,sizeof(char));
                byte += 1;
            }
        }
    }
    buffer << (8 - k);
    fout.write(&buffer,sizeof(char));
    cout << count << " " << byte << endl;
    fhelp.close(); fin.close(); fout.close();
}

int mask[8] = {1,2,4,16,32,64,128,256};

void decode(const string& infile,const string &outfile) {
    ifstream fin(infile,ios::binary);
    ofstream fout(outfile);
    ifstream fhelp("./help.huffman");
    int contents_size;
    string str; getline(fhelp,str);
    istringstream iss(str);
    iss >> contents_size;
    cout << contents_size << endl;
    auto root = unpack(fhelp);
    char buffer;
    char c;
    int k = 0;
    HuffmanTreeNode *p = root;
    while( fin.read(&buffer,sizeof(char)) ) {
        do {
            if (p->left == nullptr &&  p->right == nullptr) {
     //           cout << p->data;
                fout << p->data;
                p = root;
                contents_size--;
                if (contents_size == 0) break;
            }
            if (mask[k] & buffer) p = p->right;
            else p = p->left;
            k = (k + 1) % 8;
        } while(k != 0);
    }
}

int main (int argc,char **argv) {
    if (argc < 4) {
        exit(1);
    }
    if (string(argv[1]) == "-enc") {
        encode(string(argv[2]),string(argv[3]));
    } else if(string(argv[1]) == "-dec") {
        decode(string(argv[2]),string(argv[3]));
    } else {
        ;
    }
}
