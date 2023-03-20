/// \file Task.cpp
/// \brief Code for the task class `CTask`.

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
#include "Nearsort2.h"

/// Default constructor.
/// \param p Pointer to searchable sorting network.

CTask::CTask(CSearchable* p): 
  CBaseTask(), m_pSearch(p){
} //constructor

/// Perform this task. This function overrides `CBaseTask::Perform()`.

void CTask::Perform(){
  if(m_pSearch)
    m_pSearch->Backtrack();
} //Perform

/// Reader function for the number of sorting networks found.
/// \return The count.

const size_t CTask::GetCount() const{
  if(m_pSearch)
    return m_pSearch->GetCount();
  else return 0;
} //GetCount
