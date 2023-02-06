/// \file Task.cpp
/// \brief Code for the class CTask.

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

#include <chrono>
#include <thread>

#include "Task.h"

/// Default constructor. All this does is call the `CBaseTask` default
/// constructor. If you have any initialization code, then it should go here.

CTask::CTask(): CBaseTask(){
} //constructor

/// Perform this task. This function overrides `CBaseTask::Perform()`. The
/// task described here is merely to wait a short period of time. Your task
/// code should go here instead.

void CTask::Perform(){
  const size_t delay = 400*(m_nThreadId + 1);
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
} //Perform
