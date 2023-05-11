///\file main.cpp
/// \brief Main.
/// 
/// Prompt the user for width (number of inputs) and depth, then spawn a
/// multi-threaded backtracking search for sorting networks of the given
/// width and depth. The user is also prompted to choose whether the new
/// search hauristic nearsort2 is to the used.

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

#ifdef _DEBUG
  #include <vld.h> //Visual Leak Detector from http://vld.codeplex.com/
#endif

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Nearsort2.h"

#include "ThreadManager.h"
#include "Task.h"
#include "Timer.h"

#include "TernaryGrayCode.h"

/// \brief Get `size_t` from input.
///
/// Print a banner and read a value of type `size_t`.
/// \param strBanner Banner to print before reading.
/// \return `size_t` value from input.

size_t getn(const std::string& strBanner){
  std::cout << strBanner << std::endl << "> ";
  std::string strLine;
  std::getline(std::cin, strLine);

  return (size_t)std::stoi(strLine);
} //getn

/// \brief Check that depth is reasonable for width.
///
/// Check that depth is reasonable for width, that is, either equal to or one
/// less than the smallest known depth. An error message is printed to stdout
/// if it is not. This function assumes that \f$n \leq 12\f$.
/// \param n Width.
/// \param d Depth.
/// \return true if depth is reasonable for width, defaults to
/// false if width is too large..

bool CheckParams(const size_t n, const size_t d){
  bool ok = false;  

  switch(n){
    case 3:  case 4:  ok = d == 2 || d == 3; break;
    case 5:  case 6:  ok = d == 4 || d == 5; break;
    case 7:  case 8:  ok = d == 5 || d == 6; break;
    case 9:  case 10: ok = d == 6 || d == 7; break;
    case 11: case 12: ok = d == 7 || d == 8; break;
    default: ok = false;
  } //switch
    
  if(!ok){  
    std::cout << "Depth must be ";

    switch(n){
      case 3:  case 4:  std::cout << "2 or 3"; break;
      case 5:  case 6:  std::cout << "4 or 5"; break;
      case 7:  case 8:  std::cout << "5 or 6"; break;
      case 9:  case 10: std::cout << "6 or 7"; break;
      case 11: case 12: std::cout << "7 or 8"; break;
    } //switch

    std::cout << std::endl;
  } //if

  return ok;
} //CheckParams

/// \brief Read parameters for search.
///
/// Read the sorting network width and depth.
/// \param n [out] Width.
/// \param d [out] Depth.

void ReadParams(size_t& n, size_t& d){
  bool ok = false; //for loop control

  //read the width and make sure it is within range

  while(!ok){
    n = getn("Enter number of inputs. Must be at least 3 and at most 12.");
    ok = n >= 3 && n <= 12;
    if(!ok)std::cout << "Out of range" << std::endl;
  } //while

  //read the depth and make sure it is within range for the width chosen

  ok = false;

  while(!ok){
    d = getn("Enter depth.");
    ok = d >= 3 && d <= 8;
    if(!ok)std::cout << "Out of range" << std::endl;
    ok = ok && CheckParams(n, d);
  } //while
} //ReadParams

/// \brief Read optimization settings.
/// 
/// Read the optimization settings.
/// \param bNearsort2 [out] true to use nearsort2 heuristic (if appropriate).
/// \param d [out] Depth.

void ReadParams(bool& bNearsort2, const size_t d){
  if(d >= 5){ //deep enough for nearsort2 heuristic
    std::cout << "Use nearsort2 heuristic? [yn]" << std::endl << "> ";
    std::string strLine;
    std::getline(std::cin, strLine);
    bNearsort2 = strLine[0] == 'y' || strLine[0] == 'Y';
  } //if
} //ReadParams

/// \brief Save summary string.
///
/// Append a summary string to the log file `log.txt` and print it to 
/// the console.
/// \param s Summary string.

void SaveSummary(const std::string s){
  std::cout << s << std::endl; //print to console

  //append to log file

  std::ofstream logfile("log.txt", std::ios::app);
  logfile << s << std::endl;
  logfile.close();
} //SaveSummary

/// \brief Multi-threaded search.
///
/// Conduct multi-threaded sorting network search. First search for all level 2
/// candidates, then pass each one as a task to the thread manager. Get the
/// thread manager to spawn the search threads, wait until they terminate, then
/// process the results.
/// \param p Pointer to thread manager.
/// \param nDepth Sorting network depth.
/// \param bNearsort2 true to use nearsort2 heuristic (if appropriate).

void Search(CThreadManager* p, const size_t nDepth, const bool bNearsort2){
  CLevel2Search* pLevel2Search = new CLevel2Search(); //for level 2 matchings
  auto L2Matchings = pLevel2Search->GetMatchings(); //get level 2 matchings
  size_t i = 0; //index of current matching

  //insert search tasks to task queue

  for(auto matching: L2Matchings){ //for each level2 matching
    CSearchable* pSearch = nullptr; //for the searchable sorting network

    switch(nDepth){ //choose optimization depending on depth
      case 2: pSearch = new C2NF(matching, i++); break;
      case 3: pSearch = new CAutocomplete(matching, i++); break;
      case 4: pSearch = new CNearsort(matching, i++); break;
      default: //depth 5 or greater
        if(bNearsort2)
          pSearch = new CNearsort2(matching, i++); 
        else pSearch = new CNearsort(matching, i++); 
        break;
    } //switch

    p->Insert(new CTask(pSearch)); //insert search task
  } //for

  //perform multi-threaded backtracking search

  p->Spawn(); //spawn threads
  p->Wait(); //wait for threads to finish
  p->Process(); //process results

  delete pLevel2Search;
} //Search

/// \brief Main.
/// 
/// Get the sorting network width and depth from the user.
/// Conduct the search and process the results. 
/// \return 0 (What could possibly go wrong?)

int main(){
  size_t nWidth = 0; //sorting network width (number of inputs)
  size_t nDepth = 0; //sorting network depth (number of layers)
  ReadParams(nWidth, nDepth); //read from stdin
  CSettings::SetWidth(nWidth); //distribute width to all classes
  CSettings::SetDepth(nDepth); //distribute depth to all classes

  bool bFastGrayCode = false; //use fast Gray code flag
  bool bNearsort2 = false; //use nearsort2 flag
  ReadParams(bNearsort2, nDepth); //read from stdin

  CTimer* pTimer = new CTimer; //timer for elapsed and CPU time
  
  //print header to console and log file

  std::cout << "Start " << pTimer->GetTimeAndDate() << std::endl;

  std::string strSummary = "Searching for " +
    std::to_string(nWidth) + "-input sorting networks of depth " +
    std::to_string(nDepth);

  SaveSummary(strSummary);

  //multithreaded search
  
  CThreadManager* pThreadManager = new CThreadManager; //thread manager

  pTimer->Start(); //start timing CPU and elapsed time
  Search(pThreadManager, nDepth, bNearsort2); //this is where the search happens

  //print results to console and log file

  std::cout << "Finish " << pTimer->GetTimeAndDate() << std::endl;

  strSummary = std::to_string(pThreadManager->GetCount()) + " found in " +
    pTimer->GetElapsedTime() + " using " +
    pTimer->GetCPUTime() + " CPU time over " +
    std::to_string(pThreadManager->GetNumThreads()) + " threads";

  SaveSummary(strSummary);

  //clean up and exit
  
  delete pThreadManager;
  delete pTimer;

  return 0;
} //main
