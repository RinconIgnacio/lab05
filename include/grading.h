// include/grading.h
#ifndef GRADING_H
#define GRADING_H

#include "student.h"

/**
 * @brief Calculates one student's mean score across all assignments.
 *
 * @post The student record is not modified.
 *
 * @param[in] student The student to average.
 * @return The mean of that student's assignment scores.
 */
[[nodiscard]] double student_average(const Student& student);

/**
 * @brief Calculates the mean score on one assignment across all students.
 *
 * @pre assignment_index is in the range [0, assignment_count).
 * @post The student records are not modified.
 *
 * @param[in] students          The collection of student records.
 * @param[in] assignment_index  Assignment to average.
 * @param[in] num_students      Number of students in the collection.
 * @return The mean score earned on that assignment.
 */
[[nodiscard]] double assignment_average(const Student students[],
                                        int assignment_index,
                                        int num_students);

/**
 * @brief Calculates the mean of every score in the collection.
 *
 * @post The student records are not modified.
 *
 * @param[in] students      The collection of student records.
 * @param[in] num_students  Number of students in the collection.
 * @return The mean of all student assignment scores.
 */
[[nodiscard]] double class_average(const Student students[],
                                   int num_students);

/**
 * @brief Finds one student's lowest and highest assignment scores.
 *
 * @post lowest holds the student's minimum score.
 * @post highest holds the student's maximum score.
 * @post The student record is not modified.
 *
 * @param[in]  student The student to examine.
 * @param[out] lowest  Receives the minimum score.
 * @param[out] highest Receives the maximum score.
 */
void find_extremes(const Student& student,
                   double& lowest,
                   double& highest);

/**
 * @brief Counts how many students earned a given letter grade.
 *
 * @pre target is one of 'A', 'B', 'C', 'D', or 'F'.
 * @post The student records are not modified.
 *
 * @param[in] students      The collection of student records.
 * @param[in] target        The letter grade to count.
 * @param[in] num_students  Number of students in the collection.
 * @return The number of students whose average earns that letter.
 */
[[nodiscard]] int count_grade(const Student students[],
                              char target,
                              int num_students);

/**
 * @brief Reports whether a student earned a perfect score on any assignment.
 *
 * @post The student record is not modified.
 *
 * @param[in] student The student to examine.
 * @return true if any of the student's scores is 100 or above.
 */
[[nodiscard]] bool has_perfect_score(const Student& student);

/**
 * @brief Reports whether a student is academically at risk.
 *
 * A student is at risk when their average is below 70, or when any
 * single assignment score is below 50.
 *
 * @post The student record is not modified.
 *
 * @param[in] student The student to examine.
 * @return true if either at-risk condition holds.
 */
[[nodiscard]] bool is_at_risk(const Student& student);

#endif
