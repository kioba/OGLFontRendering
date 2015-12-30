#include <gtest/gtest.h>

#include "CardLayoutTest.hpp"
#include "RectTest.hpp"


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}
