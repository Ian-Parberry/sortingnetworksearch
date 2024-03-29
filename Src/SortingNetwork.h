/// \file SortingNetwork.h 
/// \brief Interface for the sorting network `CSortingNetwork`.

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

#ifndef __SortingNetwork_h__
#define __SortingNetwork_h__

#include "Defines.h"

#include "BinaryGrayCode.h"
#include "ComparatorNetwork.h"

/// \brief Sorting network
///
/// `CSortingNetwork` combines a comparator network with a binary Gray
/// code generator `CBinaryGrayCode` to test whether the comparator network
/// sorts based on the Zero-One Principle, which says that a comparator network
/// is a sorting network if and only if it sorts all inputs made up of only 
/// zeros and ones. See Knuth Volume 3 for the details. Using a Gray code 
/// generator instead of a standard binary string generator simplifies and
/// speeds up the test. The main function of interest here is
/// `CSortingNetwork::Sorts()` which returns `true` if the base comparator
/// network sorts all inputs.

class CSortingNetwork: public CComparatorNetwork{
  protected: 
    CBinaryGrayCode *m_pGrayCode = nullptr; ///< Gray code generator.
    size_t m_nValue[MAXDEPTH][MAXINPUTS] = {0}; ///< Values at each level when sorting.
    size_t m_nZeros = 0; ///< Number of zeros in the input.

    virtual void Initialize(); ///< Initialize the sorting test.
    virtual bool Sorts(); ///< Does it sort?

    virtual bool StillSorts(const size_t); ///< Does it still sort when a bit is changed?

    size_t FlipInput(size_t, const size_t, const size_t); ///< Recompute network values when a bit is changed.
    void InitValues(const size_t, const size_t); ///< Initialize the network values to the all zero input.

  public:
    CSortingNetwork(); ///< Constructor.
    ~CSortingNetwork(); ///< Destructor.
}; //CSortingNetwork

#endif //__SortingNetwork_h__