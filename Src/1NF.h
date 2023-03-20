/// \file 1NF.h
/// \brief Interface for the first normal form sorting network `C1NF`.

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

#ifndef __1NF_h__
#define __1NF_h__

#include "SortingNetwork.h"

/// \brief Sorting network in first normal form.
///
/// A first normal form sorting network has comparators in the first
/// level between channels 0-1, 2-3, 4-5, etc. This simplifies the sorting
/// test since we need only test ternary Gray code strings instead of binary.

class C1NF: public CSortingNetwork{
  protected: 
    void initialize(); ///< Initialize the sorting test.
    bool sorts(); ///< Does it sort all inputs?
    bool stillsorts(const size_t); ///< Does it still sort when a bit is changed?
    bool evensorts(); ///< Does it sort if there are an odd number of inputs and we fix the value on the last channel?

  public:
    C1NF(); ///< Constructor.
}; //C1NF

#endif //__1NF_h__