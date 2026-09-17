// src/grading.cpp
#include "grading.h"

#include <algorithm>

#include "utilities.h"

double student_average(const double* const* scores, int student_index, const int num_assignments) {
    double total{};

    // Total the assignment scores for this student
    for (auto i{0}; i < num_assignments; i++) {
        total += scores[student_index][i];
    }

    return total / num_assignments;
}

double assignment_average(const double* const* scores, int assignment_index, const int num_students, const int num_assignments) {
    double total{};

    // Total this assignment's score down every student row
    for (auto i{0}; i < num_students; i++) {
        total += scores[i][assignment_index];
    }

    return total / num_students;
}

double class_average(const double* const* scores, const int num_students, const int num_assignments) {
    double total{};

    for (auto i{0}; i < num_students; i++) {
        for (auto j{0}; j < num_assignments; j++) {
            total += scores[i][j];
        }
    }

    return total / (num_students * num_assignments);
}

void find_extremes(const double* const* scores, int student_index, const int num_students, const int num_assignments, double& lowest, double& highest){
    // Start from a real score so the result is correct for any range of
    // values, including all-negative ones
    lowest = scores[student_index][0];
    highest = scores[student_index][0];

    for (auto i{1}; i < num_assignments; i++) {
        lowest = std::min(lowest, scores[student_index][i]);
        highest = std::max(highest, scores[student_index][i]);
    }
}

int count_grade(const double* const* scores, char target, const int num_students, const int num_assignments) {
    int count{};

    for (auto i{0}; i < num_students; i++) {
        if (letter_grade(student_average(scores, i, num_assignments)) == target) {
            count++;
        }
    }

    return count;
}

bool has_perfect_score(const double* const* scores, int student_index, const int num_students, const int num_assignments) {
    for (auto i{0}; i < num_assignments; i++) {
        if (scores[student_index][i] >= 100.0) {
            return true;
        }
    }

    return false;
}

bool is_at_risk(const double* const* scores, int student_index, const int num_students, const int num_assignments) {
    if (student_average(scores, student_index, num_students) < 70.0) {
        return true;
    }

    for (auto i{0}; i < num_assignments; i++) {
        if (scores[student_index][i] < 50.0) {
            return true;
        }
    }

    return false;
}
