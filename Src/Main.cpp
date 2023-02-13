///\file main.cpp
/// \brief Main code for computing all second level candidates.

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

#include <iostream>

#include "Nearsort.h"

#include "ThreadManager.h"
#include "Task.h"
#include "Timer.h"

/// Create a thread manager and a timer. Insert tasks into the thread manager.
/// Start the timer. Report current data and time, and the number of available
/// threads. Spawn the threads and wait for them to terminate. Use the timer
/// to report current time, elapsed time, and CPU time, then have the thread
/// manager process the results.
/// \return 0 (What could possibly go wrong?)

int main(){
  CNearsort* pSearch = new CNearsort;
  pSearch->backtrack();
  delete pSearch;

  //CThreadManager* pThreadManager = new CThreadManager; //thread manager
  //CTimer* pTimer = new CTimer; //timer for elapsed and CPU time

  //for(size_t i=0; i<16; i++) //create empty tasks
  //  pThreadManager->Insert(new CTask);

  //pTimer->Start(); //start timing CPU and elapsed time

  //std::cout << "Start " << pTimer->GetTimeAndDate() << std::endl;
  //std::cout << pThreadManager->GetNumThreads() << " threads" << std::endl;
  //std::cout << std::flush;

  //pThreadManager->Spawn(); //spawn threads
  //pThreadManager->Wait(); //wait for threads to finish

  //std::cout << "Finish " << pTimer->GetTimeAndDate() << std::endl;
  //std::cout << "Elapsed time " << pTimer->GetElapsedTime() << std::endl;
  //std::cout << "CPU time " << pTimer->GetCPUTime() << std::endl;

  //pThreadManager->Process(); //process results

  ////clean up and exit

  //delete pTimer;
  //delete pThreadManager;

  return 0;
} //main