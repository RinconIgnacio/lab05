// src/grading.cpp
#include "grading.h"

#include <algorithm>

#include "utilities.h"

double student_average(const Student& student) {
    double total{};

    for (auto i{0}; i < assignment_count; i++) {
        total += student.scores[i];
    }

    return total / assignment_count;
}

double assignment_average(const Student students[], int assignment_index,
                          int num_students) {
    double total{};

    for (auto i{0}; i < num_students; i++) {
        total += students[i].scores[assignment_index];
    }

    return total / num_students;
}

double class_average(const Student students[], int num_students) {
    double total{};

    for (auto i{0}; i < num_students; i++) {
        for (auto j{0}; j < assignment_count; j++) {
            total += students[i].scores[j];
        }
    }

    return total / (num_students * assignment_count);
}

void find_extremes(const Student& student,
                   double& lowest, double& highest) {
    lowest = student.scores[0];
    highest = student.scores[0];

    for (auto i{1}; i < assignment_count; i++) {
        lowest = std::min(lowest, student.scores[i]);
        highest = std::max(highest, student.scores[i]);
    }
}

int count_grade(const Student students[], char target, int num_students) {
    int count{};

    for (auto i{0}; i < num_students; i++) {
        if (letter_grade(student_average(students[i])) == target) {
            count++;
        }
    }

    return count;
}

bool has_perfect_score(const Student& student) {
    for (auto i{0}; i < assignment_count; i++) {
        if (student.scores[i] >= 100.0) {
            return true;
        }
    }

    return false;
}

bool is_at_risk(const Student& student) {
    if (student_average(student) < 70.0) {
        return true;
    }

    for (auto i{0}; i < assignment_count; i++) {
        if (student.scores[i] < 50.0) {
            return true;
        }
    }

    return false;
}
