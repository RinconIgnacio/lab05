// include/printing.h
#ifndef PRINTING_H
#define PRINTING_H

#include "student.h"

constexpr int name_width{14};

/**
 * @brief Prints the column header for the full grade report.
 *
 * @post Writes to standard output.
 */
void print_header(int num_students);

/**
 * @brief Prints one student's row of the full grade report.
 *
 * The row shows the padded name, each assignment score, the average,
 * the letter grade, and markers for a perfect score or at-risk status.
 *
 * @pre student_index is in the range [0, num_students).
 * @post The student records are not modified.
 * @post Writes to standard output.
 *
 * @param[in] students       The collection of student records.
 * @param[in] student_index  Index of the student to print.
 */
void print_student_row(const Student students[], int student_index);

/**
 * @brief Prints a bar chart of how many students earned each letter grade.
 *
 * @post The student records are not modified.
 * @post Writes to standard output.
 *
 * @param[in] students      The collection of student records.
 * @param[in] num_students  Number of students in the collection.
 */
void print_histogram(const Student students[], int num_students);

/**
 * @brief Prints the mean score for each assignment.
 *
 * Assignments averaging below 70 are flagged for review.
 *
 * @post The student records are not modified.
 * @post Writes to standard output.
 *
 * @param[in] students      The collection of student records.
 * @param[in] num_students  Number of students in the collection.
 */
void print_assignment_summary(const Student students[], int num_students);

/**
 * @brief Prints each student's initials beside their full name.
 *
 * @pre num_students is not negative.
 * @post The student records are not modified.
 * @post Writes to standard output.
 *
 * @param[in] students      The collection of student records.
 * @param[in] num_students  Number of students in the collection.
 */
void print_roster(const Student students[], int num_students);

#endif
