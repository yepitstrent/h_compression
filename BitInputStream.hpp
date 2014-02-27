/********************************************************************
 * Name: Trent Russell
 * ID: a10226136
 * Class: CSE 100 P. Kube, Winter 13
 * Project: P3
 * Date: Feb. 2013
 *
 * Filename: BitInputStream.hpp
 * Description: Header file for BitInputStream.cpp
 *
 *******************************************************************/

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <math.h>

using namespace std;

class BitInputStream
{

private:

  unsigned char buf; // one byte buffer of bits

  int nbits; // how many bits have been written to buf
  int leafNum; //number of leaves in the tree.
  int fileSize;
  queue<int> myQ;
  stack<int> bitStack;


public:

  BitInputStream(std::istream & is);

  void fill();

  int getLeafCount();

  int getBit();

  int getByte();

  int readBit();

  void setSize( int fileByte );

  int getSize();

  int getCharCount();

  std::istream & in;

};

#endif
