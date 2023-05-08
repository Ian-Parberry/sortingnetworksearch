/// \file Matching.h
/// \brief Interface for the matching `CMatching`.

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

#ifndef __Matching_h__
#define __Matching_h__

#include <string>

#include "Defines.h"
#include "Settings.h"

/// \brief Perfect matching.
///
/// `CMatching` represents a perfect matching... well, as
/// perfect as it can be if its size is odd.

class CMatching: public CSettings{
  private:   
    size_t m_nMatching[MAXINPUTS + 1] = {0}; ///< Matching.
    size_t m_nMap[MAXINPUTS + 1] = {0}; ///< Matching index map.
    int m_nStack[MAXINPUTS + 1] = {0}; ///< Stack to remove recursion from permutation.
    
    void SwapPair(int[], size_t, size_t); ///< Swap pair.

  public:
    CMatching(); ///< Void constructor
    CMatching(const CMatching&); ///< Copy constructor.

    void Initialize(); ///< Initialize.
    bool Next(); ///< Advance to next matching.

    void Swap(const size_t, const size_t); ///< Swap.

    void Normalize(); ///< Normalize.
    
    size_t& operator[](const size_t); ///< Overloaded index operator.
    const size_t operator[](const size_t) const; ///< Overloaded index operator.
    //CMatching& operator=(const CMatching&); ///< Overloaded assignment operator.
    operator std::string() const; ///< Cast to a string.
    
    //friend bool operator<(const CMatching& k1, const CMatching& k2); ///< Less than.
    //friend bool operator==(const CMatching& k1, const CMatching& k2); ///< Equals.
}; //CMatching

#endif //__Matching_h__