/********************************************************************
 * Name: Trent Russell
 * ID: a10226136
 * Class: CSE 100 P. Kube, Winter 13
 * Project: P3
 * Date: Feb. 2013
 *
 * Filename: compress.cpp
 * Description: Takes input from the commandline and compresses a 
 *              file. It saves it to the specified file.
 *
 *******************************************************************/


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "HCTree.hpp"

using namespace std;

/********************************************************************
 * main method to compress
 *******************************************************************/
int main(int argc, char *argv[] )
{

  /////////////////CHECK: TOO FEW FILES ENTERED//////////////////////
  if( argc < 3 )
  {
    cout<< "Too few files listed in commandline: ERROR" << 
           " \nPlease enter: ./compress inputfile outputfile "<< endl;
    return -1;
  }

  //////////////////////SOME STUFF USED??////////////////////////////
  unsigned char c;
  int leafCounter = 0;
  int totalChar = 0;

  vector<int> charCount( 256, 0 );
  ifstream ifs( argv[1], ifstream::binary );
  ofstream os( argv[2], ofstream::binary );
  
  //////////////////////NULL CHECK///////////////////////////////////
  if( ifs == NULL )
  {
    return 0;
  }

  ///////////////////////CHAR COUNT//////////////////////////////////
  int i;

  //////////////////LOOP TILL END OF FILE////////////////////////////
  c = (char)ifs.get();

  while( ifs.good() )
  {
    for( i = 0; i < 256; i++)
    {
      if( c == ( unsigned char)i )
      {
        totalChar++;
        charCount[i] = charCount[i] + 1;
      }
    }
    c = (unsigned char)ifs.get();
  }

  /******************************************************************
   * close this file because I need
   * to open it again from the start
   *****************************************************************/
  ifs.close(); 

  ////////////////////////SET LEAF COUNT/////////////////////////////
  for( i = 0; i < 256; i++ )
  {
    if( charCount[i] != 0 )
    {
      leafCounter++;
    }
  }

  /******************************************************************
   * Optimized vectors for frequency and ascii numbers
   ******************************************************************/
  vector<int> leafNodeVector(leafCounter, 0);
  vector<int> leafASCII( leafCounter, 0 );
  int j = 0;
  
  for( i = 0; i < 256; i++ )
  {
    if( charCount[i] != 0 )
    {
      leafNodeVector[j] = charCount[i];
      leafASCII[j] = i;
      j++;
    }
  }
  cout << "Welcome to my Huffman Compression: " << endl;
  /////////////////////////////BUILD TREE////////////////////////////
  cout << "Building tree...  " << endl;
  
  HCTree hTree;
  hTree.build( leafNodeVector, leafASCII );

  cout << "Sucessful tree built" << endl;
  ///////////////////////////WRITING BETTER HEADER///////////////////
  BitOutputStream bOS = BitOutputStream(os);
  hTree.makeHeader( bOS, leafCounter, totalChar );

  /////////////////////////////COMPRESS FILE/////////////////////////
  ifstream ifsComp( argv[1], ifstream::in );
  
  i = 0;
  cout << "Starting encodeing..." << endl;
  int counter = 0;
  while( ifsComp.good() )
  {
    c = ( unsigned char)ifsComp.get();
   
    hTree.encode( c, bOS  );
  }
  cout<< "File encoded, done" << endl;
  cout << "Use the uncompressor to decode.  " << endl;
  bOS.flush();
  /////////////////////////////END////////////////////////////////////
  os.close();
  ifsComp.close();

  return 0;
}
