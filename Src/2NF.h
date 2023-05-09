/// \file 2NF.h
/// \brief Interface for the searchable second normal form sorting network `C2NF`.

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

#ifndef __2NF_h_
#define __2NF_h_

#include "Searchable.h"
#include "Level2Search.h"

/// \brief Second normal form searchable sorting network.
///
/// A first normal form sorting network that will be given its second level
/// from a generator `CLevel2Search` that provides second level candidates
/// unique up to symmetry.

class C2NF: public CSearchable{ 
  protected:
    size_t m_nLevel2Index = 0; ///< Index of current level 2 candidate.

    void Save(); ///< Save comparator network.

  public:
    C2NF(CMatching&, const size_t); ///< Constructor.

    void Backtrack();  ///< Backtracking search.
}; //C2NF

#endif //__2NF_h_