/// \file Task.h
/// \brief Header for the class CTask.

// MIT License
//
// Copyright (c) 2023 Ian Parberry
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef __Task_h__
#define __Task_h__

#include "BaseTask.h"

class CNearsort2;

/// \brief Task.
///
/// This task descriptor, derived from `CBaseTask`, overrides the 
/// `CBaseTask::Process()` function.

class CTask: public CBaseTask{
  private:
    CNearsort2* m_pSearch = nullptr; ///< Searchable sorting network.

  public:
    CTask(CNearsort2*); ///< Default constructor.

    virtual void Perform(); ///< Perform the task.
    const size_t GetCount() const; ///< Get count.
}; //CTask

#endif //__Task_h__
