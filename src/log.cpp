/**
 * Copyright 2020 PHAM Minh Thuc
 * @file log.cpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File define log function to log the information in program and debug.
 */
#include "../includes/log.h"

const char* ExtractFileName(const char* file) {
  std::string s = file;
  std::string part;
  std::string delimiter = "/";

  int start = 0;
  size_t pos = s.find(delimiter);

  while (pos != std::string::npos) {
    start = pos + delimiter.length();
    pos = s.find(delimiter, start);
  }
  part = s.substr(start, pos - start);
  return part.c_str();
}

void PrintTime() {
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  unsigned int hours = std::chrono::duration_cast<std::chrono::hours>(now.time_since_epoch()).count()%24;
  unsigned int minutes = std::chrono::duration_cast<std::chrono::minutes>(now.time_since_epoch()).count()%60;
  unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count()%60;
  unsigned int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count()%1000;
  printf("< %02d:%02d:%02d.%04d >", hours, minutes, seconds, milliseconds);
}
