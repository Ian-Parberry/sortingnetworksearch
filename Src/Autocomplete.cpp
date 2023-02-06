/// \file Autocomplete.cpp
/// \brief Code for the fast searchable sorting network CAutocomplete.

// MIT License
//
// Copyright (c) 2022 Ian Parberry
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

/// Check whether stub of a sorting network sorts when the current input has
/// channel flipped. This overrides `CSortingNetwork::sort()`. Attempts to 
/// build the last level while testing it.
/// \param delta Index of channel to flip.
/// \return true if it still sorts when channel is flipped.

bool CAutocomplete::stillsorts(const size_t delta){
  size_t j = flipinput(delta - 1, 1, DEPTH - 2);

  //Build last layer, if necessary. Changed channel is currently j.
  size_t k = m_pGrayCode->m_nZeros + m_pGrayCode->m_nBit[delta] - 1; //destination channel
  
  if(j == k)
    return true; //success

  else{  
    size_t& cj = m_nMatch[DEPTH - 1][j]; //one end of comparator
    size_t& ck = m_nMatch[DEPTH - 1][k]; //other end of comparator

    if(cj == k && ck == j)
      return true; //comparator already exists  

    else if(cj == j && ck == k){ //both channels free
      cj = k; ck = j; //insert comparator
      return true;
    } //else if

    else return false; //can't put a comparator in, so fail
  } //else
} //stillsorts

/// Initialize the network for the sorting test, that is, make the Gray code
/// word for input be all zeros, and the values on every channel at every level
/// be zero. Yhis differs from `C1NFSortingNetwork::initSortingTest()` in that
/// it doesn't initialize values in the first and last levels.

void CAutocomplete::initSortingTest(){   
  m_pGrayCode->initalize(); //initialize the Gray code to all zeros.
  initValues(1, DEPTH - 2); //initialize the network values to all zeros.
} //initSortingTest

/// Initializes the testable representation of the last level of the sorting 
/// network to be empty, that is, containing no comparators.

void CAutocomplete::initLastLevel(){
  for(int j=0; j<INPUTS; j++) //for each channel
    m_nMatch[DEPTH - 1][j] = j;
} //initLastLevel

/// Check whether sorting network sorts all inputs.
/// Works for both odd and even n.
/// The difference between this and CSortingNetwork::sorts() is that
/// this version has to handle any hypothetical last even-numbered channel 
/// separately, testing it first with value zero then with value 1.
/// \return true iff it sorts

bool CAutocomplete::sorts(){ 
  initLastLevel(); //set last level to be empty, will be constructed on-the-fly

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

/// Set top of stack `m_nToS` to the second-last level of the sorting network.

void CAutocomplete::SetToS(){
  m_nToS = DEPTH - 2;
} //SetToS
