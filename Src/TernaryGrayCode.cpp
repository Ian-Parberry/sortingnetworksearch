/// \file TernaryGrayCode.cpp
/// \brief Code for the ternary reflected Gray code generator `CTernaryGrayCode`.

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

#include "TernaryGrayCode.h"

/// Reset Gray code generator to the first word in Gray code order, the
/// all-zero word.

void CTernaryGrayCode::initialize(){ 
  CBinaryGrayCode::initialize(); //reset as for the binary version
  
  for(size_t i=0; i<=m_nWidth+2; i++) //reset the direction array too
    m_nDirection[i] = 0;
} //initialize

/// Get the next binary word in ternary reflected Gray code order, which will
/// differ from the previous one in exactly one bit.
/// \return Index of the bit that has changed, in the range 1..m_nWidth. 
/// Out of range means we're finished.

size_t CTernaryGrayCode::next(){
  const size_t i = m_nStack[0]; 
  m_nStack[0] = 1;

  const size_t j = 2*i - m_nBit[2*i - m_nDirection[i]];
  m_nBit[j] ^= 1;

  if(m_nBit[2*i] == m_nBit[2*i - 1]){
    m_nDirection[i] ^= 1;
    m_nStack[i - 1] = m_nStack[i];
    m_nStack[i] = i + 1;
  } //if

  return j;
} //next

//////////////////////////////////////////////////////////////////////////////
//CTernaryGrayCode2 functions

/// Initialize `CTernaryGrayCode` and fill the delta table `m_stdDelta` with the
/// indexes of the channels whose values are flipped in the order in which they
/// are flipped.

CTernaryGrayCode2::CTernaryGrayCode2(){
  CTernaryGrayCode::initialize(); //set to all zeros
  size_t j = CTernaryGrayCode::next(); //skip to the next that's not all zeros

  while(j <= m_nWidth){
    m_stdDelta.push_back(j); 
    j = CTernaryGrayCode::next();
  } //while
  
  m_stdDelta.push_back(m_nWidth + 3); //sentinel
} //constructor

/// Initialize `CTernaryGrayCode` and set the current index to zero.

void CTernaryGrayCode2::initialize(){ 
  CTernaryGrayCode::initialize();
  m_nIndex = 0;
} //initialize

/// Get the next value from the table and increment the current index.

size_t CTernaryGrayCode2::next(){
  return m_stdDelta[m_nIndex++];
} //next
