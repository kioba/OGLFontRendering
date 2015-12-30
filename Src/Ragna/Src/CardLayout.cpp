#include "CardLayout.hpp"
#include <iostream>

namespace Ragna {

// #############################################################################
// ### Ragna::CardLayout #######################################################
// #############################################################################

CardLayout::CardLayout() :
	row_num{0},
	col_num{0}
{
	resizeContent();
}


CardLayout::CardLayout(const unsigned int row, const unsigned int col) :
	row_num{row},
	col_num{col}
{
	resizeContent();
}


CardLayout::~CardLayout()
{
}


void CardLayout::resizeContent()
{
	items.resize(row_num * col_num);
}


void CardLayout::setColumnCount(const unsigned int column_count)
{
	col_num = column_count;
	resizeContent();
}


unsigned int CardLayout::getColumnCount() const
{
	return col_num;
}


void CardLayout::setRowCount(const unsigned int row_count)
{
	row_num = row_count;
	resizeContent();
}


unsigned int CardLayout::getRowCount() const
{
	return row_num;
}


std::shared_ptr<Core> CardLayout::getItem(const unsigned int row, const unsigned int column) const
{
	const unsigned int position = row * (col_num) + column;
	return items.at(position);
}


void CardLayout::addItem(const unsigned int row, const unsigned int column, std::shared_ptr<Core> item)
{
	const unsigned int position = row * (col_num) + column;

	// float distance = 0;
	// for (size_t i = row * (row_num - 1); i < position; ++i) {
	// 	if (items[i]) {
	// 		distance += items[i]->getPos().x;
	// 	}
	// }
	//
	// if (row > 0) {
	// 	item->move(distance + pos.x, pos.y + 5000);
	// } else {
	// 	item->move(distance + pos.x, pos.y);
	// }

	if (position < items.size()) {
		items[position] = item;
	}
}


void CardLayout::resize(const float /*width*/, const float /*height*/)
{
	// Layout::resize(width, height);
	// for (size_t i = 0; i < items.size(); ++i) {
	// 	if (items[i]) {
	// 		items[i]->resize(width, height);
	// 	}
	// }
}


void CardLayout::move(const float /*x_axis*/, const float /*y_axis*/)
{
	// Layout::move(x_axis, y_axis);
	//
	// glm::vec2 new_pos = pos;
	//
	// for (size_t i = 0; i < items.size(); ++i) {
	// 	if (items[i]) {
	// 		items[i]->move(new_pos.x, new_pos.y);
	// 		new_pos.x += items[i]->getSize().x;
	// 	}
	// }
}


void CardLayout::draw()
{
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i] && items[i]->isVisible()) {
			items[i]->draw();
		}
	}
}


void CardLayout::show()
{
	Layout::show();
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]) {
			items[i]->show();
		}
	}
}


void CardLayout::hide()
{
	Layout::hide();
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]) {
			items[i]->hide();
		}
	}
}


bool CardLayout::keyDown(const SDL_KeyboardEvent& key)
{
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i] && items[i]->isVisible()) {
			if(items[i]->keyDown(key)) {
				return true;
			}
		}
	}

	return false;
}


bool CardLayout::mouseButtonDown(const SDL_MouseButtonEvent& button)
{
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]&& items[i]->isVisible()) {
			if(items[i]->mouseButtonDown(button)) {
				return true;
			}
		}
	}

	return false;
}


bool CardLayout::mouseMotion(const SDL_MouseMotionEvent& motion)
{
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]&& items[i]->isVisible()) {
			if(items[i]->mouseMotion(motion)) {
				return true;
			}
		}
	}

	return false;
}


bool CardLayout::mouseWheel(const SDL_MouseWheelEvent& wheel)
{
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]&& items[i]->isVisible()) {
			if(items[i]->mouseWheel(wheel)) {
				return true;
			}
		}
	}

	return false;
}


void CardLayout::setZOrder(float z_axis)
{
	Layout::setZOrder(z_axis);

	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]) {
			items[i]->setZOrder(z_axis);
		}
	}

}
} // Ragna namespace
