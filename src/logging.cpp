//
// Created by Conni Bilham on 10/07/2023.
//

#define RESET   "\033[0m"
#define BLACK   "\033[30m"                 /* Black */
#define RED     "\033[31m"                 /* Red */
#define GREEN   "\033[32m"                 /* Green */
#define YELLOW  "\033[33m"                 /* Yellow */
#define BLUE    "\033[34m"                 /* Blue */
#define MAGENTA "\033[35m"                 /* Magenta */
#define CYAN    "\033[36m"                 /* Cyan */
#define WHITE   "\033[37m"                 /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#include <iomanip>
#include "../include/logging.h"

void logging::log(const std::string& message) {
    auto c_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << BOLDWHITE << "[" << std::put_time(std::localtime(&c_time), "%F %T") << "] " << RESET << message << std::endl;
}

void logging::info(const std::string& message) {
    log(GREEN + std::string("INFO:    ") + RESET + message);
}

void logging::verbose(const std::string& message) {
    log(MAGENTA + std::string("VERBOSE: ") + RESET + message);
}

void logging::error(const std::string& message) {
    log(RED + std::string("ERROR: ") + RESET + message);
}

void logging::debug(const std::string& message) {
    log(BLUE + std::string("DEBUG:   ") + RESET + message);
}