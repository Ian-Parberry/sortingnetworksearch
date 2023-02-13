/// \file VeryFastSearchableSortingNetwork.h
/// \brief Interface for the sorting network CNearsort.

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

#ifndef __Nearsort_h__
#define __Nearsort_h__

#include "Autocomplete.h"
#include "Defines.h"

/// \brief Searchable sorting network with nearsort.
///
/// `CNearsort` is a version of  `CAutocomplete` that uses the nearsort
/// heuristic, which is based on reachability, to prune the second-last level.

class CNearsort: public CAutocomplete{
  protected:
    bool m_bReachableFrom[INPUTS][INPUTS]; ///< Reachable from.
    int m_nReachCountFrom[INPUTS]; ///< Count of channels reachable from.

    bool m_bReachableTo[INPUTS][INPUTS]; ///< Reachable to.
    int m_nReachCountTo[INPUTS]; ///< Count of channels reachable to.

    bool m_bReachable[INPUTS][INPUTS]; ///< Reachable from or to.
    int m_nReachCount[INPUTS]; ///< Count of channels reachable from or to.

    bool stillnearsorts(const size_t); ///< Does it still nearsort with this input change?
    bool evennearsorts(); ///< Does it nearly sort, even number of inputs?
    bool nearsorts(); ///< Does it nearly sort?
 
    void Process(); ///< Process a candidate comparator network.
    void SetToS(); ///< Set top of stack.

  public:
    CNearsort(CMatching& L2Matching, const size_t index); ///< Constructor.
}; //CNearsort

#endif //__Nearsort_h__