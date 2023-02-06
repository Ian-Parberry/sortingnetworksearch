/// \file CPUtime.cpp
/// \brief Code for getting access to CPU time under Windows.

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

#include <windows.h>

/// Get CPU time in units of 100 nanoseconds, which is the default.
/// \return User CPU time in hundreds of nanoseconds.

long long CPUTimeInCentiNanoseconds(){  
  long long llCNS=0LL;
  HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());

  if(hProcess != NULL){
    FILETIME ftCreation, ftExit, ftKernel, ftUser;
    if(GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftKernel, &ftUser))
      llCNS = *((long long*)&ftUser);
    CloseHandle(hProcess);
  } //if
  return llCNS;
} //CPUTimeInCentiNanoseconds


/// Get CPU time in units of a millisecond.
/// \return User CPU time in ms.

unsigned int CPUTimeInMilliseconds(){
  return (unsigned int)(CPUTimeInCentiNanoseconds()/10000LL);
} //CPUTimeInMilliseconds