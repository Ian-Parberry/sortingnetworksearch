/// \file Defines.h
/// \brief Useful definitions.

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

#ifndef __Defines_h__
#define __Defines_h__

// Optimal depth of sorting networks:
//  2 inputs, depth 1
//  3 inputs, depth 3
//  4 inputs, depth 3
//  5 inputs, depth 5
//  6 inputs, depth 5
//  7 inputs, depth 6
//  8 inputs, depth 6
//  9 inputs, depth 7
// 10 inputs, depth 7
// 11 inputs, depth 8
// 12 inputs, depth 8

#define INPUTS 5 ///< Number of inputs.
#define DEPTH 5 ///< Depth.

#define COUNTONLY false ///< Define true to count but not output sorting networks.

#define odd(n) ((n) & 1) ///< Oddness test.
#define oddfloor(n) (odd(n)?(n):((n)-1)) ///< If even, round down to make odd.
#define evenceil(n) (odd(n)?((n)+1):(n)) ///< If odd, round up to make even.

#endif //__Defines_h__
