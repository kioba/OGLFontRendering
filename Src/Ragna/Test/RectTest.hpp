#ifndef __RAGNA_RECT_TEST_HPP__
#define __RAGNA_RECT_TEST_HPP__

#include <vector>

#include <gtest/gtest.h>
#include <Core/Rect.hpp>
#include <Core/Object.hpp>

class RectTest :
	public ::testing::Test
{
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	RectTest() {
		// You can do set-up work for each test here.
		float x = 0.0f;
		float y = 0.0f;
		float w = 3.0f;
		float h = 4.0f;

		p.move(x, y);
		p.resize(w, h);
	}

	virtual ~RectTest() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Project1.
	Ragna::Rect p;
};


#endif // __RAGNA_RECT_TEST_HPP__
