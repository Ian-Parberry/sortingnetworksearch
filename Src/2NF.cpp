/// \file SearchableSortingNetwork2NF.cpp
/// \brief Code for the searchable second normal form sorting network `C2NF`.

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

#include "2NF.h"
#include "Defines.h"

/// Constructor.
/// \param L2Matching Level 2 matching.
/// \param index Lexicographic number of level 2 matching.

C2NF::C2NF(CMatching& L2Matching, const size_t index): 
  CSearchable(),
  m_nSecondLevelIndex(index)
{
  m_nStack[0] = 0;
  InitMatchingRepresentations(0); //the level 1 matching is the identity

  for(int j=0; j<m_nWidth; j++)
    m_nMatching[1][j] = L2Matching[j]; //install second level candidate
} //constructor

/// Initialize and then start a backtracking search for all sorting networks
/// in Second Normal Form of given width and depth.

void C2NF::Backtrack(){ 
  if(odd(m_nWidth))m_nMatching[1][m_nWidth] = m_nWidth; 
  SynchMatchingRepresentations(1); //synch representation for testing
  FirstComparatorNetwork(2); //initialize from there down
  Search(); //begin actual search
} //Backtrack

/// Save a generated sorting network into a file with a suitable name.
/// Save comparator network to a file whose name encodes number of inputs,
/// depth, second level index, size, and lexicographics number. For example,
/// an 8-input comparator network of depth 5 with level 2 index 99, and 
/// 12 comparators, which is the 20th sorting network found, would be saved 
/// to file w8d5x99s12n20.txt.

void C2NF::SaveGeneratedSortingNetwork(){
  size_t size = RemoveRepeatedComparators(); //size after redundant comparators removed
  
  std::string filename = //construct file name
    "w" + std::to_string(m_nWidth) + 
    "d" + std::to_string(m_nDepth) +
    "x" + std::to_string(m_nSecondLevelIndex) +
    "s" + std::to_string(size) +
    "n" + std::to_string(m_nCount) + ".txt"; 

  Save(filename); //save to file with that name
} //SaveGeneratedSortingNetwork
