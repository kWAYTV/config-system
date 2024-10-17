#pragma once

#include <iostream>
#include <string>

// ANSI color codes
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Logging macros
#define LOG_INFO(message)    std::cout << ANSI_COLOR_GREEN   << "[+] " << ANSI_COLOR_RESET << message << std::endl
#define LOG_ERROR(message)   std::cout << ANSI_COLOR_RED     << "[-] " << ANSI_COLOR_RESET << message << std::endl
#define LOG_WARNING(message) std::cout << ANSI_COLOR_YELLOW  << "[!] " << ANSI_COLOR_RESET << message << std::endl
#define LOG_INPUT(message)   std::cout << ANSI_COLOR_BLUE    << "[?] " << ANSI_COLOR_RESET << message << std::endl

// Helper function to get user input
inline std::string get_user_input(const std::string& prompt) {
    std::string input;
    LOG_INPUT(prompt);
    std::getline(std::cin, input);
    return input;
}

