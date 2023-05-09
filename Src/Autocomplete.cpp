/// \file Autocomplete.cpp
/// \brief Code for the fast searchable sorting network `CAutocomplete`.

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

#include "Autocomplete.h"

#include "Defines.h"

/// Constructor.
/// \param L2Matching Level 2 matching.
/// \param index Lexicographics number of level 2 matching.

CAutocomplete::CAutocomplete(CMatching& L2Matching, const size_t index):
  C2NF(L2Matching, index){
} //constructor

/// Check whether stub of a sorting network sorts when the current input has
/// channel flipped. This overrides `CSortingNetwork::sort()`. Attempts to 
/// build the last level while testing it.
/// \param delta Index of channel to flip.
/// \return true if it still sorts when channel is flipped.

bool CAutocomplete::StillSorts(const size_t delta){
  size_t k = m_nValue[1][delta]? m_nZeros: m_nZeros - 1; //destination channel
  size_t j = FlipInput(delta, 1, m_nDepth - 2);

  //Build last layer, if necessary. Changed channel is currently j.
  
  if(j == k)
    return true; //success

  else{  
    size_t& cj = m_nComparator[m_nDepth - 1][j]; //one end of comparator
    size_t& ck = m_nComparator[m_nDepth - 1][k]; //other end of comparator

    if(cj == k && ck == j)
      return true; //comparator already exists  

    else if(cj == j && ck == k){ //both channels free
      cj = k; ck = j; //insert comparator
      return true;
    } //else if

    else return false; //can't put a comparator in, so fail
  } //else
} //StillSorts

/// Initialize the network for the sorting test, that is, make the Gray code
/// word for input be all zeros, and the values on every channel at every level
/// be zero. Yhis differs from `C1NF::Initialize()` in that
/// it doesn't initialize values in the first and last levels.

void CAutocomplete::Initialize(){   
  m_pGrayCode->Initialize(); //initialize the Gray code to all zeros.
  InitValues(1, m_nDepth - 2); //initialize the network values to all zeros.
  m_nZeros = m_nWidth; //all zeros
} //initialize

/// Initializes the testable representation of the last level of the sorting 
/// network to be empty, that is, containing no comparators.

void CAutocomplete::initLastLevel(){
  for(int j=0; j<m_nWidth; j++) //for each channel
    m_nComparator[m_nDepth - 1][j] = j;
} //initLastLevel

/// Check whether sorting network sorts all inputs.
/// The difference between this and `CSortingNetwork::Sorts()` is that
/// this version has to handle any hypothetical last even-numbered channel 
/// separately, testing it first with value zero then with value 1.
/// \return true iff it sorts

bool CAutocomplete::Sorts(){ 
  initLastLevel(); //set last level to be empty, will be constructed on-the-fly

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

/// Set top of stack `m_nToS` to the second-last level of the sorting network.

void CAutocomplete::SetToS(){
  m_nToS = (int)m_nDepth - 2;
} //SetToS
