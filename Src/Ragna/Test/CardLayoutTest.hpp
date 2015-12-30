#ifndef __CARDLAYOUT_TEST_HPP__
#define __CARDLAYOUT_TEST_HPP__

#include <gtest/gtest.h>
#include <CardLayout.hpp>
#include <Material.hpp>

#include <memory>

// The fixture for testing class Project1. From google test primer.
class CardLayoutTest :
	public ::testing::Test
{
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	CardLayoutTest() :
		card_construct(5,4)
	{
		// You can do set-up work for each test here.
	}

	virtual ~CardLayoutTest() {
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

	// Objects declared here can be used by all tests in the test case.
	Ragna::CardLayout card_construct;
	Ragna::CardLayout card_empty;
};


#endif // __CARDLAYOUT_TEST_HPP__
