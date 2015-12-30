#ifndef __RUNIC_FONT__
#define __RUNIC_FONT__

#include <string>
#include <memory>

#include "Runic.hpp"
#include "RunicCmapTable.hpp"
#include "RunicGlyph.hpp"
#include "RunicGlyphTable.hpp"
#include "RunicHeadTable.hpp"
#include "RunicLoader.hpp"
#include "RunicLocaTable.hpp"
#include "RunicMaxpTable.hpp"
#include "RunicNameTable.hpp"
#include "RunicTriangulator.hpp"

namespace Runic {

// #############################################################################
// ### Runic::GlyphPoint #######################################################
// #############################################################################

class RUNIC_API RFont
{


private: /* variables */
	const static std::vector<std::string> TTF_table_str;
	std::unique_ptr<RunicCore::RFileHeader> file_header;

	std::shared_ptr<RunicCore::RCmapTable> cmap;
	std::shared_ptr<RunicCore::RHeadTable> head;
	// std::shared_ptr<RunicCore::RHheaTable> hhea;
	// std::shared_ptr<RunicCore::RHmtxTable> hmtx;
	std::shared_ptr<RunicCore::RMaxpTable> maxp;
	std::shared_ptr<RunicCore::RNameTable> name;
	// std::shared_ptr<RunicCore::ROS2Table> OS2;
	// std::shared_ptr<RunicCore::RPostTable> post;
	// std::shared_ptr<RunicCore::RCvtTable> cvt;
	// std::shared_ptr<RunicCore::RFpgmTable> fpgm;
	std::shared_ptr<RunicCore::RGlyfTable> glyf;
	std::shared_ptr<RunicCore::RLocaTable> loca;
	// std::shared_ptr<RunicCore::RPrepTable> prep;

private: /* types */
	class Contour {
		public: /* variables */
			std::vector<std::vector<GlyphPoint>> polygons;
			std::vector<bool> is_hole;
			std::shared_ptr<Triangulator> tri;

		private: /* functions */
			void convertSplinesToBezier(std::vector<GlyphPoint>& points) const;

		public: /* functions */
			Contour();
			virtual ~Contour();
			void convertSplines();
			bool pointInsideFilledArea(const GlyphPoint& point) const;
			std::vector<Triangle> getFilledTriangles();
			std::vector<Triangle> getBezierTriangles() const;

	};

private: /* functions */
	RFont(const RFont& source) = delete;
	RFont& operator=(const RFont& source) = delete;

	void createFont();
	Glyph fillGlyph(const RawGlyph& raw) const;

	static bool pointInPoligon(const std::vector<GlyphPoint>& polygon,
								const GlyphPoint& point);

	static bool pointInPoligonWithoutCurve(const std::vector<GlyphPoint>& polygon,
								const GlyphPoint& point);

public: /* functions */
	RFont(const std::string file_path);
	~RFont();

	Glyph getGlyph(char char_code);
	GlyphMetric getFontBoundingBox() const;
};

} //Runic namespace

#endif // __RUNIC_FONT__
