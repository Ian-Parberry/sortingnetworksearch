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
#include <fstream>

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
  CTimer* pTimer = new CTimer; //timer for elapsed and CPU time
  pTimer->Start(); //start timing CPU and elapsed time

  //print header information to console

  std::cout << "Start " << pTimer->GetTimeAndDate() << std::endl;
  std::cout << std::flush;

  CLevel2Search* pLevel2Search = new CLevel2Search(); //for level 2 matchings
  auto L2Matchings = pLevel2Search->GetMatchings(); //get level 2 matchings
  size_t i = 0; //index of current matching

  //create thread manager and insert tasks to task queue

  CThreadManager* pThreadManager = new CThreadManager; //thread manager

  for(auto matching: L2Matchings) //for each level2 matching
    pThreadManager->Insert(new CTask(new CNearsort(matching, i++))); //insert task

  //perform multi-threaded backtracking search

  pThreadManager->Spawn(); //spawn threads
  pThreadManager->Wait(); //wait for threads to finish
  pThreadManager->Process(); //process results

  std::cout << "Finish " << pTimer->GetTimeAndDate() << std::endl;

  //compose string that summarizes the search results

  const std::string strSummary = std::to_string(pThreadManager->GetCount()) +
    " " + std::to_string(INPUTS) + "-input sorting networks of depth " +
    std::to_string(DEPTH) +" found in " + pTimer->GetElapsedTime() + " using " +
    pTimer->GetCPUTime() + " CPU time over " +
    std::to_string(pThreadManager->GetNumThreads()) + " threads";

  std::cout << strSummary << std::endl; //print summary to log file

  //append summary to log file

  std::ofstream logfile("log.txt", std::ios::app);
  logfile << strSummary << std::endl;
  logfile.close();

  ////clean up and exit

  delete pTimer;
  delete pThreadManager;
  delete pLevel2Search;

  return 0;
} //main
