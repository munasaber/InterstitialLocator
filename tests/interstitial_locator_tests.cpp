#include "../tests/autotools.hh"
#include "../include/interstitial_locator.hpp"
#include <gtest/gtest.h>

TEST(DivisibleByTest, MultOf4)
{
	EXPECT_TRUE(isDivisibleby4(16));
	EXPECT_FALSE(isDivisibleby4(15));
}

TEST(VectorDistances, CorrectDistance)
{
	Eigen::Vector3d vector1<<4, 4, 4;
	Eigen::Vector3d vector2<<0, 0, 0;
	EXPECT_EQ(distances_between_vectors(vector1, vector2), sqrt(12));
	EXPECT_GT(distances_between_vectors(vector2, vector1), sqrt(12));
}

TEST(mytest, mytest2)
{
	ASSERT_TRUE(FALSE);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
