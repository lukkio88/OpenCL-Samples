#include <gtest/gtest.h>

// Tests positive input.
TEST(IsPrimeTest, Positive) {
	ASSERT_EQ(0, 0); //Naive example to be used as example
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}