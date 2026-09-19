#ifndef STUDENT_H
#define STUDENT_H

#include <string>

const int assignment_count = 5;

struct Student {
    std::string name;
    double scores[assignment_count];
};

#endif
