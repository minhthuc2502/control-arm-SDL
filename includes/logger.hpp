/**
 * @file logger.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief another version of log file. Don't be used.
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <chrono>
#include <bitset>
#include <mutex>

#define binaire(taille, variable) std::bitset<(taille)>(variable).to_string().c_str()       /*!< bianire  */

/**
 * @brief log class
*/
class Logger {
private:
  /** @brief constructor 
   *  Constructor of class Logger
    */
  Logger(){};

  std::mutex printfMutex_;        /*!< print mutex */
  /**
   * @brief print time
  */
  void PrintTime();
  /**
   * @brief extract file name from path
   * @param file real path of file
   * @return file name
  */
  std::string ExtractFileName(const char* file);

public:
  /**
   * @brief unable copy with constructor or operator =
  */
  Logger(const Logger&) = delete;
  /**
   * @brief unable copy with constructor or operator =
  */
  Logger& operator=(const Logger&) = delete;

  /**
   * @brief method to return the static instance of Logger
  */
  static Logger &GetInstance() {
    static Logger singleton_;
    return singleton_;
  }
  /**
   * @brief Log error function
   * @param function name of function
   * @param file name of file
   * @param line index of line
   * @param msg message
  */
  void LogERROR(const char* function, const char* file, long line, const char* msg, ...);
  /**
   * @brief Log perror function
   * @param function name of function
   * @param file name of file
   * @param line index of line
   * @param libFunction lib function
  */
  void LogPERROR(const char* function, const char* file, long line, const char* libFunction);
  /**
   * @brief Log debug function
   * @param function name of function
   * @param file name of file
   * @param line index of line
   * @param msg message
  */
  void LogDEBUG(const char* function, const char* file, long line, const char* msg, ...);
    /**
   * @brief Log info function
   * @param tag tag
   * @param msg message
  */
  void LogINFO(const char* tag, const char* msg, ...);
};
#endif
