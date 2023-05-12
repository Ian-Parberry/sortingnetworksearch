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

CSortingNetwork::CSortingNetwork(): CComparatorNetwork(){
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

void CSortingNetwork::Initialize(){ 
  m_pGrayCode->Initialize(); //initialize the Gray code to all zeros.
  InitValues(0, m_nDepth - 1); //initialize the network values to all zeros.
  m_nZeros = m_nWidth - 1; //all zeros
} //initialize

/// Flip bit and propagate down the comparator network. Note that when a
/// bit is flipped at a certain level, exactly one bit is changed at subsequent
/// levels following a path to the outputs. An example is shown in the following
/// figure.
/// \image html path.png width=60%
/// On the left we see a 6-input sorting network of depth 5 on input
/// \f$1, 1, 1, 0, 0, 0\f$. The output is in ascending order from top to bottom.
/// On the right we see what happens when we flip the second-from-last input
/// from a 0 to a 1. That change follows a path from the input channel to the
/// channel formerly carrying the last 0, shown in red.
/// \param j Flip value in this channel.
/// \param first Flip value starting at this level.
/// \param last Propagate change down to this level.
/// \return Channel whose value is flipped after the last level.

size_t CSortingNetwork::FlipInput(size_t j, const size_t first, const size_t last){
  const size_t nBit = m_nValue[first][j] ^ 1;
  m_nZeros += nBit? -1: 1; //if nBit has flipped to 1, one less zero, else one more
  
  for(size_t i=first; i<=last; i++){ //for each layer in range
    m_nValue[i][j] = nBit; //flip the value on channel j at that level 

    const size_t k = m_nComparator[i][j]; //channel joined via a comparator

    if(xor(m_nValue[i][k], j > k))
      j = k;
  } //for

  return j;
} //FlipInput

/// Get target output channel when the value on an input channel is flipped.
/// Assumes that local variable `m_nZeros` is set to the number of zeros in
/// the input before this value is flipped, and that the value in 
/// `m_nValue` has not been flipped yet (that is, `FlipInput()`has
/// not been called on that channel yet). If a 1 is to be flipped to a 0, then
/// it should output at channel `m_nZeros`. If a 0 is to be flipped to a 1,
/// then it should output at channel `m_nZeros - 1`.
/// \param delta Index of input channel whose value is to be flipped.
/// \param j Input level.
/// \return Index of output channel whose value is flipped.

//const size_t CSortingNetwork::GetTarget(const size_t delta, const size_t j) const{
//  return m_nValue[j][delta]? m_nZeros: m_nZeros - 1;
//} //GetTarget

/// Check whether sorting network sorts when the input value on a given
/// channel is flipped.
/// \param delta Index of channel to flip.
/// \return true if it still sorts when channel is flipped.

bool CSortingNetwork::StillSorts(const size_t delta){
  const size_t nTarget = m_nValue[0][delta]? m_nZeros: m_nZeros - 1;
  return FlipInput(delta, 0, m_nDepth - 1) == nTarget;
} //StillSorts

/// Check whether sorting network sorts all inputs.
/// \return true if it sorts.

bool CSortingNetwork::Sorts(){ 
  size_t i = 0; //index of bit to flip
  bool bSorts = true; //assume it sorts until we find otherwise
  Initialize(); //intialize input and values in comparator network to zero

  while(bSorts && i < m_nWidth){ //bail if it doesn't sort, or we've tried all binary inputs
    i = m_pGrayCode->Next(); //next bit to flip in Gray code order
    bSorts = bSorts && (i >= m_nWidth || StillSorts(i)); //check whether it still sorts when this bit is flipped
  } //while

  return bSorts;
} //Sorts