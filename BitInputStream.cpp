/********************************************************************
 * Name: Trent Russell
 * ID: a10226136
 * Class: CSE 100 P. Kube, Winter 13
 * Project: P3
 * Date: Feb. 2013
 *
 * Filename: BitInputStream.cpp
 * Description: Reads bits and spits them out as chars
 *
 *******************************************************************/

#include "BitInputStream.hpp"

  /** Initialize a BitInputStream that will use
  * the given istream for input.
  */
  BitInputStream::BitInputStream(std::istream & is) : in(is) 
  {
    buf = 0; // clear buffer
    nbits = 0; // initialize bit index
    leafNum = 0;
  }

  /** Fill the buffer from the input */
  void BitInputStream::fill()
  {
    buf = in.get();
    nbits = 8;
  }

  /** Reads the first eight bit from the header and makes an int */
  int BitInputStream::getLeafCount()
  {
    unsigned char c;

    c = in.get();

    leafNum = (int)c;

    
    return leafNum;
  }

  /******************************************************************
   * takes a char and extracts a single bit
   *****************************************************************/
  int BitInputStream::readBit()
  {
    int bitValue;
    if( nbits == 0 )
    {
      fill();
    }
    int mask = 1;
  
    mask = mask << ( nbits -1 );
    bitValue = buf & mask;

    bitValue = bitValue >> ( nbits - 1 );

    nbits--;

    return bitValue;
  }

  int BitInputStream::getBit()
  {
    int i = myQ.front();
    myQ.pop();

    return i;
  }

  /******************************************************************
   * Reads the first 8 values of the queue and converts 
   * them to an int.
   *****************************************************************/
  int BitInputStream::getByte()
  {   
    int byte = 0;
    int bit = 0;
    int count = 0;

    while( count < 8 )
    {
      bit = readBit();
      byte = byte + bit*pow( 2, ( 7 - count ) );
      count++;
    }

    return byte;
  }

  /******************************************************************
   * Set the size of the file in bits so I can do bounds checking.
   *****************************************************************/
  void BitInputStream::setSize( int fileByte )
  {
    fileSize = fileByte * 8;
  }

  int BitInputStream::getSize()
  {
    return fileSize;
  }

  /******************************************************************
   * Gets the number of characters from the header file. 
   * ONLY USE AT THE PROPPER TIME! 
   *****************************************************************/
  int BitInputStream::getCharCount()
  {
    int bytes = 0;
    int bit = 0;
    int count = 0;

    while( count < 32 )
    {
      bit = readBit();

      bytes = bytes + bit*pow( 2, 31 - count );
      count++;
    }

    return bytes;
  }
