/// \file SearchableSortingNetwork.cpp
/// \brief Code for the searchable sorting network class CSearchableSortingNetwork.

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
#include <windows.h> //for timeGetTime()

#include "SearchableSortingNetwork.h"

unsigned int CPUTimeInMilliseconds(); //guess what this does?

/// Initialize the CPU timer, compute the number of matchings and store it in
/// m_nNumMatchings.

CSearchableSortingNetwork::CSearchableSortingNetwork(): C1NFSortingNetwork(){
  m_nCumulativeCPUSecs = 0; //initialize timer

  //compute number of matchings and store in m_nNumMatchings
  m_nNumMatchings = 1;
  for(int i = INPUTS + (INPUTS&1) - 1; i>1; i-=2)
    m_nNumMatchings *= i;
} //constructor

/// Save a generated sorting network into a file with a suitable name.
/// Save comparator network to a file whose name encodes number of inputs,
/// depth, and size. For example an 8-input comparator network of depth
/// 5 with 12 comparators would be saved to file w8d5s12.txt.

void CSearchableSortingNetwork::SaveGeneratedSortingNetwork(){
  const size_t size = RemoveRepeatedComparators(); //size after redundant comparators removed
  
  std::string filename = 
    "w" + std::to_string(INPUTS) + 
    "d" + std::to_string(DEPTH) +
    "s" + std::to_string(size) +
    "n" + std::to_string(m_nCount) + ".txt"; 

  save(filename); //save to file with that name
} //SaveGeneratedSortingNetwork

/// Set top of stack `m_nToS` to the last level of the sorting network.

void CSearchableSortingNetwork::SetToS(){
  m_nToS = DEPTH - 1;
} //SetToS

/// Process a comparator network, which means testing whether it sorts, and if
/// it does, saving it to a file and incrementing a counter.

void CSearchableSortingNetwork::process(){
  if(sorts()){ //if it sorts
    SaveGeneratedSortingNetwork(); //save it
    m_nCount++; //add 1 to the total
  } //if
} //process

/// Perform a backtracking search, assuming everything has been initialized in
/// a suitable fashion.

void CSearchableSortingNetwork::search(){
  bool unfinished = true; //assume we're not finished

  while(unfinished){ //until we're finished
    process(); //process the corrent comparator network, that is, see if it sorts
    unfinished = nextComparatorNetwork(); //get the next comparator network, we're finished if this function says so  
  } //while
} //search

/// Initialize and then start a backtracking search for all sorting networks
/// of given width and depth.

void CSearchableSortingNetwork::backtrack(){
  m_nCount = 0; //we've found none so far
  firstComparatorNetwork(1); //assuming first normal form here
  search(); //perform the search
  writeToLogFile(); //write results to the log file for later perusal
} //backtrack

/// Set to first comparator network from some given level down to the bottom.
/// \param toplevel Top level of comparator network we are constructing here.

void CSearchableSortingNetwork::firstComparatorNetwork(int toplevel){
  m_nTop = toplevel; //save value of toplevel for later use

  for(int i=toplevel; i<DEPTH; i++){ //for each level in range
    InitMatchingRepresentations(i); //initialize both matching representations
    //m_nStack[i] = 0;
  }
} //firstComparatorNetwork

/// Synchronize m_nMatch to m_nMatching at a given level. The latter is 
/// assumed to be correct.
/// \param level The level at which to synchronize matchings.

void CSearchableSortingNetwork::SynchMatchingRepresentations(int level){
  for(size_t j=0; j<INPUTS; j+=2){ //for each pair of channels
    size_t x = m_nMatching[level][j]; //channel at left end of comparator
    size_t y = m_nMatching[level][j+1]; //channel at the other end

    if(y == INPUTS) //if the rightmost channel is the last one in a comparator network with an odd number of inputs
      m_nMatch[level][x] = x; //it's empty

    else{ //make the testable representation
      m_nMatch[level][x] = y; //x goes to y
      m_nMatch[level][y] = x; //y goes to x
    } //else
  } //for
} //SynchMatchingRepresentations

/// Initialize m_nMatch and m_nMatching to the first matching at a given level.
/// \param level The level at which to initialize matchings.

void CSearchableSortingNetwork::InitMatchingRepresentations(int level){
  m_nMatching[level].Initialize();  //initialize the generatable form
  m_nStack[level] = 0; //and its stack

  for(size_t j=0; j<INPUTS; j++) //initialize the testable form
    m_nMatch[level][j] = j^1;

  if(odd(INPUTS)) //one extra one if n is odd
    m_nMatch[level][INPUTS - 1] = INPUTS - 1;
} //InitMatchingRepresentations

/// Change to next comparator network.
/// This implementation uses a stack in the standard way to remove 
/// the need for recursion.
/// \return false if there are no more comparator networks.

bool CSearchableSortingNetwork::nextComparatorNetwork(){
//#if defined VANILLA || defined FIRSTNORMALFORM || defined SECONDNORMALFORM
//  m_nToS = d - 1;
//#elif defined AUTOCOMPLETE
//  m_nToS = d - 2;
//#elif defined NEARSORT
//  m_nToS = d - 3;
//#elif defined SUPERNEARSORT
//  m_nToS = d - 4;
//#endif

  SetToS(); //set top of stack

  m_nStack[m_nToS]++;
  if(m_nMatching[m_nToS].Next()){
    SynchMatchingRepresentations(m_nToS);
  }

  while((m_nToS >= m_nTop) && (m_nStack[m_nToS] == m_nNumMatchings)){
    InitMatchingRepresentations(m_nToS);

    if(--m_nToS >= m_nTop){
      m_nStack[m_nToS]++;

      if(m_nStack[m_nToS] < m_nNumMatchings && m_nMatching[m_nToS].Next())
          SynchMatchingRepresentations(m_nToS);
    } //if
  } //while

  return m_nToS >= m_nTop; //there are no more if we blow the top of the stack
} //nextComparatorNetwork

/// Write an entry to the log file recording how many sorting networks found and
/// how much CPU time was used. Slam it up on the console too.

void CSearchableSortingNetwork::writeToLogFile(){   
  FILE* logfile;
  fopen_s(&logfile, "log.txt", "at");

  if(logfile){
    float t = (float)CPUTimeInMilliseconds()/1000.0f;

    fprintf_s(logfile, 
      "%d %d-input sorting networks of depth %d found in %0.3f seconds CPU time.\n",
      m_nCount, INPUTS, DEPTH, t); 
    printf("%d found in %0.3f seconds CPU time.\n", m_nCount, t);

    fclose(logfile);
  } //if
} //writetologfile
