/// \file SortingNetwork1NF.cpp
/// \brief Code for the first normal form sorting network C1NFSortingNetwork.

// MIT License
//
// Copyright (c) 2023 Ian Parberry
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include "Defines.h"
#include "TernaryGrayCode.h"

#include "SortingNetwork1NF.h"

/// Create a ternary Gray code generator and set the first layer to the
/// identity matching, which places comparators between channels 0 and 1,
/// 2 and 3, 4 and 5, etc.

C1NFSortingNetwork::C1NFSortingNetwork(){
  m_pGrayCode = new CTernaryGrayCode;

  //n is the largest even number no greater than the number of inputs
  const size_t n = INPUTS - (INPUTS & 1); 

  //first layer is the identity matching

  for(size_t i=0; i<n; i++)
    m_nMatch[0][i] = i ^ 1;
} //constructor

/// Initialize the network for the sorting test, that is, make the Gray code
/// word for input be all zeros, and the values on every channel at every level
/// be zero.

void C1NFSortingNetwork::initSortingTest(){ 
  m_pGrayCode->initalize(); //initialize the Gray code to all zeros.
  initValues(1, DEPTH - 1); //initialize the network values to all zeros.
} //initSortingTest

/// Check that sorting network sorts when the current input has channel flipped.
/// \param delta Index of channel to flip.
/// \return true if it still sorts when channel is flipped.

bool C1NFSortingNetwork::stillsorts(const size_t delta){
  return flipinput(delta - 1, 1, DEPTH - 1) ==
    m_pGrayCode->m_nZeros + m_pGrayCode->m_nBit[delta] - 1;
} //stillsorts

/// Check whether sorting network sorts all inputs. Works for even number of
/// channels, and for odd number of channels it doesn't change the last input.
/// The difference between this and `CSortingNetwork::sorts()` is that this 
/// version does not call `initSortingTest()`, which means that the value on any
/// hypothetical last even-numbered channel will not be changed.
/// \return true iff it sorts

bool C1NFSortingNetwork::evensorts(){ 
  size_t i = 0;  //index of bit to flip
  bool bSorts = true; //assume it sorts until we find otherwise

  while(bSorts && i<=INPUTS){ //bail if it doesn't sort, or we've tried all binary inputs
    i = m_pGrayCode->next(); //next bit to flip in Gray code order
    bSorts = bSorts && (i>INPUTS || stillsorts(i)); //check whether it still sorts when this bit is flipped
  } //while
  return bSorts;
} //sorts

/// Check whether sorting network sorts all inputs. Works for both odd and even
/// number of channels. The difference between this and `CSortingNetwork::sorts()`
/// is that this version has to handle any hypothetical last even-numbered
/// channel separately, testing it first with value zero then with value 1.
/// \return true iff it sorts

bool C1NFSortingNetwork::sorts(){ 
  //first handle the case where n is even, and the case where n is odd
  //and fails to sort an input that ends with a zero
  initSortingTest(); //set all channels to zero
  if(!evensorts())return false;  //test inputs ending in zero

  //if odd number of inputs, check input that end with a one 
  if(odd(INPUTS)){   
    initSortingTest(); //set all channels to zero

    for(int j=0; j<DEPTH; j++) //set all values on last channel to one
      m_nValue[j][INPUTS - 1] = 1;

    m_pGrayCode->m_nZeros = INPUTS - 1; //correct the count of zeros

    if(!evensorts())return false; //test inputs ending with one
  } //if

  return true; //Oh, we made it this far? Then I must be a sorting network. Hurray!
} //sorts
