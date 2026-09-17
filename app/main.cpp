// app/main.cpp

#include <string>
#include <limits>
#include <iostream>
#include <iomanip>

#include "printing.h"
#include "grading.h"

int main(int argc, char** argv) {
    int input{-1};

    const std::string names[]{
        "Ada Lovelace",
        "Grace Hopper",
        "Alan Turing",
        "Katherine Johnson",
        "Linus Torvalds",
        "Bill Gates"
    };

    const int num_students{static_cast<int>(std::size(names))};
    const int num_assignments{5};
    
    double **scores = new double*[num_students];

    scores[0] = new double[num_assignments]{95.0, 88.5, 92.0, 78.0, 100.0};
    scores[1] = new double[num_assignments]{72.5, 80.0, 68.0, 91.0, 85.5};
    scores[2] = new double[num_assignments]{55.0, 62.5, 48.0, 70.0, 59.0};
    scores[3] = new double[num_assignments]{100.0, 98.0, 95.5, 99.0, 97.0};
    scores[4] = new double[num_assignments]{83.0, 79.5, 88.0, 84.0, 91.5};
    scores[5] = new double[num_assignments]{45.0, 52.0, 61.0, 38.5, 55.0};

    while(input != 0) {
        std::cout << "\n=== GRADEBOOK ===\n"
                  << "1. Full Report\n"
                  << "2. Grade Distribution\n"
                  << "3. Assignment Averages\n"
                  << "4. Roster\n"
                  << "5. Class Average\n"
                  << "0. Quit\n"
                  << "Choice: ";
        if(std::cin >> input) {
            switch(input) {
                case 1: {
                            print_header(num_students, num_assignments);

                            for(auto row{0}; row < num_students; row++) {
                                print_student_row(names[row], scores, row, num_students, num_assignments);
                            }

                            std::cout << "\t* perfect score\t! at risk\n";
                            break;
                        }
                        case 2: {
                    print_histogram(scores, num_students, num_assignments);
                    break;
                }
                case 3: {
                    print_assignment_summary(scores, num_students, num_assignments);
                    break;
                }
                case 4: {
                    print_roster(names, num_students);
                    break;
                }
                case 5: {
                    double avg{class_average(scores, num_students, num_assignments)};

                    std::cout << "Class Average: " << std::setw(6)
                              << std::setprecision(2) << std::fixed << avg
                              << '\n';
                    break;
                }
                case 0: {
                            for(auto student{0}; student < num_students; student++) {
                                delete[] scores[student];
                            }

                            delete[] scores;
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

//    for(auto student{0}; student < num_students; student++) {
//        for(auto assignment{0}; assignment < num_assignments; assignment++) {
//            std::cout << scores[student][assignment] << " ";
//        }
//        std::cout << std::endl;
//    }

    return 0;
}
