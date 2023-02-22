/// \file ComparatorNetwork.cpp
/// \brief Code for the comparator network CComparatorNetwork.

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

#include "ComparatorNetwork.h"

/// Initialize the matching array to represent a comparator network with no
/// comparators.

CComparatorNetwork::CComparatorNetwork(){
  for(size_t i=0; i<m_nDepth; i++) //for each level
    for(size_t j=0; j<m_nWidth; j++) //for each channel
      m_nMatch[i][j] = j; //connected to self means no comparator
} //constructor
 
/// Remove any comparators that duplicate a comparator on the
/// previous level.
/// \return Number of comparators after redundant ones have been removed.

size_t CComparatorNetwork::RemoveRepeatedComparators(){
  size_t count = 2*(m_nWidth/2); //number of comparators

  for(size_t i=0; i<m_nDepth; i++) //for each level
    for(size_t j=0; j<m_nWidth; j++) //for each channel
      m_bRedundant[i][j] = false;

  for(size_t i=1; i<m_nDepth; i++) //for each level except the top one
    for(size_t j=0; j<m_nWidth; j++) //for each channel
      if((m_nMatch[i][j] == m_nMatch[i-1][j]) && !m_bRedundant[i][j]) //if channel connected to same one in previous level
        m_bRedundant[i][j] = true;  //remove connection
      else if(m_nMatch[i][j] != j)count++;

  return count/2; //everything gets counted twice
} //RemoveRepeatedComparators

/// Save comparator network to a text file.
/// \param fname File name.

void CComparatorNetwork::save(const std::string& fname){
  FILE* output = nullptr;
  fopen_s(&output, fname.c_str(), "wt");

  if(output){    
    for(size_t i=0; i<m_nDepth; i++){ //for each level
      for(size_t j=0; j<m_nWidth; j++){ //for each channel
        size_t k = m_nMatch[i][j]; //comparator between channel j and k at level i
        
        if(!m_bRedundant[i][j] && k > j)
          fprintf_s(output, "%zu %zu ", j, k);
      } //for each channel

      fprintf_s(output, "\n");
    } //for

    fclose(output);
  } //if
} //save