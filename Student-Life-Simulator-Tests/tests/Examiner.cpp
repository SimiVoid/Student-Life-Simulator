#include "gtest/gtest.h"

#include "../src/Examiner.h"

TEST(Examiner, ExaminerClassTest) {
	Examiner examiner(std::make_pair(1, 1), 1);
	
	ASSERT_EQ(examiner.getSuspicion(), 1);	
}