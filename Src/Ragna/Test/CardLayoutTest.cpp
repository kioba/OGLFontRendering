#include "CardLayoutTest.hpp"


TEST_F(CardLayoutTest, empty_getColumnCount)
{
	unsigned int i = 0;
	EXPECT_EQ(card_empty.getColumnCount(), i);
}


TEST_F(CardLayoutTest, empty_getRowCount)
{
	unsigned int i = 0;
	EXPECT_EQ(card_empty.getRowCount(), i);
}


TEST_F(CardLayoutTest, empty_setColumnCount)
{
	unsigned int i = 10;
	card_empty.setColumnCount(i);
	EXPECT_EQ(card_empty.getColumnCount(), i);
}


TEST_F(CardLayoutTest, empty_setRowCount)
{
	unsigned int i = 15;
	card_empty.setRowCount(i);
	EXPECT_EQ(card_empty.getRowCount(), i);
}


TEST_F(CardLayoutTest, construct_getColumnCount)
{
	unsigned int i = 4;
	EXPECT_EQ(card_construct.getColumnCount(), i);
}


TEST_F(CardLayoutTest, construct_getRowCount)
{
	unsigned int i = 5;
	EXPECT_EQ(card_construct.getRowCount(), i);
}


TEST_F(CardLayoutTest, construct_reSetColumnCount)
{
	unsigned int i = 22;
	card_construct.setColumnCount(i);
	EXPECT_EQ(card_construct.getColumnCount(), i);
}


TEST_F(CardLayoutTest, construct_reSetRowCount)
{
	unsigned int i = 22;
	card_construct.setRowCount(i);
	EXPECT_EQ(card_construct.getRowCount(), i);
}


TEST_F(CardLayoutTest, addItem)
{
	std::shared_ptr<Ragna::Material> material = std::make_shared<Ragna::Material>();
	card_construct.addItem(0, 0, material);
	EXPECT_EQ(card_construct.getItem(0, 0), material);
}
