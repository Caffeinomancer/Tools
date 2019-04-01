#include "Logger.h"

Logger::Logger()
{
  //Truncate curr session log
  m_OutFile.open(CURR_SESSION_LOG_FILE_NAME, ios::trunc);
  m_OutFile.close();
}

Logger* Logger::Instance()
{
  if (!m_pInstance)
    m_pInstance = new Logger;

  return m_pInstance;
}

void Logger::Log(string messageToLog)
{
  SetCurrentTime();

  //Begin writing to session log
  m_OutFile.open(CURR_SESSION_LOG_FILE_NAME, ios::out | ios::app);

  if (m_OutFile.is_open())
  {
    m_OutFile << ERROR_SPLIT << "\n";
    
    m_OutFile << m_CurrentTime << "\n";
    m_OutFile << messageToLog << "\n";
  }

  else
    cout << "Could not open " << CURR_SESSION_LOG_FILE_NAME;

  m_OutFile.close();

  //Begin writing to cumulative log
  m_OutFile.open(APP_LOG_FILE_NAME, ios::out | ios::app);

  if (m_OutFile.is_open())
  {
    m_OutFile << ERROR_SPLIT << "\n";

    m_OutFile << m_CurrentTime << "\n";
    m_OutFile << messageToLog << "\n";
  }

  else
    cout << "Could not open " << CURR_SESSION_LOG_FILE_NAME;

  m_OutFile.close();
}

void Logger::SetCurrentTime(DateFormat dateFormat, TimeFormat timeFormat)
{
  time_t rawTime = time(NULL);
  
  struct tm tm;
  localtime_s(&tm, &rawTime);
  
  string currTime;

  switch (dateFormat)
  {
  case DateFormat::MDY:
    //EX. 2-19-2019  
    currTime += to_string(tm.tm_mon + 1) + "-";
    currTime += to_string(tm.tm_mday) + "-";
    currTime += to_string(tm.tm_year + 1900);
    break;
  case DateFormat::DMY:
    //EX 19-2-2019
    currTime += to_string(tm.tm_mday) + "-";
    currTime += to_string(tm.tm_mon + 1) + "-";
    currTime += to_string(tm.tm_year + 1900);

    break;
  case DateFormat::YMD:
    //EX 2019-2-19
    currTime += to_string(tm.tm_year + 1900);
    currTime += to_string(tm.tm_mon + 1) + "-";
    currTime += to_string(tm.tm_mday) + "-";
 
    break;
  }

  switch (timeFormat)
  {
  case TimeFormat::TWELVE:
    if (tm.tm_hour >= 13 && tm.tm_hour < 24) //1-11pm
      currTime += " " + to_string((tm.tm_hour - 12)) + "pm";
    else if(tm.tm_hour == 12) // 12pm
      currTime += " " + to_string((tm.tm_hour)) + "pm";
    else if(tm.tm_hour == 24) // 12am
      currTime += " " + to_string((tm.tm_hour)) + "am";
    else // 1 - 11am
      currTime += " " + to_string(tm.tm_hour) + "am";

    currTime += ":" + to_string(tm.tm_min);
    currTime += ":" + to_string(tm.tm_sec);
    break;

  case TimeFormat::TWENTYFOUR:
    currTime += " " + to_string(tm.tm_hour);
    currTime += ":" + to_string(tm.tm_min);
    currTime += ":" + to_string(tm.tm_sec);
    break;
  }

  m_CurrentTime = currTime;
}