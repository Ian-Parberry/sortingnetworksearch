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
/// A _first normal form_ sorting network has comparators in the first
/// level between channels 0-1, 2-3, 4-5, etc. If there exists an \f$n\f$-input
/// sorting network of depth \f$d\f$, then there exists an \f$n\f$-input
/// sorting network of depth \f$d\f$ that is in first normal form.
/// For example, the sorting network in the figure below (left) is not in first
/// normal form. We swap the green and blue channels to get the sorting network
/// on the right, which has both the min-max comparators that we have used so
/// far (which put the maximum on the bottom channel and the minimum on the top
/// channel), and max-min comparators, which put the maximum on the top channel
/// and the minimum on the bottom channel. In the figure below (right) the
/// arrows on the comparators point in the direction taken by the maximum.
/// Notice that we have created a single max-min comparator (shown in red) and
/// a twist at the end of the channel to keep the outputs in sorted order.
/// \image html 1NFa.png width=60%
/// Next, as shown in the figure below (left) we flip the max-min comparator by
/// swapping the channels to its right shown in green and blue,
/// and introducing the corresponding twist at the end. This will undo the twist
/// from the first step. In general there may be
/// more than two steps but the twists will always cancel out as in this
/// example. The resulting sorting network below (right) is in first normal form.
/// \image html 1NFb.png width=60%
/// Restricting the search to sorting networks in first normal form therefore
/// does us no harm, and it speeds up the search by not having to iterate 
/// through all possibilities for the first level. In addition, it speeds up 
/// the sorting test since we need only test ternary Gray code strings
/// (00, 01, and 11 as inputs to pairs of channels) instead of binary Gray code
/// strings. These are generated using an instance of `CTernaryGrayCode`
/// instead of the instance of `CBinaryGrayCode`. 

class C1NF: public CSortingNetwork{
  protected: 
    void Initialize(); ///< Initialize the sorting test.
    bool Sorts(); ///< Does it sort all inputs?

    bool StillSorts(const size_t); ///< Does it still sort when a bit is changed?
    bool EvenSorts(); ///< Does it sort if there are an odd number of inputs and we fix the value on the last channel?

  public:
    C1NF(); ///< Constructor.
}; //C1NF

#endif //__1NF_h__