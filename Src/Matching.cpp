/// \file Matching.cpp
/// \brief Code for the matching `CMatching`.

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

#include <algorithm>

#include "Matching.h"

CComparator::CComparator(){
  MakeEmpty();
} //constructor

/// Set to the identity matching, which places comparators between channels 
/// 0 and 1, 2 and 3, 4 and 5, etc.

void CComparator::MakeIdentity(){
  for(size_t j=0; j<m_nWidth; j++) 
    m_nMatch[j] = j^1;

  if(odd(m_nWidth)) //empty channel if width is odd
    m_nMatch[m_nWidth - 1] = m_nWidth - 1;
} //MakeIdentity

void CComparator::MakeEmpty(){
  for(size_t j=0; j<m_nWidth; j++) 
    m_nMatch[j] = j;
} //MakeEmpty

const size_t CComparator::GetMatch(const size_t index) const{
  return m_nMatch[index];
} //GetMatch

void CComparator::SetMatch(const size_t i, const size_t j){
  m_nMatch[i] = j;
  m_nMatch[j] = i;
} //SetMatch

///////////////////////////////////////////////////////////////////////////////

/// Initialize the matching to the identity matching.

CMatching::CMatching(){
  Initialize();
} //constructor 

/// The copy constructor.
/// \param m Matching to copy.

CMatching::CMatching(const CMatching& m){ //copy constructor
  for(size_t i=0; i<m_nWidth+1; i++){
    m_nMatching[i] = m.m_nMatching[i];

#ifdef NEWMATCHING
    m_nMatch[i] = m.m_nMatch[i];
#else
    m_nMap[i] = m.m_nMap[i];
#endif

    m_nStack[i] = m.m_nStack[i];
  } //for
} //copy constructor

/// Initialize to the identity matching.

void CMatching::Initialize(){
  for(size_t i=0; i<evenceil(m_nWidth); i++){
    m_nMatching[i] = i;

#ifdef NEWMATCHING
    m_nMatch[i] = i;
#else
    m_nMap[i] = i;
#endif 

    m_nStack[i] = (int)i - 1;
  } //for
} //Initialize

/// Get the next matching. Uses the stack to avoid recursing.
/// \return true if there was a next matching 

bool CMatching::Next(){
  size_t s = 4;
  size_t i = m_nStack[s - 1];

  while(i < 1 && s < oddfloor(m_nWidth)){
    size_t temp = m_nMatching[s - 2];

    for(size_t j=s-1; j>=2; j--){
      m_nMatching[j - 1] = m_nMatching[j - 2];

#ifdef NEWMATCHING
      m_nMatch[m_nMatching[j - 1]] = j - 1;
#else
      m_nMap[m_nMatching[j - 1]] = j - 1;
#endif

    } //for

    m_nMatching[0] = temp;

#ifdef NEWMATCHING
    m_nMatch[temp] = 0;
#else
    m_nMap[temp] = 0;
#endif

    for(size_t j=0; j<s; j++)
      m_nStack[j] = (int)j - 1;

    s += 2;
    i = m_nStack[s - 1];
  } //while

  if(i > 0){
    std::swap(m_nMatching[i - 1], m_nMatching[s - 2]);

#ifdef NEWMATCHING
    m_nMatch[m_nMatching[i - 1]] = i - 1;
    m_nMatch[m_nMatching[s - 2]] = s - 2;
#else
    m_nMap[m_nMatching[i - 1]] = i - 1;
    m_nMap[m_nMatching[s - 2]] = s - 2;
#endif

    m_nStack[s - 1] = (int)i - 1;
  } //if

  return m_nStack[i] >= 0;
} //Next

/// Swap a pair of entries in an array.
/// \param m An array.
/// \param i The first index.
/// \param j The second index.

