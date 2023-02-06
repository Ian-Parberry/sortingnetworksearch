/// \file SortingNetwork.cpp
/// \brief Code for the sorting network CSortingNetwork.

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

#include "SortingNetwork.h"

/// Create a binary Gray code generator.

CSortingNetwork::CSortingNetwork(){
  m_pGrayCode = new CBinaryGrayCode;
} //constructor

/// Delete the binary Gray code generator.

CSortingNetwork::~CSortingNetwork(){
  delete m_pGrayCode;
} //destructor

/// Set the values on every channel between two levels to zero.
/// \param firstlayer First level to set to zero.
/// \param lastlayer Last level to set to zero.

void CSortingNetwork::initValues(const size_t firstlayer, const size_t lastlayer){
  for(size_t i=firstlayer; i<=lastlayer; i++) //for each layer in range
    for(size_t j=0; j<INPUTS; j++) //for each channel
      m_nValue[i][j] = 0; //set the value on this channel at that layer to zero
} //initValues

/// Initialize the network for the sorting test, that is, make the
/// Gray code word for input be all zeros, and the values on every channel at
/// every level be zero.

void CSortingNetwork::initSortingTest(){ 
  m_pGrayCode->initalize(); //initialize the Gray code to all zeros.
  initValues(0, DEPTH - 1); //initialize the network values to all zeros.
} //initSortingTest

/// Flip value and propagate down the comparator network.
/// \param j Flip value in this channel.
/// \param firstlayer Flip value at this layer.
/// \param lastlayer Propagate change down to this layer.
/// \return Channel whose value is flipped after the last layer.

size_t CSortingNetwork::flipinput(size_t j, const size_t firstlayer, const size_t lastlayer){
  for(size_t i=firstlayer; i<=lastlayer; i++){ //for each layer in range
    m_nValue[i][j] ^= 1; //flip the value on channel j at that level

    size_t k = m_nMatch[i][j]; //find the channel to which it is joined via a comparator, if any
    
    if((m_nValue[i][k] && j>k) || !(m_nValue[i][k] || j>k))
      j = k;
  } //for

  return j;
} //flipinput

/// Check whether sorting network sorts when the current input has channel flipped.
/// \param delta Index of channel to flip.
/// \return true if it still sorts when channel is flipped.

bool CSortingNetwork::stillsorts(const size_t delta){
  return flipinput(delta - 1, 0, DEPTH - 1) == 
    m_pGrayCode->m_nZeros + m_pGrayCode->m_nBit[delta] - 1;
} //stillsorts

/// Check whether sorting network sorts all inputs.
/// \return true if it sorts.

bool CSortingNetwork::sorts(){ 
  size_t i = 0; //index of bit to flip
  bool bSorts = true; //assume it sorts until we find otherwise
  initSortingTest(); //intialize input and values in comparator network to zero
  while(bSorts && i<=INPUTS){ //bail if it doesn't sort, or we've tried all binary inputs
    i = m_pGrayCode->next(); //next bit to flip in Gray code order
    bSorts = bSorts && (i>INPUTS || stillsorts(i)); //check whether it still sorts when this bit is flipped
  } //while
  return bSorts;
} //sorts