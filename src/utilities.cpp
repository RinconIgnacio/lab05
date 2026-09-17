// src/utilities.cpp
#include "utilities.h"

#include <string>

char letter_grade(double average) {
    if (average >= 90.0) {
        return 'A';
    } else if (average >= 80.0) {
        return 'B';
    } else if (average >= 70.0) {
        return 'C';
    } else if (average >= 60.0) {
        return 'D';
    } else {
        return 'F';
    }
}

double grade_points(char letter) {
    switch (letter) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        default:  return 0.0;
    }
}

std::string initials_of(const std::string& full_name) {
    std::string result{};

    result += full_name[0];
    result += ". ";

    auto index = full_name.find(' ');
    result += full_name[index + 1];
    result += '.';

    return result;
}

std::string pad_name(const std::string& full_name, int width) {
    std::string padded{full_name};
    padded.resize(static_cast<std::size_t>(width), ' ');
    return padded;
}
