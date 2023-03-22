/// \file Nearsort2.cpp
/// \brief Code for the searchable sorting network with the nearsort2
/// heuristic `CNearsort2`.

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

#include "Nearsort2.h"

/// Constructor.
/// \param L2Matching Level 2 matching.
/// \param index Lexicographic number of level 2 matching.

CNearsort2::CNearsort2(CMatching& L2Matching, const size_t index):
  CNearsort(L2Matching, index){
} //constructor

/// Check whether sorting network nearsorts2 all inputs. Works for even width,
/// and for odd width it doesn't change the last input.
/// \return true iff it sorts

bool CNearsort2::evennearsorts2(){ 
  size_t i = 0;
  bool bNearSorts = true;

  while(bNearSorts && i<=m_nWidth){
    i = m_pGrayCode->next();
    bNearSorts = bNearSorts && (i>m_nWidth || stillnearsorts2(i));
  } //while
  
  m_pGrayCode->initialize(); 

  return bNearSorts;
} //evennearsorts2

/// Check whether sorting network nearsorts2 all inputs.
/// Works for both odd and even `m_nWidth`.
/// \return true iff it nearsorts2

bool CNearsort2::nearsorts2(){
  m_pGrayCode->initialize();  
  InitValues(1, m_nDepth - 4);
  m_nZeros = m_nWidth; //all zeros

  for(int i=0; i<m_nWidth; i++){
    for(int j=0; j<m_nWidth; j++)
	    m_bReachableFrom[i][j] = m_bReachableTo[i][j] = m_bReachable[i][j] = false;
    
    m_nReachCountFrom[i] = m_nReachCountTo[i] = m_nReachCount[i] = 0;
  } //for

  if(!evennearsorts2())
    return false;

  if(m_nWidth & 1){ //odd number of inputs, handle the last one independently   
    m_pGrayCode->initialize();  
    InitValues(1, m_nDepth - 4);
    m_nZeros = m_nWidth - 1;

    for(int j=1; j<m_nDepth; j++)
      m_nValue[j][m_nWidth - 1] = 1;

    if(!evennearsorts2())
      return false;
  } //if

  return true;
} //nearsorts2

/// Check whether sorting network nearsorts2 when the current input has 
/// channel flipped.
/// \param delta Index of channel to flip.
/// \return true if it still nearsorts2 when channel is flipped.

bool CNearsort2::stillnearsorts2(const size_t delta){
  size_t k = GetTarget(delta - 1, 1); //destination channel  
  const size_t j = flipinput(delta - 1, 1, m_nDepth - 4);
  
  if(j == k)return true; //self

  //reachability heuristic: size of "from" <= 7

  if(!m_bReachableFrom[j][k]){
    if(m_nReachCountFrom[j] >= 7) return false; //not there and no room
	  m_nReachCountFrom[j]++;
    m_bReachableFrom[j][k] = true;
  } //if
  
  //reachability heuristic: size of "to" <= 7

  if(!m_bReachableTo[j][k]){
    if(m_nReachCountTo[k] >= 7) return false; //not there and no room
	  m_nReachCountTo[k]++;
    m_bReachableTo[j][k] = true;
  } //if
  
  //reachability heuristic: size of "from" union "to" <= 9

  if(!m_bReachable[j][k]){
    if(m_nReachCount[j] >= 9 || m_nReachCount[k] >= 9) return false; //not there and no room
	  m_nReachCount[j]++; m_nReachCount[k]++;
    m_bReachable[j][k] = m_bReachable[k][j] = true;
  } //if

	return true;
} //stillnearsorts2

/// Process a comparator network, which is pretty much the same as
/// `CNearsort::Process()` except that you stop two levels
/// early and prune if the network so far fails to nearsort2 all inputs.
/// If it fails to nearsort2, then it won't sort. Continue with
/// those that nearsort2 because some of them might actually sort.

void CNearsort2::Process(){
  if(nearsorts2()){
    InitMatchingRepresentations(m_nDepth - 3);
    bool unfinished = true;

    while(unfinished){
      CNearsort::Process();
      unfinished = m_nMatching[m_nDepth - 3].Next(); 
      if(unfinished)
        SynchMatchingRepresentations(m_nDepth - 3);
    } //while
  } //if
} //Process

  /// Set top of stack `m_nToS` to the fourth-last level of the sorting network.

void CNearsort2::SetToS(){
  m_nToS = (int)m_nDepth - 4;
} //SetToS
