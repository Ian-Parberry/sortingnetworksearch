/// \file SortingNetwork.cpp
/// \brief Code for the sorting network `CSortingNetwork`.

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
/// \param first First level to set to zero.
/// \param last Last level to set to zero.

void CSortingNetwork::InitValues(const size_t first, const size_t last){
  for(size_t i=first; i<=last; i++) //for each level in range
    for(size_t j=0; j<m_nWidth; j++) //for each channel
      m_nValue[i][j] = 0; //set the value on this channel at that level to zero
} //InitValues

/// Initialize the network for the sorting test, that is, make the
/// Gray code word for input be all zeros, and the values on every channel at
/// every level be zero.

void CSortingNetwork::initialize(){ 
  m_pGrayCode->initialize(); //initialize the Gray code to all zeros.
  InitValues(0, m_nDepth - 1); //initialize the network values to all zeros.
  m_nZeros = m_nWidth - 1; //all zeros
} //initialize

/// Flip value and propagate down the comparator network.
/// \param j Flip value in this channel.
/// \param first Flip value starting at this level.
/// \param last Propagate change down to this level.
/// \return Channel whose value is flipped after the last level.

size_t CSortingNetwork::flipinput(size_t j, const size_t first, const size_t last){
  const size_t nBit = m_nValue[first][j] ^ 1;
  m_nZeros += nBit? -1: 1; //if nBit has flipped to 1, one less zero, else one more
  
  for(size_t i=first; i<=last; i++){ //for each layer in range
    m_nValue[i][j] = nBit; //flip the value on channel j at that level
    const size_t k = m_nMatch[i][j]; //channel joined via a comparator  
    if(xor(m_nValue[i][k], j > k))
      j = k;
  } //for

  return j;
} //flipinput

/// Get target output channel when the value on an input channel is flipped.
/// Assumes that local variable `m_nZeros` is set to the number of zeros in
/// the input before this value is flipped, and that the value in 
/// `m_nValue` has not been flipped yet (that is, `flipinput()`has
/// not been called on that channel yet). If a 1 is to be flipped to a 0, then
/// it should output at channel `m_nZeros`. If a 0 is to be flipped to a 1,
/// then it should output at channel `m_nZeros - 1`.
/// \param delta Index of input channel whose value is to be flipped.
/// \param j Input level.
/// \return Index of output channel whose value is flipped.

const size_t CSortingNetwork::GetTarget(const size_t delta, const size_t j) const{
  size_t nTarget = m_nZeros;

  if(m_nValue[j][delta] == 0) //a zero to be flipped to a 1
    nTarget--;

  return nTarget;
} //GetTarget

/// Check whether sorting network sorts when the current input has channel flipped.
/// \param delta Index of channel to flip.
/// \return true if it still sorts when channel is flipped.

bool CSortingNetwork::stillsorts(const size_t delta){
  const size_t nTarget = GetTarget(delta - 1, 0); //target before flipping
  return flipinput(delta - 1, 0, m_nDepth - 1) == nTarget;
} //stillsorts

/// Check whether sorting network sorts all inputs.
/// \return true if it sorts.

bool CSortingNetwork::sorts(){ 
  size_t i = 0; //index of bit to flip
  bool bSorts = true; //assume it sorts until we find otherwise
  initialize(); //intialize input and values in comparator network to zero

  while(bSorts && i <= m_nWidth){ //bail if it doesn't sort, or we've tried all binary inputs
    i = m_pGrayCode->next(); //next bit to flip in Gray code order
    bSorts = bSorts && (i > m_nWidth || stillsorts(i)); //check whether it still sorts when this bit is flipped
  } //while

  return bSorts;
} //sorts