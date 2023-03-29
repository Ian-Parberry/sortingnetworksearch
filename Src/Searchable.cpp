/// \file SearchableSortingNetwork.cpp
/// \brief Code for the searchable sorting network class `CSearchable`.

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

#include "Searchable.h"

/// Compute the number of matchings and store it in `m_nNumMatchings`.

CSearchable::CSearchable(): C1NF(){
  m_nNumMatchings = 1;
  for(size_t i = oddfloor(m_nWidth); i>1; i-=2)
    m_nNumMatchings *= i;
} //constructor

/// Save a generated sorting network into a file with a suitable name.
/// Save comparator network to a file whose name encodes number of inputs,
/// depth, and size. For example an 8-input comparator network of depth
/// 5 with 12 comparators would be saved to file w8d5s12.txt.

void CSearchable::SaveGeneratedSortingNetwork(){
  const size_t size = RemoveRepeatedComparators(); //size after redundant comparators removed
  
  std::string filename = 
    "w" + std::to_string(m_nWidth) + 
    "d" + std::to_string(m_nDepth) +
    "s" + std::to_string(size) +
    "n" + std::to_string(m_nCount) + ".txt"; 

  Save(filename); //save to file with that name
} //SaveGeneratedSortingNetwork

/// Set top of stack `m_nToS` to the last level of the sorting network.

void CSearchable::SetToS(){
  m_nToS = (int)m_nDepth - 1;
} //SetToS

/// Process a comparator network, which means testing whether it sorts, and if
/// it does, saving it to a file and incrementing a counter.

void CSearchable::Process(){
  if(Sorts()){ //if it sorts
    SaveGeneratedSortingNetwork(); //save it
    m_nCount++; //add 1 to the total
  } //if
} //Process

/// Perform a backtracking search, assuming everything has been initialized in
/// a suitable fashion.

void CSearchable::Search(){
  bool unfinished = true; //assume we're not finished

  while(unfinished){ //until we're finished
    Process(); //process the current comparator network, that is, see if it sorts
    unfinished = NextComparatorNetwork(); //get the next comparator network, we're finished if this function says so  
  } //while
} //Search

/// Initialize and then start a backtracking search for all sorting networks
/// of given width and depth.

void CSearchable::Backtrack(){
  m_nCount = 0; //we've found none so far
  FirstComparatorNetwork(1); //assuming first normal form here
  Search(); //perform the search
} //Backtrack

/// Set to first comparator network from some given level down to the bottom.
/// \param toplevel Top level of comparator network we are constructing here.

void CSearchable::FirstComparatorNetwork(size_t toplevel){
  m_nTop = (int)toplevel; //save value of toplevel for later use

  for(size_t i=toplevel; i<m_nDepth; i++) //for each level in range
    InitMatchingRepresentations(i); //initialize both matching representations
} //FirstComparatorNetwork

/// Synchronize m_nMatch to m_nMatching at a given level. The latter is 
/// assumed to be correct.
/// \param level The level at which to synchronize matchings.

void CSearchable::SynchMatchingRepresentations(size_t level){
  for(size_t j=0; j<m_nWidth; j+=2){ //for each pair of channels
    size_t x = m_nMatching[level][j]; //channel at left end of comparator
    size_t y = m_nMatching[level][j + 1]; //channel at the other end

    if(y == m_nWidth) //if the rightmost channel is the last one in a comparator network with an odd number of inputs
      m_nMatch[level][x] = x; //it's empty

    else{ //make the testable representation
      m_nMatch[level][x] = y; //x goes to y
      m_nMatch[level][y] = x; //y goes to x
    } //else
  } //for
} //SynchMatchingRepresentations

/// Initialize m_nMatch and m_nMatching to the first matching at a given level.
/// \param level The level at which to initialize matchings.

void CSearchable::InitMatchingRepresentations(size_t level){
  m_nMatching[level].Initialize();  //initialize the generatable form
  m_nStack[level] = 0; //and its stack

  for(size_t j=0; j<m_nWidth; j++) //initialize the testable form
    m_nMatch[level][j] = j^1;

  if(odd(m_nWidth)) //one extra one if n is odd
    m_nMatch[level][m_nWidth - 1] = m_nWidth - 1;
} //InitMatchingRepresentations

/// Change to next comparator network. This implementation uses a stack in the
/// standard way to remove the need for recursion.
/// \return false if there are no more comparator networks.

bool CSearchable::NextComparatorNetwork(){
  SetToS(); //set top of stack

  m_nStack[m_nToS]++;

  if(m_nMatching[m_nToS].Next())
    SynchMatchingRepresentations(m_nToS);

  while((m_nToS >= m_nTop) && (m_nStack[m_nToS] == m_nNumMatchings)){
    InitMatchingRepresentations(m_nToS);

    if(--m_nToS >= m_nTop){
      m_nStack[m_nToS]++;

      if(m_nStack[m_nToS] < m_nNumMatchings && m_nMatching[m_nToS].Next())
        SynchMatchingRepresentations(m_nToS);
    } //if
  } //while

  return m_nToS >= m_nTop; //there are no more if we blow the top of the stack
} //NextComparatorNetwork

/// Reader function for the number of sorting networks found.
/// \return The number of sorting networks found.

const size_t CSearchable::GetCount() const{
  return m_nCount;
} //GetCount
