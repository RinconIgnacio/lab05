// src/printing.cpp
#include "printing.h"

#include <iomanip>
#include <iostream>

#include "grading.h"
#include "utilities.h"

void print_header(int num_students) {
    std::cout << pad_name("STUDENT", num_students);

    for (auto i{0}; i < assignment_count; i++) {
        std::cout << std::setw(5) << "A" << i;
    }

    std::cout << std::setw(8) << "AVG" << std::setw(6) << "GRADE" << '\n';

    for (auto i{0}; i < 60; i++) {
        std::cout << '-';
    }

    std::cout << '\n';
}

void print_student_row(const Student students[], int student_index) {
    std::cout << pad_name(students[student_index].name, name_width);

    for (auto i{0}; i < assignment_count; i++) {
        std::cout << std::setw(6) << std::setprecision(1) << std::fixed
                  << students[student_index].scores[i];
    }

    double avg{student_average(students[student_index])};

    std::cout << std::setw(8) << std::setprecision(2) << std::fixed << avg
              << " \t" << letter_grade(avg);

    if (has_perfect_score(students[student_index])) {
        std::cout << "  *";
    }

    if (is_at_risk(students[student_index])) {
        std::cout << "  !";
    }

    std::cout << '\n';
}

void print_histogram(const Student students[], int num_students) {
    const char letters[]{'A', 'B', 'C', 'D', 'F'};

    std::cout << "\nGRADE DISTRIBUTION\n";

    for (auto letter : letters) {
        auto count{count_grade(students, letter, num_students)};

        std::cout << letter << " | ";

        for (auto i{0}; i < count; i++) {
            std::cout << '#';
        }

        std::cout << "\t\t(" << count << ")\n";
    }
}

void print_assignment_summary(const Student students[], int num_students) {
    std::cout << "\nASSIGNMENT AVERAGES\n";

    for (auto i{0}; i < assignment_count; i++) {
        auto avg{assignment_average(students, i, num_students)};

        std::cout << "  A" << i + 1 << ": " << std::setw(6)
                  << std::setprecision(2) << std::fixed << avg;

        if (avg < 70.0) {
            std::cout << "\t<-- review this assignment";
        }

        std::cout << '\n';
    }
}

void print_roster(const Student students[], int num_students) {
    std::cout << "\nROSTER\n";

    for (auto i{0}; i < num_students; i++) {
        std::cout << initials_of(students[i].name) << '\t'
                  << students[i].name << '\n';
    }
}
