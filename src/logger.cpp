/**
 * @file logger.cpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief another version of log file. Don't be used.
 */
#include "Logger.hpp"

//------------------------------------------------------------------------------
//  Public methods
//------------------------------------------------------------------------------
void Logger::LogERROR(const char* function, const char* file, long line, const char* msg, ...){
  va_list args;
  va_start(args, msg);
  std::string fileName = ExtractFileName(file);
  printfMutex_.lock();
  printf("ERROR!!!: ");
  PrintTime();
  printf("%s[%s,%ld]-> ", function, fileName.c_str(), line);
  printfMutex_.unlock();
  vprintf(msg, args);
  va_end(args);
}

void Logger::LogPERROR(const char* function, const char* file, long line, const char* libFunction){
  printfMutex_.lock();
  printf("ERROR!!!: ");
  perror(libFunction);
  std::string fileName = ExtractFileName(file);
  PrintTime();
  printf("%s[%s,%ld]\n", function, fileName.c_str(), line);
  printfMutex_.unlock();
}

void Logger::LogDEBUG(const char* function, const char* file, long line, const char* msg, ...){
  va_list args;
  va_start(args, msg);
  std::string fileName = ExtractFileName(file);
  printfMutex_.lock();
  PrintTime();
  printf("%s[%s,%ld]-> ", function, fileName.c_str(), line);
  vprintf(msg, args);
  printfMutex_.unlock();
  va_end(args);
}

void Logger::LogINFO(const char* tag, const char* msg, ...){
  va_list args;
  va_start(args, msg);
  printfMutex_.lock();
  printf("%s-> ", tag);
  vprintf(msg, args);
  printfMutex_.unlock();
  va_end(args);
}
//------------------------------------------------------------------------------
//  Private methods
//------------------------------------------------------------------------------
std::string Logger::ExtractFileName(const char* file){
  std::string s = file;
  std::string part;
  std::string delimiter = "/";

  int start = 0;
  size_t pos = s.find(delimiter);

  while( pos != std::string::npos) {
    start = pos + delimiter.length();
    pos = s.find(delimiter, start);
  }
  part = s.substr(start, pos - start);
  return part;
}

void Logger::PrintTime(){
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  unsigned int hours = std::chrono::duration_cast<std::chrono::hours>(now.time_since_epoch()).count()%24;
  unsigned int minutes = std::chrono::duration_cast<std::chrono::minutes>(now.time_since_epoch()).count()%60;
  unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count()%60;
  unsigned int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count()%1000;
  printf("%02d:%02d:%02d.%04d, ", hours, minutes, seconds, milliseconds);
}

//void Logger::LogFile()
