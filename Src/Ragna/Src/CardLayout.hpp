#ifndef __RAGNA_CARDLAYOUT__
#define __RAGNA_CARDLAYOUT__

#include "Core/Core.hpp"
#include "Layout.hpp"
#include "Ragna.hpp"

#include <utility>

namespace Ragna {

// #############################################################################
// ### Ragna::CardLayout #######################################################
// #############################################################################

class RAGNA_API CardLayout :
	public Layout
{
protected: /* variables */
	unsigned int row_num;
	unsigned int col_num;

	std::vector<std::shared_ptr<Core>> items;

protected: /* functions */
	void resizeContent();

public: /* functions */
	CardLayout();
	CardLayout(unsigned int row, unsigned int col);
	virtual ~CardLayout();

	void setColumnCount(const unsigned int column_count);
	unsigned int getColumnCount() const;

	void setRowCount(const unsigned int row_count);
	unsigned int getRowCount() const;

	std::shared_ptr<Core> getItem(const unsigned int row, const unsigned int column) const;
	void addItem(const unsigned int row, const unsigned int column, std::shared_ptr<Core> item);

	virtual void resize(const float width, const float height) override;
	virtual void move(const float x_axis, const float y_axis) override;
	virtual void draw() override;

	virtual void show() override;
	virtual void hide() override;

	virtual bool keyDown(const SDL_KeyboardEvent& key) override;
	virtual bool mouseButtonDown(const SDL_MouseButtonEvent& button) override;
	virtual bool mouseMotion(const SDL_MouseMotionEvent& motion) override;
	virtual bool mouseWheel(const SDL_MouseWheelEvent& wheel) override;

	virtual void setZOrder(float z_axis) override;
};


} // Ragna namespace

#endif // __RAGNA_CARDLAYOUT__
