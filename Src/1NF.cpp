/// \file 1NF.cpp
/// \brief Code for the first normal form sorting network `C1NF`.

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

#include "1NF.h"

/// Create a ternary Gray code generator and set the first layer to the
/// identity matching, which places comparators between channels 0 and 1,
/// 2 and 3, 4 and 5, etc.

C1NF::C1NF(): CSortingNetwork(){
  delete m_pGrayCode;
  m_pGrayCode = new CTernaryGrayCode;


  //first layer is the identity matching

#ifdef NEWMATCHING
  m_cComparator[0].MakeIdentity();
#else
  const size_t n = evenfloor(m_nWidth); 

  for(size_t i=0; i<n; i++)
    m_nComparator[0][i] = i ^ 1;
#endif

} //constructor

/// Initialize the network for the sorting test, that is, make the Gray code
/// word for input be all zeros, and the values on every channel at every level
/// be zero.

void C1NF::Initialize(){ 
  m_pGrayCode->Initialize(); //initialize the Gray code to all zeros.
  InitValues(1, m_nDepth - 1); //initialize the network values to all zeros.
  m_nZeros = m_nWidth; //all zeros
} //initialize

/// Check that sorting network sorts when the current input has channel flipped.
/// \param delta Index of channel to flip.
/// \return true if it still sorts when channel is flipped.

bool C1NF::StillSorts(const size_t delta){
  const size_t nTarget = m_nValue[1][delta]? m_nZeros: m_nZeros - 1;
  return FlipInput(delta, 1, m_nDepth - 1) == nTarget;
} //StillSorts

/// Check whether sorting network sorts all inputs. Works for even number of
/// channels, and for odd number of channels it doesn't change the last input.
/// The difference between this and `CSortingNetwork::sorts()` is that this 
/// version does not call `Initialize()`, which means that the value on any
/// hypothetical last even-numbered channel will not be changed.
/// \return true iff it sorts

bool C1NF::EvenSorts(){ 
  size_t i = 0;  //index of bit to flip
  bool bSorts = true; //assume it sorts until we find otherwise

  while(bSorts && i < m_nWidth){ //bail if it doesn't sort, or we've tried all binary inputs
    i = m_pGrayCode->Next(); //next bit to flip in Gray code order
    bSorts = bSorts && (i >= m_nWidth || StillSorts(i)); //check whether it still sorts when this bit is flipped
  } //while

  return bSorts;
} //EvenSorts

/// Check whether sorting network sorts all inputs. Works for both odd and even
/// number of channels. The difference between this and `CSortingNetwork::sorts()`
/// is that this version has to handle any hypothetical last even-numbered
/// channel separately, testing it first with value zero then with value 1.
/// \return true iff it sorts

bool C1NF::Sorts(){ 
  //first handle the case where n is even, and the case where n is odd
  //and fails to sort an input that ends with a zero
  Initialize(); //set all channels to zero
  if(!EvenSorts())return false;  //test inputs ending in zero

  //if odd number of inputs, check input that end with a one 
  if(odd(m_nWidth)){   
    Initialize(); //set all channels to zero

    for(int j=0; j<m_nDepth; j++) //set all values on last channel to one
      m_nValue[j][m_nWidth - 1] = 1;

    m_nZeros = m_nWidth - 1; //correct the count of zeros

    if(!EvenSorts())return false; //test inputs ending with one
  } //if

  return true; //Oh, we made it this far? Then I must be a sorting network. Hurray!
} //sorts
