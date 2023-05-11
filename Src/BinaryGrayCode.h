/// \file BinaryGrayCode.h
/// \brief Interface for the binary reflected Gray code generator `CBinaryGrayCode`.

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

#ifndef __BinaryGrayCode_h__
#define __BinaryGrayCode_h__

#include "Defines.h"
#include "Settings.h"

/// \brief Binary reflected Gray code generator.
///
/// A binary Gray code generates all strings of a fixed number of bits in such
/// a way that each string differs from the previous one in exactly one bit.
/// For example, the following is a binary reflected Gray code on 4 bits
/// with each bit string followed by the index of the changed bit (from
/// right to left starting at zero).
/// 
/// \code
/// 0000
/// 0001 0
/// 0011 1
/// 0010 0
/// 0110 2
/// 0111 0
/// 0101 1
/// 0100 0
/// 1100 3
/// 1101 0
/// 1111 1
/// 1110 0
/// 1010 2
/// 1011 0
/// 1001 1
/// 1000 0
/// \endcode
/// 
/// This class implements a nonrecursive version of the binary reflected Gray
/// code generation algorithm from the following paper:
///
/// > Bitner, Ehrlich, and Reingold, "Efficient generation of the Binary
/// > Reflected Gray Code and its applications", _Communications of the ACM_,
/// > Vol. 19, No. 9, pp 517-521, 1976.

class CBinaryGrayCode: public CSettings{
  protected:
    size_t m_nBit[MAXINPUTS + 3] = {0}; ///< Current code word.
    size_t m_nStack[MAXINPUTS + 3] = {0}; ///< Stack to remove recursion.

  public:
    virtual void Initialize(); ///< Get first code word.
    virtual size_t Next(); ///< Get next code word.

    void Print(); ///< Debug print.
}; //CBinaryGrayCode

#endif //__BinaryGrayCode_h__