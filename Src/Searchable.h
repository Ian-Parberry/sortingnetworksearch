/// \file Searchable.h
/// \brief Interface for the searchable sorting network `CSearchable`.

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

#ifndef __Searchable_h__
#define __Searchable_h__

#include "1NF.h"

#include "Defines.h"
#include "Matching.h"

/// \brief Searchable sorting network.
///
/// The searchable sorting network class will perform a backtracking search
/// for a sorting network of a given depth and number of inputs.

class CSearchable: public C1NF{
  protected:  
    size_t m_nCount = 0; ///< Number of comparator networks found that sort.

    CMatching m_nMatching[MAXDEPTH]; ///< Matchings that make up comparator network in a form that makes searching faster. 

    int m_nStack[MAXDEPTH] = {0}; ///< Stack to remove recursion from search.
    int m_nToS = 0; ///< Top of stack.

    size_t m_nNumMatchings = 0; ///< Number of matchings of this size.
    size_t m_nTop = 0; ///< Topmost level.

    void FirstComparatorNetwork(size_t); ///< Set to first comparator network.
    bool NextComparatorNetwork(); ///< Change to next comparator network.
    void SynchMatchingRepresentations(size_t); ///< Synchronize the two different matching representations.
    void InitMatchingRepresentations(size_t); ///< Initialize the two different matching representations.

    virtual void SaveGeneratedSortingNetwork(); ///< Save comparator network.
    virtual void SetToS(); ///< Set top of stack.
    virtual void Process(); ///< Process a candidate comparator network.

    void Search(); ///< Do the actual search.

  public:
    CSearchable(); ///< Constructor.

    virtual void Backtrack(); ///< Backtracking search.

    const size_t GetCount() const; ///< Get count.
}; //CSearchable

#endif //__Searchable_h__