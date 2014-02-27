/********************************************************************
 * Name: Trent Russell
 * ID: a10226136
 * Class: CSE 100 P. Kube, Winter 13
 * Project: P3
 * Date: Feb. 2013
 *
 * Filename: BitOutputStream.hpp
 * Description: Header file for BitOutputStream.cpp
 *
 *******************************************************************/

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BitOutputStream
{

private:

  unsigned char buf; // one byte buffer of bits
  int nbits; // how many bits have been written to buf

public:

  BitOutputStream(std::ostream &out);

  void flush();

  void writeBit(int i);

  std::ostream &out;

};

#endif //BITOUTPUTSTREAM_HPP

