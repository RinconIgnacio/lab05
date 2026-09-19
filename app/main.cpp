// app/main.cpp

#include <iomanip>
#include <iostream>
#include <limits>

#include "grading.h"
#include "printing.h"
#include "student.h"

int main(int argc, char** argv) {
    int input{-1};

    Student students[]{
        {"Ada Lovelace", {95.0, 88.5, 92.0, 78.0, 100.0}},
        {"Grace Hopper", {72.5, 80.0, 68.0, 91.0, 85.5}},
        {"Alan Turing", {55.0, 62.5, 48.0, 70.0, 59.0}},
        {"Katherine Johnson", {100.0, 98.0, 95.5, 99.0, 97.0}},
        {"Linus Torvalds", {83.0, 79.5, 88.0, 84.0, 91.5}},
        {"Bill Gates", {45.0, 52.0, 61.0, 38.5, 55.0}}
    };

    const int num_students{static_cast<int>(std::size(students))};

    while (input != 0) {
        std::cout << "\n=== GRADEBOOK ===\n"
                  << "1. Full Report\n"
                  << "2. Grade Distribution\n"
                  << "3. Assignment Averages\n"
                  << "4. Roster\n"
                  << "5. Class Average\n"
                  << "0. Quit\n"
                  << "Choice: ";

        if (std::cin >> input) {
            switch (input) {
                case 1: {
                    print_header(num_students);

                    for (auto row{0}; row < num_students; row++) {
                        print_student_row(students, row);
                    }

                    std::cout << "\t* perfect score\t! at risk\n";
                    break;
                }
                case 2: {
                    print_histogram(students, num_students);
                    break;
                }
                case 3: {
                    print_assignment_summary(students, num_students);
                    break;
                }
                case 4: {
                    print_roster(students, num_students);
                    break;
                }
                case 5: {
                    double avg{class_average(students, num_students)};

                    std::cout << "Class Average: " << std::setw(6)
                              << std::setprecision(2) << std::fixed << avg
                              << '\n';
                    break;
                }
                case 0: {
                    return 0;
                }
                default: {
                    std::cout << "Invalid choice, try again\n";
                }
            }
        } else {
            // Clear a failed read and discard the broken input
            std::cout << "Invalid input!\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
