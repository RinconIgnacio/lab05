# Lab 05 Design

## Phase 2 - Affected Functions

student_average
- Uses: scores
- Scope: one student

assignment_average
- Uses: scores
- Scope: whole roster

class_average
- Uses: scores
- Scope: whole roster

find_extremes
- Uses: scores
- Scope: one student

count_grade
- Uses: scores
- Scope: whole roster

has_perfect_score
- Uses: scores
- Scope: one student

is_at_risk
- Uses: scores
- Scope: one student

print_student_row
- Uses: name and scores
- Scope: one student

print_histogram
- Uses: scores
- Scope: whole roster

print_assignment_summary
- Uses: scores
- Scope: whole roster

print_roster
- Uses: names
- Scope: whole roster

Total affected functions: 11

Main dependency:
The full-report loop accesses names[row] and scores using the same row.
The current design depends on both collections remaining synchronized.

Tests:
The grading tests construct the old score collection directly, so the
test fixtures and function calls will need to change during the refactor.

## Phase 3 - Struct Decision

STRUCT: Student

MODELS:
One student and the scores earned by that student.

LIVES IN:
student.h, because Student is a shared type needed by both the grading
and printing modules and does not belong specifically to either module.

FIXED DIMENSION:
The number of assignments. Each Student stores the fixed number of
assignment scores for the course.

VARYING DIMENSION:
The number of students. The roster can contain different numbers of
students, so the student count travels with the collection.

FIELDS:
- name
- scores

COLLECTION PASSED AS:
A pointer to Student records together with the number of students.

## Phase 4 - Signature Table

FUNCTION: student_average
MODULE: grading
OLD:
double student_average(const double* const* scores,
                       int student_index,
                       int num_assignments);

NEW:
double student_average(const Student& student);

PARAMETER REASONS:
The function only reads one student's scores, so it should receive one
Student by const reference instead of the entire score grid and an index.

CONTRACT CHANGES:
The student_index precondition is no longer needed because the function
receives the student directly.


FUNCTION: find_extremes
MODULE: grading
OLD:
void find_extremes(const double* const* scores,
                   int student_index,
                   int num_students,
                   int num_assignments,
                   double& lowest,
                   double& highest);

NEW:
void find_extremes(const Student& student,
                   double& lowest,
                   double& highest);

PARAMETER REASONS:
The function examines only one student's scores. The Student is passed by
const reference because it is read but not modified. lowest and highest
remain output reference parameters.

CONTRACT CHANGES:
The student_index precondition is no longer needed because the function
receives the student directly.


FUNCTION: has_perfect_score
MODULE: grading
OLD:
bool has_perfect_score(const double* const* scores,
                       int student_index,
                       int num_students,
                       int num_assignments);

NEW:
bool has_perfect_score(const Student& student);

PARAMETER REASONS:
Only one student's scores are needed. A const reference avoids copying the
record and prevents the function from modifying it.

CONTRACT CHANGES:
The student_index precondition is no longer needed.


FUNCTION: is_at_risk
MODULE: grading
OLD:
bool is_at_risk(const double* const* scores,
                int student_index,
                int num_students,
                int num_assignments);

NEW:
bool is_at_risk(const Student& student);

PARAMETER REASONS:
The at-risk decision uses only one student's scores, so the function needs
one Student rather than the entire roster and an index.

CONTRACT CHANGES:
The student_index precondition is no longer needed.

FUNCTION: assignment_average
MODULE: grading
OLD:
double assignment_average(const double* const* scores,
                          int assignment_index,
                          int num_students,
                          int num_assignments);

NEW:
double assignment_average(const Student* students,
                          int num_students,
                          int assignment_index);

PARAMETER REASONS:
The function walks the whole roster for one assignment. The Student pointer
provides the records and num_students gives the runtime roster size.

CONTRACT CHANGES:
The assignment_index precondition remains. The function now reads Student
records instead of a separate score grid.


FUNCTION: class_average
MODULE: grading
OLD:
double class_average(const double* const* scores,
                     int num_students,
                     int num_assignments);

NEW:
double class_average(const Student* students,
                     int num_students);

PARAMETER REASONS:
The function must examine every student in the roster. The pointer provides
the records and the count determines how many records may be accessed.

CONTRACT CHANGES:
The representation changes from a score grid to Student records. The
behavior of calculating the class mean remains the same.


FUNCTION: count_grade
MODULE: grading
OLD:
int count_grade(const double* const* scores,
                char target,
                int num_students,
                int num_assignments);

NEW:
int count_grade(const Student* students,
                int num_students,
                char target);

PARAMETER REASONS:
The function examines every student, so it receives the Student collection
and its count. target remains the letter grade being counted.

CONTRACT CHANGES:
The target precondition remains. The score-grid representation is replaced
by the Student collection.


FUNCTION: print_histogram
MODULE: printing
OLD:
void print_histogram(const double* const* scores,
                     int num_students,
                     int num_assignments);

NEW:
void print_histogram(const Student* students,
                     int num_students);

PARAMETER REASONS:
The histogram depends on grades across the entire roster, so it receives
the Student collection and its count.

CONTRACT CHANGES:
Its output behavior does not change; only the representation of its input
changes.


FUNCTION: print_assignment_summary
MODULE: printing
OLD:
void print_assignment_summary(const double* const* scores,
                              int num_students,
                              int num_assignments);

NEW:
void print_assignment_summary(const Student* students,
                              int num_students);

PARAMETER REASONS:
The function calculates assignment information across all students, so it
needs the Student collection and the roster count.

CONTRACT CHANGES:
Its output behavior remains the same while its input representation changes.


FUNCTION: print_roster
MODULE: printing
OLD:
void print_roster(const std::string* names,
                  int name_count);

NEW:
void print_roster(const Student* students,
                  int num_students);

PARAMETER REASONS:
The roster now gets each student's name from the Student record. The count
determines how many records may be traversed.

CONTRACT CHANGES:
The old precondition about names pointing to name_count strings becomes a
precondition about students pointing to num_students Student records.


FUNCTION: print_student_row
MODULE: printing
OLD:
void print_student_row(const std::string& name,
                       const double* const* scores,
                       int student_index,
                       int num_students,
                       int num_assignments);

NEW:
void print_student_row(const Student& student);

PARAMETER REASONS:
The row describes exactly one student. The Student record already keeps the
name and scores together, so the function no longer needs the full score
collection or a student index.

CONTRACT CHANGES:
The student_index precondition disappears. The function still does not
modify the student's data and still writes to standard output.

## Phase 5 - Conversion Order

MODULE DEPENDENCIES:

main
  -> printing
      -> grading
      -> utilities
  -> grading
      -> utilities

CONVERSION ORDER:

1. Define Student and assignment_count in the shared student header.
   Expected tests: RED because existing grading functions and tests still
   use the old score-grid representation.

2. Convert the grading function declarations and implementations to use
   Student records.
   Expected tests: RED because the existing tests still call the old
   grading interfaces.

3. Convert the grading tests and their test data to Student records.
   Expected tests: GREEN after grading and its tests agree on the new
   interfaces.

4. Convert the printing declarations and implementations to use Student
   records.
   Expected build/tests: grading tests should remain GREEN, although the
   application may temporarily fail to build until main is converted.

5. Convert main to create one collection of Student records instead of
   separate names and scores collections.
   Expected build/tests: GREEN.

6. Run the complete build and test suite and compare program behavior with
   the saved baseline.
   Expected build/tests: GREEN.
