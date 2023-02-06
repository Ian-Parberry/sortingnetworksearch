/// \file ComparatorNetwork.h
/// \brief Interface for the comparator network CComparatorNetwork.

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

#ifndef __ComparatorNetwork_h__
#define __ComparatorNetwork_h__

#include <string>

#include "Defines.h"

/// \brief Comparator network.
///
/// A comparator network, each level of which is represented by a matching
/// stored in an array `m_nMatch`. There is a comparator between channels `j`
/// and `k` at level `i` iff `m_nMatch[i][j] == k && m_nMatch[i][k] == j`. 
/// This will allow for fast verification of whether a comparator network is a
/// sorting network. Note that this is different from the implementation in
/// `CMatching`, which is optimized for search rather than verification.

class CComparatorNetwork{
  protected: 
    size_t m_nMatch[DEPTH][INPUTS] = {0}; ///< Matchings at each level.
    bool m_bRedundant[DEPTH][INPUTS] = {false}; ///< True if comparator is redundant.
    
    size_t RemoveRepeatedComparators(); ///< Remove redundant comparators and return size.

  public: 
    CComparatorNetwork(); ///< Constructor.
    void save(const std::string&); ///< Save to file.
}; //CComparatorNetwork

#endif //__ComparatorNetwork_h__