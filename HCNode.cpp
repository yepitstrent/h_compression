/********************************************************************
 * Name: Trent Russell
 * ID: a10226136
 * Class: CSE 100 P. Kube, Winter 13
 * Project: P3
 * Date: Feb. 2013
 *
 * Filename: HCNode.cpp
 * Description: Overloads the < operator
 *
 *******************************************************************/

#include "HCNode.hpp"


bool HCNode::operator<(const HCNode& other)
{
  return other.count <= this->count;
}

/**
 * So we have found that to be useful for both coding and decoding, a node in a Huffman
 * code tree should have:
 *
 * a pointer to its parent (which will be null, if it is the root of the tree)
 *
 * some way to tell whether this is the ¿0¿ or ¿1¿ child of its parent
 *
 * a pointer to its 0 child and its ¿1¿ child (which will both be null, if it is a leaf)
 *
 * the value of the alphabet symbol (if it is a leaf)
 */

