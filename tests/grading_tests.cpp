#include <gtest/gtest.h>
#include <algorithm>
#include <initializer_list>

#include "grading.h"
#include "utilities.h"

// Helper class to manage dynamic 2D arrays for varying test sizes
class ScoreMatrix {
private:
    double** data;
    int rows;
    int cols;

public:
    ScoreMatrix(std::initializer_list<std::initializer_list<double>> init) {
        rows = init.size();
        cols = init.begin()->size();
        data = new double*[rows];
        int i = 0;
        for (auto row : init) {
            data[i] = new double[cols];
            std::copy(row.begin(), row.end(), data[i]);
            i++;
        }
    }

    ~ScoreMatrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    const double* const* get() const { return data; }
    int get_rows() const { return rows; }
    int get_cols() const { return cols; }
};

TEST(GradingEdgeCases, OneStudentOneAssignment) {
    ScoreMatrix matrix{{85.0}};
    
    EXPECT_DOUBLE_EQ(student_average(matrix.get(), 0, matrix.get_cols()), 85.0);
    EXPECT_DOUBLE_EQ(assignment_average(matrix.get(), 0, matrix.get_rows(), matrix.get_cols()), 85.0);
    EXPECT_DOUBLE_EQ(class_average(matrix.get(), matrix.get_rows(), matrix.get_cols()), 85.0);
    
    double lowest, highest;
    find_extremes(matrix.get(), 0, matrix.get_rows(), matrix.get_cols(), lowest, highest);
    EXPECT_DOUBLE_EQ(lowest, 85.0);
    EXPECT_DOUBLE_EQ(highest, 85.0);
    
    EXPECT_FALSE(is_at_risk(matrix.get(), 0, matrix.get_rows(), matrix.get_cols()));
    EXPECT_FALSE(has_perfect_score(matrix.get(), 0, matrix.get_rows(), matrix.get_cols()));
}

TEST(GradingEdgeCases, OneRowMultipleAssignments) {
    ScoreMatrix matrix{{100.0, 45.0, 45.0, 90.0}};
    
    EXPECT_DOUBLE_EQ(student_average(matrix.get(), 0, matrix.get_cols()), 70.0);
    
    // Has multiple failing assignments (< 50)
    EXPECT_TRUE(is_at_risk(matrix.get(), 0, matrix.get_rows(), matrix.get_cols()));
    EXPECT_TRUE(has_perfect_score(matrix.get(), 0, matrix.get_rows(), matrix.get_cols()));
}

TEST(GradingEdgeCases, ZeroesAndNegativeValues) {
    ScoreMatrix matrix{
        {0.0, 0.0, 0.0},
        {-10.0, -50.0, -5.0}
    };
    
    EXPECT_DOUBLE_EQ(class_average(matrix.get(), matrix.get_rows(), matrix.get_cols()), -65.0 / 6.0);
    
    double lowest, highest;
    find_extremes(matrix.get(), 1, matrix.get_rows(), matrix.get_cols(), lowest, highest);
    EXPECT_DOUBLE_EQ(lowest, -50.0);
    EXPECT_DOUBLE_EQ(highest, -5.0);
    
    EXPECT_TRUE(is_at_risk(matrix.get(), 1, matrix.get_rows(), matrix.get_cols()));
}

TEST(GradingEdgeCases, AtRiskVariations) {
    ScoreMatrix matrix{
        {80.0, 80.0, 80.0, 49.0},  // Avg 72.25, but one assignment < 50
        {55.0, 55.0, 55.0, 55.0},  // All assignments > 50, but avg < 70
        {40.0, 45.0, 90.0, 90.0},  // Avg 66.25, multiple assignments < 50
        {70.0, 70.0, 70.0, 70.0}   // Avg 70, no assignments < 50
    };
    
    EXPECT_TRUE(is_at_risk(matrix.get(), 0, matrix.get_rows(), matrix.get_cols()));
    EXPECT_TRUE(is_at_risk(matrix.get(), 1, matrix.get_rows(), matrix.get_cols()));
    EXPECT_TRUE(is_at_risk(matrix.get(), 2, matrix.get_rows(), matrix.get_cols()));
    EXPECT_FALSE(is_at_risk(matrix.get(), 3, matrix.get_rows(), matrix.get_cols()));
}

TEST(GradingEdgeCases, PerfectScoreVariations) {
    ScoreMatrix matrix{
        {99.9, 99.9, 99.9},        // Almost perfect, but no 100
        {100.0, 0.0, 0.0},         // Exactly one 100
        {105.0, 100.0, 102.0}      // Multiple scores >= 100
    };
    
    EXPECT_FALSE(has_perfect_score(matrix.get(), 0, matrix.get_rows(), matrix.get_cols()));
    EXPECT_TRUE(has_perfect_score(matrix.get(), 1, matrix.get_rows(), matrix.get_cols()));
    EXPECT_TRUE(has_perfect_score(matrix.get(), 2, matrix.get_rows(), matrix.get_cols()));
}
