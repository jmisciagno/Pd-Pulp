/*
  ==============================================================================

    getstartup.cpp
    Created: 26 Feb 2022 1:25:03am
    Author:  John Misciagno

  ==============================================================================
*/

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(" \n\r\t\f\v");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string exec(std::string cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    /*
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    */
    if (!pipe) return ""; // silently fail
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return rtrim(result);
}