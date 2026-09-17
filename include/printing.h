// include/printing.h
#ifndef PRINTING_H
#define PRINTING_H

#include <string>

constexpr int name_width{14};

/**
 * @brief Prints the column header for the full grade report.
 *
 * @post Writes to standard output.
 */
void print_header(const int num_students, const int num_assignments);

/**
 * @brief Prints one student's row of the full grade report.
 *
 * The row shows the padded name, each assignment score, the average,
 * the letter grade, and markers for a perfect score or at-risk status.
 *
 * @pre student_index is in the range [0, num_students).
 * @post Neither name nor scores is modified.
 * @post Writes to standard output.
 *
 * @param[in] name            The student's full name.
 * @param[in] scores          The grade grid.
 * @param[in] student_index   Row of the student to print.
 * @param[in] num_students    Number of students in scores grid
 * @param[in] num_assignments Number of assignments in scores grid
 */
void print_student_row(const std::string& name, const double* const* scores, int student_index, const int num_students, const int num_assignments);

/**
 * @brief Prints a bar chart of how many students earned each letter grade.
 *
 * @post The scores grid is not modified.
 * @post Writes to standard output.
 *
 * @param[in] scores  The grade grid.
 * @param[in] num_students    Number of students in scores grid
 * @param[in] num_assignments Number of assignments in scores grid
 */
void print_histogram(const double* const* scores, const int num_students, const int num_assignments);

/**
 * @brief Prints the mean score for each assignment.
 *
 * Assignments averaging below 70 are flagged for review.
 *
 * @post The scores grid is not modified.
 * @post Writes to standard output.
 *
 * @param[in] scores  The grade grid.
 * @param[in] num_students    Number of students in scores grid
 * @param[in] num_assignments Number of assignments in scores grid
 */
void print_assignment_summary(const double* const* scores, const int num_students, const int num_assignments);

/**
 * @brief Prints each student's initials beside their full name.
 *
 * @pre names points to at least name_count consecutive strings.
 * @pre name_count is not negative.
 * @post No name is modified.
 * @post Writes to standard output.
 *
 * @param[in] names      Pointer to the first name in the roster.
 * @param[in] name_count  How many names the roster holds.
 * @param[in] num_students    Number of students in scores grid
 * @param[in] num_assignments Number of assignments in scores grid
 */
void print_roster(const std::string* names, int name_count);

#endif
