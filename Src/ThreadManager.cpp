/// \file ThreadManager.cpp
/// \brief Code for the class CThreadManager.

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

#include <functional>
#include <iostream>

#include "ThreadManager.h"

/// Default constructor. All this does is call the `CBaseThreadManager`
/// default constructor. If you have any initialization code, then it should
/// go here.

CThreadManager::CThreadManager(): CBaseThreadManager(){
} //constructor

/// Overrides the virtual function `CBaseThreadManager::ProcessTask()` in order
/// to process the results stored in the completed task descriptor. In this
/// case it means printing to the console a list of a task identifiers and
/// the thread identifier of the thread that completed each task. Your task
/// processing code should go here instead.
/// \param pTask Pointer to a task descriptor.

void CThreadManager::ProcessTask(CTask* pTask){
  if(pTask) //safety
    std::cout << "Task " << pTask->GetTaskId() <<
      " performed by thread " << pTask->GetThreadId() << std::endl; 
} //ProcessTask
