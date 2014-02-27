/********************************************************************
 * Name: Trent Russell
 * ID: a10226136
 * Class: CSE 100 P. Kube, Winter 13
 * Project: P3
 * Date: Feb. 2013
 *
 * Filename:
 * Description:
 *
 *******************************************************************/


#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp 
{

public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const 
    {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree 
{
private:
    vector<HCNode*> leaves;

public:
    int rebuildCounter;
    int leafNumber;

    HCNode* root;

    std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> myPQ;

    //std::queue<int> myQ;

    explicit HCTree() : root(0) 
    {
       // leaves = vector<HCNode*>(256, (HCNode*) 0);
    }

    ~HCTree();

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs, const vector<int>& ascii);

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream &out);

    stack<int> traverseUp( HCNode *leaves );

    void makeHeader( BitOutputStream &out, int leafNumber, int totalCount );

    //void makeTree( BitOutputStream &out );

    void preorder( HCNode *writeNode, BitOutputStream &out );

    void preorderRebuild( HCNode *currNode, BitInputStream &in );

    void rebuildTree( BitInputStream &in );

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    unsigned int decode(BitInputStream& in) const;

    void order( HCNode *node );

    void clear();

};

#endif // HCTREE_HPP
