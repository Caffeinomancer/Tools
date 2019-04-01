#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

enum DateFormat
{
  MDY = 0,
  DMY = 1,
  YMD = 2,
  DEFAULT_DATE = MDY //Change to your preference 
};

enum TimeFormat
{
  TWELVE = 0,
  TWENTYFOUR = 1,
  DEFAULT_TIME = TWENTYFOUR //Change to your preference
};


class Logger
{
public:
  static Logger* Instance();

  void Log(string messageToLog);

private:
  Logger(); // Private so we cannot call it
  ~Logger() {};
  Logger(Logger const&) {}; // Private copy constructor
  Logger& operator=(Logger const&) {}; // Private assignment operator
  
  static Logger* m_pInstance;

  void SetCurrentTime(DateFormat dateFormat = DateFormat::DEFAULT_DATE, 
                      TimeFormat timeFormat = TimeFormat::DEFAULT_TIME);

  const char* CURR_SESSION_LOG_FILE_NAME = "ErrorLog.txt";
  const char* APP_LOG_FILE_NAME = "CumulativeErrorLog.txt";
  const char* ERROR_SPLIT = "_______________________________";
  
  string m_CurrentTime;
  ofstream m_OutFile;
};