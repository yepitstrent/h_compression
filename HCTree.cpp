
/********************************************************************
 * Name: Trent Russell
 * ID: a10226136
 * Class: CSE 100 P. Kube, Winter 13
 * Project: P3
 * Date: Feb. 2013
 *
 * Filename: HCTree.cpp
 * Description: Controller for all the tree methods. 
 *              Decodes and encode
 *
 *******************************************************************/

#include "HCTree.hpp"

using namespace std;

  HCTree::~HCTree()
  {
    clear();
    delete root;
  }

  /** Use the Huffman algorithm to build a Huffman coding trie.
   *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
   *  the frequency of occurrence of byte i in the message.
   *  POSTCONDITION:  root points to the root of the trie,
   *  and leaves[i] points to the leaf node containing byte i.
   */
  void HCTree::build(const vector<int>& freqs, const vector<int>& ascii )
  {

    //////////////////////PUSH NODES ONTO QUEUE//////////////////////
    leaves = vector<HCNode*>(freqs.size(), (HCNode*) 0);

    int i;

    for(i = 0; i < freqs.size(); i++)
    {
      HCNode *currNode = new HCNode(freqs[i], ascii[i], 0,0,0);
      leaves[i] = currNode;
      myPQ.push(currNode);
    }

    //////////////////////MERGE NODES: CHILD PARENT//////////////////

    int num0 = 0;
    int num1 = 0;
    
    //check for myPQ == 0 and size 1
    while( myPQ.size() > 1 )
    {
      HCNode *inputNode = new HCNode( 0, 90, 0, 0, 0 );//


      inputNode->c0 = myPQ.top();

      num0 = inputNode->c0->count;
      inputNode->c0->p = inputNode;

      myPQ.pop();

      inputNode->c1 = myPQ.top();
      num1 = inputNode->c1->count;
      inputNode->c1->p = inputNode;

      myPQ.pop();

      inputNode->count = (num0 + num1);

      myPQ.push( inputNode );
    
    }
    ///////////////////ASSIGN ROOT NODE//////////////////////////////
    if( !myPQ.empty() )
    {
      root = myPQ.top();
    }

  }

  /** Write to the given BitOutputStream
   *  the sequence of bits coding the given symbol.
   *  PRECONDITION: build() has been called, to create the coding
   *  tree, and initialize root pointer and leaves vector.
   */
  void HCTree::encode(byte inputSymbol, BitOutputStream& out)
  {

    HCNode *thisNode = NULL;
    

    std::stack<int> bitStack;

    int i = 0;

    for( i = 0; i < leaves.size(); i++ )
    { 
     
      if( (leaves[i])->symbol == inputSymbol && leaves[i] != NULL)
      { 
       
        thisNode = leaves[ i ];
        
      }
    }
    if( thisNode != NULL )
    {
      bitStack = traverseUp( thisNode );
    }
    while( bitStack.empty() != true )
    {
      out.writeBit( bitStack.top() ); 
      bitStack.pop();
    }

  }

  /** Return symbol coded in the next sequence of bits from the stream.
   *  PRECONDITION: build() has been called, to create the coding
   *  tree, and initialize root pointer and leaves vector.
   */
  unsigned int HCTree::decode(BitInputStream& in) const
  {
    HCNode * currNode = root;
    int bit;
    int i = 0;

    if( root == NULL )
    {
      return 0;
    }
    //cout << "AAAAAAAAAAAAAAAAAAAAAA" << currNode->c0 << endl;

    while (currNode->c0 || currNode->c1 ) 
    {
      bit = in.readBit();
      
      if (bit == 1) 
      {
        currNode = currNode->c1;


      }
      else 
      {
        currNode = currNode->c0;
      }
    }
    
    return (unsigned int)currNode->symbol;   
  }

  /****************************************************************** 
   *  Method used to traverse up the tree. Pushes a 1 or 0 into
   *  the stack.
   *  Returns a stack of 1's or 0's
   *  PRECONDITION: build() has been called, to create the coding
   *****************************************************************/
  stack<int> HCTree::traverseUp( HCNode *leaves )
  {
    std::stack<int> leafStk;

    while( leaves->p != NULL )
    {
      if( leaves->p->c0 == leaves )
      {
        leafStk.push( 0 );
      }
      else
      {
        leafStk.push( 1 );
      }

      leaves = leaves->p;
    }


    return leafStk;

  }


  /******************************************************************
   * Helper method to make a header
   *****************************************************************/
  void HCTree::makeHeader( BitOutputStream &out, int leafNumber, 
                           int totalCount )
  {
    ////////////////////////WRITE HEADER/////////////////////////////

    int bit;
    std::stack<int> bitStk;
    
    //////////////////////PUSH INTO THE STACK////////////////////////
    while( totalCount > 0 )
    {
      bit = totalCount % 2;

      bitStk.push( bit );
      totalCount = totalCount/2;
    }
    ////////////////////////FILL THE EMPTYS W/ 0'S///////////////////
    while( bitStk.size() < 32 )
    {
      bitStk.push(0);
    }
    
    //////////////GET BITS FROM STACK, PUT INTO O STREAM/////////////
    while( !bitStk.empty() )
    {
      out.writeBit( bitStk.top() );

      bitStk.pop();
    }

    //////////////////////LEAF CHECK TO AVOID OVERFLOW///////////////
    if( leafNumber == 256 )
    {
      leafNumber = 0;
    }
    while( leafNumber > 0 )
    {
      bit = leafNumber % 2;

      bitStk.push( bit );
      leafNumber = leafNumber/2;
    }

    while( bitStk.size() < 8 )
    {
      bitStk.push(0);
    }


    while( !bitStk.empty() )
    {
      out.writeBit( bitStk.top() );

      bitStk.pop();
    }

    preorder( root, out );

  }

  /******************************************************************
   * Preorder traversal for build of the tree.
   *****************************************************************/
  void HCTree::preorder( HCNode *writeNode, BitOutputStream &out )
  {

    int charSymbol;
    int bit;
    
    if( writeNode == 0 )
    {
      return;
    }

    ///////////////////CHECK IF LEAF NODE////////////////////////////
    if( writeNode->c0 == NULL && writeNode->c1 == NULL )
    {

      std::stack<int> bitStk;

      ////////////////////////////IS A LEAF//////////////////////////
      out.writeBit(1); 
      charSymbol = writeNode->symbol;

      while( charSymbol > 0 )
      {
        bit = charSymbol % 2;
        bitStk.push(bit);

        charSymbol = charSymbol/2;

      }

      while( bitStk.size() < 8 )
      {
        bitStk.push(0);
      
      }

      while( !bitStk.empty() )
      {
        out.writeBit( bitStk.top() );
        bitStk.pop();
      }

    }
    else/////////////////////////NOT A LEAF//////////////////////////
    {
      out.writeBit(0);
    }

    if( writeNode->c0 != 0 )
    {
      preorder( writeNode->c0, out );
    }

    if( writeNode->c1 != 0 )
    {
      preorder( writeNode->c1, out );
    }
    
  }

  /******************************************************************
   * Rebuild the tree from the header. Calls preorderRebuild()
   *****************************************************************/   
  void HCTree::rebuildTree( BitInputStream &in )
  {
    HCNode *newNode = new HCNode( 0,88,0,0,0 );
    int leavesNum = in.getLeafCount();

    if( leavesNum == 0 )
    {
      leavesNum = 256;
    }

    rebuildCounter = 0;
    leafNumber = leavesNum;

    preorderRebuild( newNode, in );
  }

  /******************************************************************
   * Preorder traversal that reconstructs the tree from the header
   *****************************************************************/
  void HCTree::preorderRebuild(HCNode *currNode, BitInputStream &in)
  {
    int bit;
    int byte;
    if( rebuildCounter >= leafNumber )
    {
      return;
    }
    if( root == NULL )
    {
      root = currNode;
    }
    bit = in.readBit();
    if( bit == 0 )
    {
      HCNode *newNodeC0 = new HCNode( 0,0,0,0,0 );

      preorderRebuild( newNodeC0, in );
      currNode->c0 = newNodeC0;
      newNodeC0->p = currNode;

      HCNode *newNodeC1 = new HCNode( 0,0,0,0,0 );

      preorderRebuild( newNodeC1, in );
      currNode->c1 = newNodeC1;
      newNodeC1->p = currNode;

    }
    else//////////////IS A LEAFNODE, BIT == 1////////////////////////
    {

      byte = in.getByte();
      currNode->symbol = byte;
      rebuildCounter++;
    }
  }

	/******************************************************************
   * Remove all elements from this BST, and destroy them),
 	 *****************************************************************/ 
	void HCTree::clear() 
  {
	  /****************************************************************
     * /////Recusively deleting each node, called from helper fxn////
     ***************************************************************/
    order( root );
    root = NULL;

	} // end clear()


  /******************************************************************
   * Helper function to clear() 
   *****************************************************************/
	void HCTree::order( HCNode *node )
  {
    if(root == NULL)
    {
      return;
    }
	  if( node->c0 != NULL )
  	{
      order( node->c0 );
  	}
  	
	  if( node->c1 != NULL )
  	{
      order( node->c1 );
  	}
    delete node;
  	node = NULL;	

	} // end order





