/********************************************************************
 * Name: Trent Russell
 * ID: a10226136
 * Class: CSE 100 P. Kube, Winter 13
 * Project: P3
 * Date: Feb. 2013
 *
 * Filename: BitOutputStream.cpp
 * Description: Reads char and spits them out as bits.
 *
 *******************************************************************/

#include "BitOutputStream.hpp"


  /** Initialize a BitOutputStream that will use
   * the given ostream for output.
   */
  BitOutputStream::BitOutputStream(std::ostream & os) : out(os) 
  {
    buf = nbits = 0; // clear buffer and bit counter
  }

  /** Send the buffer to the output, and clear it */
  void BitOutputStream::flush() 
  {
    out << buf;

    buf = 0;
    nbits = 0;
  }

  /** Write the least significant bit of the argument to
   * the bit buffer, and increment the bit buffer index.
   * But flush the buffer first, if it is full.
   */
  void BitOutputStream::writeBit(int i) 
  { 
    //cout << i;//keep this for future decoding

    if( nbits < 8 )
    {

      buf = buf | (i << (7 - nbits) );
      
      nbits++;
    }
    if( nbits == 8 ) 
    {
      flush();
    }
  }



