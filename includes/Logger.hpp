//$Header$
//------------------------------------------------------------------------------
//                              Logger
//------------------------------------------------------------------------------
//IIOT_ROBOTIC_ARM_2018
//author: Quentin Pantostier
//created: 11/06/2018
/*
* This class provide log functions
* Deprecated
*/
//------------------------------------------------------------------------------
#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <chrono>
#include <bitset>
#include <mutex>
//#include <errno.h>

#define binaire(taille, variable) std::bitset<(taille)>(variable).to_string().c_str()


class Logger {
private:
  Logger(){};

  std::mutex printfMutex_;

  void PrintTime();
  std::string ExtractFileName(const char* file);

public:
  //unable copy with constructor or operator =
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  //method to return the static instance of Logger
  static Logger &GetInstance() {
    static Logger singleton_;
    return singleton_;
  }

  void LogERROR(const char* function, const char* file, long line, const char* msg, ...);
  void LogPERROR(const char* function, const char* file, long line, const char* libFunction);
  void LogDEBUG(const char* function, const char* file, long line, const char* msg, ...);
  void LogINFO(const char* tag, const char* msg, ...);

};
#endif
