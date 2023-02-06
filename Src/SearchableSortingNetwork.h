/// \file SearchableSortingNetwork.h
/// \brief Interface for the searchable sorting network CSearchableSortingNetwork.

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

#ifndef __SearchableSortingNetwork_h__
#define __SearchableSortingNetwork_h__

#include "SortingNetwork1NF.h"

#include "Defines.h"
#include "Matching.h"

/// \brief Searchable sorting network.
///
/// The searchable sorting network class will perform a backtracking search
/// for a sorting network of a given depth and number of inputs. It periodically
/// dumps its state into a dump file, and will restart from that file if it is
/// present when it starts up.

class CSearchableSortingNetwork: public C1NFSortingNetwork{
  protected:  
    FILE* m_hDumpFile = nullptr; ///< Handle to dump file.
    int m_nCount = 0; ///< Number of comparator networks found that actually sort.
    int m_nCumulativeCPUSecs = 0; ///< Cumulative CPU time in seconds.

    CMatching m_nMatching[DEPTH]; ///< Matchings that make up comparator network in a form that makes searching faster. 

    int m_nStack[DEPTH] = {0}; ///< Stack to remove recursion from search.
    int m_nToS = 0; ///< Top of stack.
    int m_nNumMatchings = 0; ///< Number of matchings of this size.
    int m_nTop = 0; ///< Topmost level.

    void firstComparatorNetwork(int); ///< Set to first comparator network.
    bool nextComparatorNetwork(); ///< Change to next comparator network.
    void SynchMatchingRepresentations(int); ///< Synchronize the two different matching representations.
    void InitMatchingRepresentations(int); ///< Initialize the two different matching representations.

    virtual void SaveGeneratedSortingNetwork(); ///< Save comparator network.
    virtual void SetToS(); ///< Set top of stack.
    void search(); ///< Do the actual search.

    virtual void process(); ///< Process a candidate comparator network.

  public:
    CSearchableSortingNetwork(); ///< Constructor.

    virtual void backtrack(); ///< Backtracking search.
    void writeToLogFile(); ///< Write an entry to the log file.
}; //CSearchableSortingNetwork

#endif //__SearchableSortingNetwork_h__