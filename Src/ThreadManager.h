/// \file ThreadManager.h
/// \brief Header for the class CThreadManager.

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

#ifndef __ThreadManager_h__
#define __ThreadManager_h__

#include "BaseThreadManager.h"
#include "Task.h"

/// \brief Thread manager.
///
/// The thread manager takes care of the health and feeding of the threads.
/// It is derived from `CBaseThreadManager<CTask>`. It has a function
/// `CThreadManager::ProcessTask()` which overrides the virtual function
/// `CBaseThreadManager::ProcessTask()` in order to process the results stored
/// in the completed task descriptor.

class CThreadManager: public CBaseThreadManager<CTask>{
  protected:
    void ProcessTask(CTask*); ///< Process the result of a task.

  public:
    CThreadManager(); ///< Constructor.
}; //CThreadManager

#endif //__ThreadManager_h__
