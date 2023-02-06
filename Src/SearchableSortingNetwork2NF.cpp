/// \file SearchableSortingNetwork2NF.cpp
/// \brief Code for the searchable second normal form sorting network C2NFSearchableSortingNetwork.

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

#include <stdio.h>

#include "SearchableSortingNetwork2NF.h"
#include "Defines.h"

/// Initialize the stack, the matching representations, and the
/// index of the second level matching. Create a level 2 search object.

C2NFSearchableSortingNetwork::C2NFSearchableSortingNetwork():
  CSearchableSortingNetwork()
{
  m_nStack[0] = 0;
  InitMatchingRepresentations(0); //make sure the level 0 matching is the identity
  m_nSecondLevelIndex = 0; //start with the first candidate for level 2
  m_pLevel2 = new CLevel2Search();
} //constructor

/// Delete the level 2 search object.

C2NFSearchableSortingNetwork::~C2NFSearchableSortingNetwork(){
  delete m_pLevel2;
} //destructor

/// Initialize and then start a backtracking search for all sorting networks of
/// given width and depth.

void C2NFSearchableSortingNetwork::backtrack(){
  printf("Starting search for %d-input sorting networks of depth %d.\n",
    INPUTS, DEPTH);

  m_nSecondLevelIndex = 0;

  for(auto matching: m_pLevel2->GetMatchings()){
    for(int j=0; j<INPUTS; j++)
      m_nMatching[1][j] = matching[j]; //install candidate
      
    if(odd(INPUTS))m_nMatching[1][INPUTS] = INPUTS;
    SynchMatchingRepresentations(1); //synch representation for testing
    firstComparatorNetwork(2); //initialize from there down

    search(); //begin actual search

    m_nSecondLevelIndex++; //next candidate
  } //for

  writeToLogFile(); //report results
} //backtrack

/// Save a generated sorting network into a file with a suitable name.
/// Save comparator network to a file whose name encodes number of inputs,
/// depth, and size. For example an 8-input comparator network of depth
/// 5 with 12 comparators would be saved to file w8d5s12.txt.

void C2NFSearchableSortingNetwork::SaveGeneratedSortingNetwork(){
  size_t size = RemoveRepeatedComparators(); //size after redundant comparators removed
  
  std::string filename = 
    "w" + std::to_string(INPUTS) + 
    "d" + std::to_string(DEPTH) +
    "l" + std::to_string(m_nSecondLevelIndex) +
    "s" + std::to_string(size) +
    "n" + std::to_string(m_nCount) + ".txt"; 

  save(filename); //save to file with that name
} //SaveGeneratedSortingNetwork

