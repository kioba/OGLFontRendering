#ifndef __RUNIC_RANGE__
#define __RUNIC_RANGE__

#include <vector>
#include <fstream>

namespace RunicCore {

// #############################################################################
// ### RRange ##################################################################
// #############################################################################

class RRange
{
public: /* types */
	typedef const char* Iter;

private: /* variable */
	Iter front;
	Iter back;

public: /* functions */
	RRange();
	RRange(RRange::Iter begin_pos, RRange::Iter end_pos);
	virtual ~RRange();

	RRange::Iter begin() const;
	void setBegin(RRange::Iter iter);

	RRange::Iter end() const;
	void setEnd(RRange::Iter iter);

	unsigned int getSize() const;
};


} // RunicCore namespace

#endif // __RUNIC_RANGE__
