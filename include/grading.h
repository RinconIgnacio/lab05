// include/grading.h
#ifndef GRADING_H
#define GRADING_H

/**
 * @brief Calculates one student's mean score across all assignments.
 *
 * @pre student_index is in the range [0, num_students).
 * @post The scores grid is not modified.
 *
 * @param[in] scores          The grade grid.
 * @param[in] student_index   Row of the student to average.
 * @param[in] num_students    Number of students in the grid
 * @param[in] num_assignments Number of assignments in the grid
 * @return The mean of that student's assignment scores.
 */
[[nodiscard]] double student_average(const double* const* scores,
                                    const int student_index,
                                    const int num_assignments);

/**
 * @brief Calculates the mean score on one assignment across all students.
 *
 * @pre assignment_index is in the range [0, num_assignments).
 * @post The scores grid is not modified.
 *
 * @param[in] scores           The grade grid.
 * @param[in] assignment_index  Column of the assignment to average.
 * @return The mean score earned on that assignment.
 */
[[nodiscard]] double assignment_average(const double* const* scores,
                                       int assignment_index, const int num_students, const int num_assignments);

/**
 * @brief Calculates the mean of every score in the grid.
 *
 * @post The scores grid is not modified.
 *
 * @param[in] scores  The grade grid.
 * @return The mean of all num_students * num_assignments scores.
 */
[[nodiscard]] double class_average(const double* const* scores, const int num_students, const int num_assignments);

/**
 * @brief Finds one student's lowest and highest assignment scores.
 *
 * @pre student_index is in the range [0, num_students).
 * @post lowest holds that student's minimum score.
 * @post highest holds that student's maximum score.
 * @post The scores grid is not modified.
 *
 * @param[in]  scores           The grade grid.
 * @param[in]  student_index    Row of the student to examine.
 * @param[in]  num_students     Number of students in the scores grid
 * @param[in]  num_assignments  Number of assignments in the scores grid
 * @param[out] lowest           Receives the minimum score.
 * @param[out] highest          Receives the maximum score.
 */
void find_extremes(const double* const* scores, int student_index, const int num_students, const int num_assignments, double& lowest, double& highest);

/**
 * @brief Counts how many students earned a given letter grade.
 *
 * @pre target is one of 'A', 'B', 'C', 'D', or 'F'.
 * @post The scores grid is not modified.
 *
 * @param[in] scores  The grade grid.
 * @param[in] target  The letter grade to count.
 * @param[in] num_students     Number of students in the scores grid
 * @param[in] num_assignments  Number of assignments in the scores grid
 * @return The number of students whose average earns that letter.
 */
[[nodiscard]] int count_grade(const double* const* scores, char target, const int num_students, const int num_assignments);

/**
 * @brief Reports whether a student earned a perfect score on any assignment.
 *
 * @pre student_index is in the range [0, num_students).
 * @post The scores grid is not modified.
 *
 * @param[in] scores        The grade grid.
 * @param[in] student_index  Row of the student to examine.
 * @param[in] num_students     Number of students in the scores grid
 * @param[in] num_assignments  Number of assignments in the scores grid
 * @return true if any of that student's scores is 100 or above.
 */
[[nodiscard]] bool has_perfect_score(const double* const* scores, int student_index, const int num_students, const int num_assignments);

/**
 * @brief Reports whether a student is academically at risk.
 *
 * A student is at risk when their average is below 70, or when any
 * single assignment score is below 50.
 *
 * @pre student_index is in the range [0, num_students).
 * @post The scores grid is not modified.
 *
 * @param[in] scores        The grade grid.
 * @param[in] student_index  Row of the student to examine.
 * @param[in] num_students     Number of students in the scores grid
 * @param[in] num_assignments  Number of assignments in the scores grid
 * @return true if either at-risk condition holds.
 */
[[nodiscard]] bool is_at_risk(const double* const* scores, int student_index, const int num_students, const int num_assignments);

#endif
