#ifndef __POLYGONTEST_HPP__
#define __POLYGONTEST_HPP__


#include <gtest/gtest.h>

#include <exception>

class PolygonTest :
	public ::testing::Test
{
protected:
	PolygonTest();
	virtual ~PolygonTest();
	virtual void SetUp();
	virtual void TearDown();

};


#endif // __POLYGONTEST_HPP__
