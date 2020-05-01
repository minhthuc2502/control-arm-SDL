/**
 * @file log.h
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File define log function to log the information in program and debug.
 */
#ifndef LOG_H
#define LOG_H

#include <chrono>
#include <bitset>
#include <mutex>
#include <string.h>

#define binaire(taille, variable) std::bitset<(taille)>(variable).to_string().c_str()              /*!< bianire  */

#define LOG(_l_, _i_, ...) do { \
             printf("| %s | %s[%s, %d]: ", _l_, __FUNCTION__, _i_, __LINE__);\
             printf(__VA_ARGS__); \
             printf("\n"); \
          } while(0)                                                                               /*!< Log function */
#define LOG_TIME() PrintTime();                                                                    /*!< Log time function */

#define LOG_I(...) LOG("INFO", ExtractFileName(__FILE__), __VA_ARGS__)                             /*!< Log info function */
#define LOG_E(...) LOG_TIME() LOG("ERROR", ExtractFileName(__FILE__), __VA_ARGS__)                 /*!< Log error function */
#define LOG_W(...) LOG_TIME() LOG("WARNING", ExtractFileName(__FILE__), __VA_ARGS__)               /*!< Log warning function */

#ifdef DEBUG
#define LOG_D(...) LOG_TIME() LOG("DEBUG", ExtractFileName(__FILE__), __VA_ARGS__)                 /*!< Log debug function */
#endif

/**
* @brief method extract file name
* @param file real path of file
* @return file name
* */
const char* ExtractFileName(const char* file);

/**
* @brief method print time
* */
void PrintTime();

#endif
