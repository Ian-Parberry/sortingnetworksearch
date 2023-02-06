/// \file Autocomplete.h
/// \brief Interface for the fast searchable sorting network CAutocomplete.

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

#ifndef __Autocomplete_h__
#define __Autocomplete_h__

#include "SearchableSortingNetwork2NF.h"

/// \brief Searchable second normal form sorting network with autocomplete.
///
/// A searchable second normal form sorting network that tries to autocomplete
/// the last level instead of iterating through all possibilities.

class CAutocomplete: public C2NFSearchableSortingNetwork{
  protected:  
    void SetToS(); ///< Set top of stack.
    bool stillsorts(const size_t); ///< Does it still sort when a bit is changed?
    void initSortingTest(); ///< Initialize the sorting test. 
    void initLastLevel(); ///< Initialize the last level of the comparator network.
    bool sorts(); ///< Does it sort?
}; //CAutocomplete

#endif //__Autocomplete_h__
