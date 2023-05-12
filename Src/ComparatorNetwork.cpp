/// \file ComparatorNetwork.cpp
/// \brief Code for the comparator network `CComparatorNetwork`.

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

#include <iostream>
#include <fstream>

#include "ComparatorNetwork.h"

/// Initialize the matching array to represent a comparator network with no
/// comparators.

CComparatorNetwork::CComparatorNetwork(){
  //for(size_t i=0; i<m_nDepth; i++) //for each level
  //  for(size_t j=0; j<m_nWidth; j++) //for each channel
  //    m_nComparator[i][j] = j; //connected to self means no comparator
} //constructor

/// Virtual destructor.

CComparatorNetwork::~CComparatorNetwork(){
} //destructor

/// Save comparator network to a text file.
/// \param fname File name string.

void CComparatorNetwork::Save(const std::string& fname){
  std::ofstream output(fname); //output file stream

  if(output.is_open()){ //file opened correctly
    for(size_t i=0; i<m_nDepth; i++){ //for each level
      for(size_t j=0; j<m_nWidth; j++){ //for each channel
        const size_t k = m_nComparator[i][j]; //between channels j, k at level i
        if(k > j) //not already printed
          output << j << " " << k << " "; //print comparator
      } //for

      output << std::endl; //end of line
    } //for

    output.close(); //end of file
  } //if
} //Save
