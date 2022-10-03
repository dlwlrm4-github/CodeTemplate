
#include <bits/stdc++.h>
using namespace std;

struct Node
{
public:
    int par;
    int leaf = 0;
    char parChar;
    int link = -1;

    int go[26];
    int edges[26];
    Node(int _par = 0, char _parChar = '$') : par(_par), parChar(_parChar)
    {
        for (int ii = 0; ii < 26; ++ii)
            edges[ii] = go[ii] = -1;
    }
};
vector<Node> Trie;
vector<long long> points;
// add new string. if any transition not possible makes new node.
void addString(string s)
{
    int root = 0;
    for (char ch : s)
    {
        int cur = ch - 'a';
        if (Trie[root].edges[cur] == -1)
        {
            Trie[root].edges[cur] = Trie.size();
            Trie.emplace_back(root, ch);
        }
        root = Trie[root].edges[cur];
    }
    Trie[root].leaf++;
}
// gives you the node with current string ending. Must be in given string or custom the function
int findString(string s)
{
    int root = 0;
    for (char ch : s)
    {
        int cur = ch - 'a';
        root = Trie[root].edges[cur];
    }
    return root;
}

int goLink(int root, char curChar);
// find the suffix / failure link
int findLink(int root)
{
    if (Trie[root].link == -1)
    {
        if (root == 0 || Trie[root].par == 0)
        {
            Trie[root].link = 0;
        }
        else
        {
            Trie[root].link = goLink(findLink(Trie[root].par), Trie[root].parChar);
        }
    }
    return Trie[root].link;
}
// automaton next transition with some character
int goLink(int root, char curChar)
{
    int cur = curChar - 'a';
    if (Trie[root].go[cur] == -1)
    {
        if (Trie[root].edges[cur] != -1)
        {
            Trie[root].go[cur] = Trie[root].edges[cur];
        }
        else
        {
            Trie[root].go[cur] = root == 0 ? 0 : goLink(findLink(root), curChar);
        }
    }
    return Trie[root].go[cur];
}