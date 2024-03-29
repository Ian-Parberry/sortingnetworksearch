/// \file Settings.h
/// \brief Settings.

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

#ifndef __Settings_h__
#define __Settings_h__

/// \brief The common variables class.
///
/// A singleton class that encapsulates things that are common to
/// different components. Making it a singleton class means that we can avoid
/// passing its member variables around as parameters, which makes the code 
/// minisculely faster, and more importantly, makes the code more readable by
/// reducing function clutter.

class CSettings{
  protected:
    static size_t m_nWidth; ///< Comparator network width.
    static size_t m_nDepth; ///< Comparator network depth.

  public:
    static void SetWidth(const size_t); ///< Set width.
    static void SetDepth(const size_t); ///< Set depth.
}; //CSettings

#endif
