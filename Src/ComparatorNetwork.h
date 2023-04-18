/// \file ComparatorNetwork.h
/// \brief Interface for the comparator network `CComparatorNetwork`.

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

#ifndef __ComparatorNetwork_h__
#define __ComparatorNetwork_h__

#include <string>

#include "Defines.h"
#include "Settings.h"

/// \brief Comparator network.
///
/// A comparator network, each level of which is represented by a matching
/// stored in an array `m_nComparator`. There is a comparator between channels `j`
/// and `k` at level `i-1` iff `m_nComparator[i][j] == k` and `m_nComparator[i][k] == j`. 
/// Intuitively, `m_nComparator[i][j]` is the channel that channel `j` is matched
/// to via a comparator in level `i-1`. This is called the _map_ representation.
/// \image html comparator.png "A sorting network (left) and its map representation (right)." width=47% 
/// For example, in the above diagram at left there is a comparator between
/// channels 0 and 1 at level 1, and in the table at right `m_nComparator[0][0] == 1`
/// and `m_nComparator[0][1] == 0`.

class CComparatorNetwork: public CSettings{
  protected: 
    size_t m_nComparator[MAXDEPTH][MAXINPUTS] = {0}; ///< Matchings at each level.
    bool m_bRedundant[MAXDEPTH][MAXINPUTS] = {false}; ///< True if comparator is redundant.
    
    size_t RemoveRepeatedComparators(); ///< Remove redundant comparators and return size.

  public: 
    CComparatorNetwork(); ///< Constructor.
    void Save(const std::string&); ///< Save to file.
}; //CComparatorNetwork

#endif //__ComparatorNetwork_h__