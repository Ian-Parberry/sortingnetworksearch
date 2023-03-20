/// \file BinaryGrayCode.cpp
/// \brief Code for the binary reflected Gray code generator `CBinaryGrayCode`.

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

#include "BinaryGrayCode.h"

/// Reset Gray code generator to the first word in Gray code order, which is
/// the all-zero word.

void CBinaryGrayCode::initialize(){ 
  m_nZeros = m_nWidth; //all zeros
  
  for(size_t i=0; i<=m_nWidth+2; i++){
    m_nBit[i] = 0; //all zeros
    m_nStack[i] = i + 1; //recursion stack initial conditions
  } //for
} //initialize

/// Get the next binary word in binary reflected Gray code order, which will
/// differ from the previous one in exactly one bit.
/// \return Index of the bit that has changed, in the range 1..n. 
/// Out of range means we're finished.

size_t CBinaryGrayCode::next(){
  const size_t i = m_nStack[0]; //bit to change

  m_nStack[0] = 1; 
  m_nBit[i] ^= 1; //change bit
  m_nStack[i - 1] = m_nStack[i];
  m_nStack[i] = i + 1;
  m_nZeros += 1 - 2*m_nBit[i]; //adjust zero count

  return i; //return bit changed
} //next

///// Reader function for `m_nZeros`, the number of zeros.
///// \return `m_nZeros`, the number of zeros.
//
//const size_t CBinaryGrayCode::GetNumZeros() const{
//  return m_nZeros;
//} //GetNumZeros
//
///// Reader function for the array `m_nBit`. For speed, it is assumed that the
///// index parameter is in range.
///// \param i Index.
///// \return `m_nBit[i]`, the number of zeros.
//
//const size_t CBinaryGrayCode::operator[](const size_t i){
//  return m_nBit[i];
//} //operator[]

/// Get the target channel when a single bit of the input is changed.
/// \param delta Index of input bit to be changed.
/// \return The corresponding output channel for the changed bit.

const size_t CBinaryGrayCode::GetTarget(const size_t delta) const{
  return m_nZeros + m_nBit[delta] - 1;
} //GetTarget

/// Set the count of the number of zeros.
/// \param count New number of zeros.

void CBinaryGrayCode::SetNumZeros(const size_t count){
  m_nZeros = count;
} //SetNumZeros