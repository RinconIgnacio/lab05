// src/printing.cpp
#include "printing.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "grading.h"
#include "utilities.h"

void print_header(const int num_students, const int num_assignments) {
    std::cout << pad_name("STUDENT", num_students);

    for (auto i{0}; i < num_assignments; i++) {
        std::cout << std::setw(5) << "A" << i;
    }

    std::cout << std::setw(8) << "AVG" << std::setw(6) << "GRADE" << '\n';

    for (auto i{0}; i < 60; i++) {
        std::cout << '-';
    }

    std::cout << '\n';
}

void print_student_row(const std::string& name, const double* const* scores, int student_index, const int num_students, const int num_assignments) {
    std::cout << pad_name(name, name_width);

    for (auto i{0}; i < num_assignments; i++) {
        std::cout << std::setw(6) << std::setprecision(1) << std::fixed
                  << scores[student_index][i];
    }

    double avg{student_average(scores, student_index, num_assignments)};

    std::cout << std::setw(8) << std::setprecision(2) << std::fixed << avg
              << " \t" << letter_grade(avg);

    if (has_perfect_score(scores, student_index, num_students, num_assignments)) {
        std::cout << "  *";
    }

    if (is_at_risk(scores, student_index, num_students, num_assignments)) {
        std::cout << "  !";
    }

    std::cout << '\n';
}

void print_histogram(const double* const* scores, const int num_students, const int num_assignments) {
    const char letters[]{'A', 'B', 'C', 'D', 'F'};

    std::cout << "\nGRADE DISTRIBUTION\n";

    for (auto letter : letters) {
        auto count{count_grade(scores, letter, num_students, num_assignments)};

        std::cout << letter << " | ";

        for (auto i{0}; i < count; i++) {
            std::cout << '#';
        }

        std::cout << "\t\t(" << count << ")\n";
    }
}

void print_assignment_summary(const double* const* scores, const int num_students, const int num_assignments) {
    std::cout << "\nASSIGNMENT AVERAGES\n";

    for (auto i{0}; i < num_assignments; i++) {
        auto avg{assignment_average(scores, i, num_students, num_assignments)};

        std::cout << "  A" << i + 1 << ": " << std::setw(6)
                  << std::setprecision(2) << std::fixed << avg;

        if (avg < 70.0) {
            std::cout << "\t<-- review this assignment";
        }

        std::cout << '\n';
    }
}

void print_roster(const std::string* names, int name_count) {
    std::cout << "\nROSTER\n";

    // names is a pointer to the first element; it carries no size of its
    // own, so name_count is how far we are permitted to walk
    for (auto i{0}; i < name_count; i++) {
        std::cout << initials_of(names[i]) << '\t' << names[i] << '\n';
    }
}
