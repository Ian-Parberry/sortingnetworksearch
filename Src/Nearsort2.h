/// \file Nearsort.h
/// \brief Interface for the searchable sorting network with the nearsort2 
/// heuristic `CNearsort2`.

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

#ifndef __Nearsort2_h__
#define __Nearsort2_h__

#include "Nearsort.h"

/// \brief Searchable sorting network with nearsort2.
///
/// CNearsort2 is a version of CNearsort that uses the nearsort2 heuristic, 
/// which is based on reachability, to prune two levels from the end.

class CNearsort2: public CNearsort{
  protected: 
    bool StillNearsorts2(const size_t delta); ///< Does it still nearsort with this input change?
    bool EvenNearsorts2(); ///< Does it nearly sort, even number of inputs?
    bool Nearsorts2(); ///< Does it nearly sort?

    void Process(); ///< Process a candidate comparator network.
    void SetToS(); ///< Set top of stack.

public:
  CNearsort2(CMatching&, const size_t); ///< Constructor.
}; //CNearsort2

#endif //__Nearsort2_h__