void CMatching::SwapPair(int m[], size_t i, size_t j){
  const size_t i0 = 2*i;
  const size_t i1 = i0 + 1;
  const size_t j0 = 2*j;
  const size_t j1 = j0 + 1;

  std::swap(m[i0], m[j0]);
  std::swap(m[i1], m[j1]);

  for(size_t k=0; k<m_nWidth; k++)
    if(m[k] == i0)           m[k] = (int)j0;
    else if(m[k] == (int)j0) m[k] = (int)i0;
    else if(m[k] == (int)i1) m[k] = (int)j1;
    else if(m[k] == (int)j1) m[k] = (int)i1;
} //SwapPair

/// Normalize the matching.

void CMatching::Normalize(){ 
  const size_t n = evenceil(m_nWidth);
  
  int nCopy[MAXINPUTS + 1] = {0}; ///< Integer copy of matching.
  
  for(size_t j=0; j<n; j++)

#ifdef NEWMATCHING
    nCopy[j] = (int)m_nMatching[m_nMatch[j]^1];
#else
    nCopy[j] = (int)m_nMatching[m_nMap[j]^1];
#endif

  size_t next = 1;

  for(size_t j=0; j<n; j++){
    const size_t src = std::max(next++, j/2 + 1); 

    if(nCopy[j] > int(2*src + 1))
      SwapPair(nCopy, src, nCopy[j]/2);
  } //for

  size_t top = 0;

  for(size_t k=0; k<n; k++)
    if(nCopy[k] >= 0){
      m_nMatching[top++] = k;
      m_nMatching[top++] = nCopy[k];
      nCopy[nCopy[k]] = -1;
    } //if
} //Normalize

/// Swap two pairs of entries in the `m_nMatching` and `m_nMap` arrays.
/// \param i Index of first pair.
/// \param j Index of second pair.

void CMatching::Swap(const size_t i, const size_t j){

#ifdef NEWMATCHING
  const size_t i0 = m_nMatch[2*i];
  const size_t j0 = m_nMatch[2*j]; 
#else
  const size_t i0 = m_nMap[2*i];
  const size_t j0 = m_nMap[2*j]; 
#endif

  m_nMatching[i0] = 2*j;
  m_nMatching[j0] = 2*i;

#ifdef NEWMATCHING
  m_nMatch[m_nMatching[i0]] = i0;
  m_nMatch[m_nMatching[j0]] = j0;
#else
  m_nMap[m_nMatching[i0]] = i0;
  m_nMap[m_nMatching[j0]] = j0;
#endif


#ifdef NEWMATCHING
  const size_t i1 = m_nMatch[2*i + 1];
  const size_t j1 = m_nMatch[2*j + 1];
#else
  const size_t i1 = m_nMap[2*i + 1];
  const size_t j1 = m_nMap[2*j + 1];
#endif

  m_nMatching[i1] = 2*j + 1;
  m_nMatching[j1] = 2*i + 1;

#ifdef NEWMATCHING
  m_nMatch[m_nMatching[i1]] = i1;
  m_nMatch[m_nMatching[j1]] = j1;
#else
  m_nMap[m_nMatching[i1]] = i1;
  m_nMap[m_nMatching[j1]] = j1;
#endif
} //swap

/// Type cast to a string consisting of space-separated values
/// from `m_nMatching`.
/// \return String describing this matching.

CMatching::operator std::string() const{
  std::string str; //result string

  for(size_t i=0; i<m_nWidth-1; i++) //for all but last entry
    str += std::to_string(m_nMatching[i]) + " "; //append space separated

  return str + std::to_string(m_nMatching[m_nWidth - 1]); //append last entry
} //std::string

/// Index operator, used to access members of `m_nMatching` as an L-value.
/// \param i Index.
/// \return Reference to the indexed element of the matching.

size_t& CMatching::operator[](const size_t i){ 
  return m_nMatching[i];
} //operator[]

/// Index operator, used to access members of `m_nMatching` as an R-value.
/// \param i Index.
/// \return The indexed element of the matching.

const size_t CMatching::operator[](const size_t i) const{ 
  return m_nMatching[i];
} //operator[]
