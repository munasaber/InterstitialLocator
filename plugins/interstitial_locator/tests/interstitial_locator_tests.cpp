#include "../tests/autotools.hh"
#include "../include/interstitial_locator.hpp"
#include <gtest/gtest.h>


class InterstitialTest: public testing::Test
{
protected:
	void SetUp()  
	{
	structure=casmutils::xtal::Structure::from_poscar("../../../tests/input_files/hcp.vasp");
	max_length={4, 4, 4};
	min_length={2, 2, 2};
	tol=1e-6;
	}
	casmutils::xtal::Structure structure;
	double tol;
	std::vector<double> max_lenth;
	std::vector<double> min_length;
}

TEST(InterstitialTest, isDivisibleby4)
{
	EXPECT_TRUE(isDivisibleby4(16));
	EXPECT_FALSE(isDivisibleby4(15));
}

TEST(InterstitialTest, distances_between_vectors)
{
	Eigen::Vector3d vector1<<4, 4, 4;
	Eigen::Vector3d vector2<<0, 0, 0;
	EXPECT_EQ(distances_between_vectors(vector1, vector2), sqrt(12));
	EXPECT_GT(distances_between_vectors(vector2, vector1), sqrt(12));
}

TEST(InterstitialTest, mytest2)
{
	ASSERT_TRUE(FALSE);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
