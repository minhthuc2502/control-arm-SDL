//$Header$
//------------------------------------------------------------------------------
//                              Log
//------------------------------------------------------------------------------
//IIOT_ROBOTIC_ARM_2018
//author: Quentin Pantostier
//created: 27/06/2018
/*
* This class provide log macros
*/
//------------------------------------------------------------------------------
#ifndef LOG_H
#define LOG_H

#include <chrono>
#include <bitset>
#include <mutex>
#include <string.h>

#define binaire(taille, variable) std::bitset<(taille)>(variable).to_string().c_str()

#define LOG(_l_, _i_, ...)\
          do { \
             printf("| %s | %s[%s, %d]: ", _l_, __FUNCTION__, _i_, __LINE__);\
             printf(__VA_ARGS__); \
             printf("\n"); \
          } while(0)
#define LOG_TIME() PrintTime();

#define LOG_I(...) LOG("INFO", ExtractFileName(__FILE__), __VA_ARGS__)
#define LOG_E(...) LOG_TIME() LOG("ERROR", ExtractFileName(__FILE__), __VA_ARGS__)
#define LOG_W(...) LOG_TIME() LOG("WARNING", ExtractFileName(__FILE__), __VA_ARGS__)

#ifdef DEBUG
#define LOG_D(...) LOG_TIME() LOG("DEBUG", ExtractFileName(__FILE__), __VA_ARGS__)
#endif

const char* ExtractFileName(const char* file);

void PrintTime();

#endif
