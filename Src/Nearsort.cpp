/// \file Nearsort.cpp
/// \brief Code for the searchable sorting network with the nearsort 
/// heuristic `CNearsort`.

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

#include "Nearsort.h"

/// Constructor.
/// \param L2Matching Level 2 matching.
/// \param index Lexicographic number of level 2 matching.

CNearsort::CNearsort(CMatching& L2Matching, const size_t index):
  CAutocomplete(L2Matching, index){
} //constructor

/// Check whether sorting network nearsorts all inputs.
/// \return true iff it sorts

bool CNearsort::evennearsorts(){ 
  bool bNearSorts = true;
  size_t i = m_pGrayCode->next();

  do{
    bNearSorts = stillnearsorts(i);
    i = m_pGrayCode->next();
  }while(bNearSorts && i < m_nWidth); 

  m_pGrayCode->initialize();
 
  return bNearSorts;
} //evennearsorts

/// Check whether sorting network nearsorts all inputs.
/// Works for both odd and even n.
/// \return true iff it nearsorts

bool CNearsort::nearsorts(){
  m_pGrayCode->initialize();  
  InitValues(1, m_nDepth - 3);
  m_nZeros = m_nWidth; //all zeros

  for(int i=0; i<m_nWidth; i++){
    for(int j=0; j<m_nWidth; j++)
	    m_bReachableFrom[i][j] = m_bReachableTo[i][j] = m_bReachable[i][j] = false;
    
    m_nReachCountFrom[i] = m_nReachCountTo[i] = m_nReachCount[i] = 0;
  } //for

  if(!evennearsorts())
    return false;

  //if odd number of inputs, handle the last one

  if(odd(m_nWidth)){     
    m_pGrayCode->initialize();  
    InitValues(1, m_nDepth - 3);
    m_nZeros = m_nWidth - 1; //all zeros

    for(int j=1; j<m_nDepth; j++)
      m_nValue[j][m_nWidth - 1] = 1;

    if(!evennearsorts())
      return false;
  } //if

  return true;
} //nearsorts

/// Check whether sorting network nearsorts when the current input has channel
/// flipped.
/// \param delta Index of channel to flip.
/// \return true if it still nearsorts when channel is flipped.

bool CNearsort::stillnearsorts(const size_t delta){
  size_t k = GetTarget(delta, 1); //destination channel 
  size_t j = flipinput(delta, 1, m_nDepth - 3); //source channel into level d-2
  
  if(j == k)return true; //self

  //reachability heuristic: size of "from" <= 3

  if(!m_bReachableFrom[j][k]){
    if(m_nReachCountFrom[j] >= 3)return false; //not there and no room
	  m_nReachCountFrom[j]++;
    m_bReachableFrom[j][k] = true;
  } //if
  
  //reachability heuristic: size of "to" <= 3

  if(!m_bReachableTo[j][k]){
    if(m_nReachCountTo[k] >= 3)return false; //not there and no room
	  m_nReachCountTo[k]++;
    m_bReachableTo[j][k] = true;
  } //if
  
  //reachability heuristic: size of "from" union "to" <= 5

  if(!m_bReachable[j][k]){
    if(m_nReachCount[j] >= 5 || m_nReachCount[k] >= 5) return false; //not there and no room
	  m_nReachCount[j]++; m_nReachCount[k]++;
    m_bReachable[j][k] = m_bReachable[k][j] = true;
  } //if

	return true;
} //stillnearsorts

/// Process a comparator network, which is pretty much the same as
/// `CSearchable::Process()` except that you stop one level
/// early and prune if the network so far fails to nearsort all inputs.
/// If it fails to nearsort, then it won't sort. Continue with
/// those that nearsort because some of them might actually sort.

void CNearsort::Process(){
  if(nearsorts()){
    InitMatchingRepresentations(m_nDepth - 2);
    bool unfinished = true;

    while(unfinished){
      CSearchable::Process();
      unfinished = m_nMatching[m_nDepth - 2].Next();   

      if(unfinished)SynchMatchingRepresentations(m_nDepth - 2);
    } //while
  } //if
} //Process

/// Set top of stack `m_nToS` to the third-last level of the sorting network.

void CNearsort::SetToS(){
  m_nToS = (int)m_nDepth - 3;
} //SetToS
