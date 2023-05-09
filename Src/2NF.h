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
/// A first normal form sorting network that takes its second level from a 
/// generator that provides second level candidates unique up to symmetry.
/// Consider the sorting network in the figure below (left). We can construct
/// a new sorting network by swapping the pair of green channels with the pair
/// of blue channels. The resulting sorting network on the right has both the
/// min-max comparators that we have used so far (which put the maximum on the
/// bottom channel and the minimum on the top channel), and max-min comparators,
/// which put the maximum on the top channel and the minimum on the bottom
/// channel. See also `C1NF1`. In the figure below (right) the
/// arrows on the comparators point in the direction taken by the maximum.
/// Notice that we have created four max-min comparators and
/// a twist at the end of the channel to keep the outputs in sorted order. 
/// \image html 2NFa.png width=60%
/// We flip the first max-min comparator and the green and blue channels
/// to the right of it (below, left) and make the corresponding twist at the end
/// (below, right).
/// \image html 2NFb.png width=60%
/// We flip the second max-min comparator and the green and blue channels
/// to the right of it (below, left) and make the corresponding twist at the end
/// (below, right).
/// \image html 2NFc.png width=60%
/// We flip the third max-min comparator and the green and blue channels
/// to the right of it (below, left) and make the corresponding twist at the end
/// (below, right).
/// \image html 2NFd.png width=60%
/// We flip the fourth max-min comparator and the green and blue channels
/// to the right of it (below, left) and make the corresponding twist at the end
/// (below, right). Notice that the twists have cancelled out leaving us with
/// a new sorting network that has a different second level than the one we
/// started with.
/// \image html 2NFe.png width=60%
/// Our search therefore needs to include only one of the second level candidates
/// that can be obtained by permuting pairs of channels. In our example above,
/// only one of the two second levels in the figure below need appear in the
/// search. Notice that the comparator networks remain in first normal form.
/// \image html 2NFf.png width=25%
/// This speeds up the search by not having to iterate through all 
/// possibilities for the second level.

class C2NF: public CSearchable{ 
  protected:
    size_t m_nLevel2Index = 0; ///< Index of current level 2 candidate.

    void Save(); ///< Save comparator network.

  public:
    C2NF(CMatching&, const size_t); ///< Constructor.

    void Backtrack();  ///< Backtracking search.
}; //C2NF

#endif //__2NF_h_