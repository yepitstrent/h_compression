/********************************************************************
 *
 * Name: Trent Russell
 * ID: a10226136
 * Class: CSE 100 P. Kube, Winter 13
 * Project: P3
 * Date: Feb. 2013
 *
 * Filename: uncompress.cpp
 * Description: Decompresses the file you previously compressed with
 *              compress.cpp based on the Huffman Compression Tree.
 *              WORKS WITH ANY FILE!!!!!!!!! I hope...
 *
 *******************************************************************/
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "HCTree.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


using namespace std;

/********************************************************************
 * main method to uncompress
 *******************************************************************/
int main( int argc, char *argv[] )
{
  /////////////////////RE-BUILD THE TREE/////////////////////////////
  cout << "in uncompress" << endl;
  unsigned int c;
  int fileSize = 0;
  int totalChar = 0;
  struct stat filestatus;
  stat( argv[ 1 ], &filestatus ); 

  ////////////////////OPEN THE FILES/////////////////////////////////
  ifstream ifs( argv[1], ifstream::binary );
  ofstream os( argv[2], ofstream::binary );
 
  ////////////////////MAKE A BitInputStream//////////////////////////
  BitInputStream bIS = BitInputStream( ifs );
  
  fileSize = filestatus.st_size;
  
  bIS.setSize( filestatus.st_size );

  //////////////////START TO REBUILD THE TREE////////////////////////
  cout << "building tree" << endl;
  HCTree hTree;
  totalChar = bIS.getCharCount();
  hTree.rebuildTree( bIS );
  cout << "tree built, starting decode" << endl;

  /////////////////////DECODE FILE///////////////////////////////////
  c = hTree.decode(bIS);
  int i = 0;

  ////////////////LOOP THROUGH COMPRESSED BYTES//////////////////////
  while (c >= 0) 
  {
    if( i >= totalChar )
    {
      break;
    }
    if( i < totalChar )
    {
      //os << (byte)c;
      os.put((unsigned char)c);
      c = hTree.decode(bIS);
      i++;
    }
  }

  cout << "tree decodded... enjoy your decompressed file" << endl;
  /////////////////////CLOSE FILES///////////////////////////////////
  os.close();
  ifs.close();

  return 0;
}//end main
