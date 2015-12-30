#include "RunicFont.hpp"

#include <string>
#include <algorithm>

namespace Runic {

// #############################################################################
// ### Runic::GlyphPoint #######################################################
// #############################################################################

const std::vector<std::string> RFont::TTF_table_str =
			{"cmap", "head", "hhea", "hmtx",
			 "maxp", "name", "OS/2", "post",
			 "cvt ", "fpgm", "glyf", "loca", "prep"};


RFont::RFont(const std::string file_path)
{
	RunicCore::RLoader Loader {file_path};
	file_header = Loader.moveContent();

	// for (unsigned int i = 0; i < TTF_table_str.size(); ++i) {
	// 	std::cout << TTF_table_str[i] << ": ";
	// 	bool exist = file_header->verifyTableExistance(TTF_table_str[i]);
	// 	if (exist) {
	// 		std::cout << " Exists!" << std::endl;
	// 	} else {
	// 		std::cout << " Does not exist!" << std::endl;
	// 	}
	// }

	createFont();

	loca->setLocFormat(head->index_to_loc_format);
	loca->setNumGlyphs(maxp->num_glyphs);
}


RFont::~RFont()
{
}


bool RFont::pointInPoligon(const std::vector<GlyphPoint>& polygon, const GlyphPoint& point)
{
	bool is_inside = false;

	for (size_t i = 0; i < polygon.size(); ++i) {
		unsigned int j = (i + 1) % polygon.size();

		bool inside_y = (polygon[i].pos.second > point.pos.second) !=
						(polygon[j].pos.second > point.pos.second);

		bool inside_x = point.pos.first < (polygon[j].pos.first - polygon[i].pos.first) *
					(point.pos.second - polygon[i].pos.second) /
					(polygon[j].pos.second - polygon[i].pos.second) + polygon[i].pos.first;

		if (inside_y && inside_x) {
			is_inside = !is_inside;
		}
	}

	return is_inside;
}


bool RFont::pointInPoligonWithoutCurve(const std::vector<GlyphPoint>& polygon, const GlyphPoint& point)
{
	bool is_inside = false;

	for (size_t i = 0; i < polygon.size(); ++i) {

		if (!polygon[i].isOnCurve()) {
			continue;
		}

		unsigned int j = (i + 1) % polygon.size();

		while (!polygon[j].isOnCurve()) {
			j = (i + 2) % polygon.size();
		}

		bool inside_y = (polygon[i].pos.second > point.pos.second) !=
						(polygon[j].pos.second > point.pos.second);

		bool inside_x = point.pos.first < (polygon[j].pos.first - polygon[i].pos.first) *
					(point.pos.second - polygon[i].pos.second) /
					(polygon[j].pos.second - polygon[i].pos.second) + polygon[i].pos.first;

		if (inside_y && inside_x) {
			is_inside = !is_inside;
		}
	}

	return is_inside;
}


Glyph RFont::fillGlyph(const RawGlyph& raw) const
{
	const std::vector<GlyphPoint>& points = raw.points;
	std::vector<Contour> contours;
	auto end_point_iter = points.begin();
	auto first_iter = points.begin();
	int last_out_poly = -1;

	//separate contour and contour-hole polygons
	while (end_point_iter != points.end()) {
		end_point_iter = std::find_if(end_point_iter, points.end(),
					[] (const GlyphPoint& point) { return point.isEndPoint(); });

		if (end_point_iter != points.end()) {
			end_point_iter += 1;
			std::vector<GlyphPoint> temp(first_iter, end_point_iter);
			first_iter = end_point_iter;

			bool isHolePoly = false;
			// check if a poly Hole
			if (last_out_poly != -1) {
				isHolePoly = pointInPoligon(contours[last_out_poly].polygons[0], temp.back());
			}

			// if not a whole increase the num of contours
			if (!isHolePoly) {
				++last_out_poly;
				contours.resize(last_out_poly + 1);
			}

			contours[last_out_poly].polygons.push_back(temp);
			contours[last_out_poly].is_hole.push_back(isHolePoly);

		}
	}

	Glyph glyph;
	// converts from B splines to Bezier splines
	for (size_t i = 0; i < contours.size(); i++) {
		std::vector<Triangle> temp_fill;
		std::vector<Triangle> temp_bezier;

		contours[i].convertSplines();
		temp_fill = contours[i].getFilledTriangles();
		temp_bezier = contours[i].getBezierTriangles();

		glyph.triangles.insert(glyph.triangles.end(), temp_fill.begin(), temp_fill.end());
		glyph.bezier.insert(glyph.bezier.end(), temp_bezier.begin(), temp_bezier.end());
	}

	return glyph;
}


Glyph RFont::getGlyph(char char_code)
{
	RunicCore::CharCode code(char_code);

	int index = cmap->getGlyphIndex(code);
	int glyph_offset_begin = loca->getGlyphLocation(index);
	int glyph_offset_end = loca->getGlyphLocation(index + 1);

	RawGlyph raw = glyf->decryptGlyph(glyph_offset_begin, glyph_offset_end);

	if (raw.number_of_contours < 0) {
		int glyph_nothing_begin = loca->getGlyphLocation(0);
		int glyph_nothing_end = loca->getGlyphLocation(1);

		raw = glyf->decryptGlyph(glyph_nothing_begin, glyph_nothing_end);
	}

	Glyph glyph = fillGlyph(raw);

	glyph.metric.y_min = static_cast<float>(raw.y_min);
	glyph.metric.x_min = static_cast<float>(raw.x_min);
	glyph.metric.x_max = static_cast<float>(raw.x_max);
	glyph.metric.y_max = static_cast<float>(raw.y_max);

	return glyph;
}


GlyphMetric RFont::getFontBoundingBox() const
{
	GlyphMetric metric;
	metric.x_min = head->xmin;
	metric.y_min = head->ymin;
	metric.x_max = head->xmax;
	metric.y_max = head->ymax;

	return metric;
}


void RFont::createFont()
{
	for (unsigned int i = 0; i < TTF_table_str.size(); ++i) {
		switch (i) {
			case 0:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					cmap = std::make_shared<RunicCore::RCmapTable>(file_header->GetTableEntry(TTF_table_str[i]));
					cmap->decrypt();
					// std::cout << cmap->toStr() << std::endl;
				}
				break;

			case 1:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					head = std::make_shared<RunicCore::RHeadTable>(file_header->GetTableEntry(TTF_table_str[i]));
					head->decrypt();
					// std::cout << head->toStr() << std::endl;
				}
				break;

			case 2:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					// hhea = std::make_shared<RunicCore::RHheaTable>(file_header->GetTableEntry(TTF_table_str[i]));
					// hhea->decrypt();
					// std::cout << hhea->toStr() << std::endl;
				}
				break;

			case 3:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					// hmtx = std::make_shared<RunicCore::RHmtxTable>(file_header->GetTableEntry(TTF_table_str[i]));
					// hmtx->decrypt();
					// std::cout << hmtx->toStr() << std::endl;
				}
				break;

			case 4:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					maxp = std::make_shared<RunicCore::RMaxpTable>(file_header->GetTableEntry(TTF_table_str[i]));
					maxp->decrypt();
					// std::cout << maxp->toStr() << std::endl;
				}
				break;

			case 5:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					name = std::make_shared<RunicCore::RNameTable>(file_header->GetTableEntry(TTF_table_str[i]));
					name->decrypt();
					// std::cout << name->toStr() << std::endl;
				}
				break;

			case 6:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					// OS2 = std::make_shared<RunicCore::ROS2Table>(file_header->GetTableEntry(TTF_table_str[i]));
					// OS2->decrypt();
					// std::cout << OS2->toStr() << std::endl;
				}
				break;

			case 7:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					// post = std::make_shared<RunicCore::RPostTable>(file_header->GetTableEntry(TTF_table_str[i]));
					// post->decrypt();
					// std::cout << post->toStr() << std::endl;
				}
				break;

			case 8:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					// cvt = std::make_shared<RunicCore::RCvtTable>(file_header->GetTableEntry(TTF_table_str[i]));
					// cvt->decrypt();
					// std::cout << cvt->toStr() << std::endl;
				}
				break;

			case 9:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					// fpgm = std::make_shared<RunicCore::RFpgmTable>(file_header->GetTableEntry(TTF_table_str[i]));
					// fpgm->decrypt();
					// std::cout << fpgm->toStr() << std::endl;
				}
				break;

			case 10:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					glyf = std::make_shared<RunicCore::RGlyfTable>(file_header->GetTableEntry(TTF_table_str[i]));
					// glyf->decrypt(); // not needed
					// std::cout << glyf->toStr() << std::endl;
				}
				break;

			case 11:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					loca = std::make_shared<RunicCore::RLocaTable>(file_header->GetTableEntry(TTF_table_str[i]));
					// loca->decrypt(); // not needed
					// std::cout << loca->toStr() << std::endl;
				}
				break;

			case 12:
				if (file_header->verifyTableExistance(TTF_table_str[i])) {
					// prep = std::make_shared<RunicCore::RPrepTable>(file_header->GetTableEntry(TTF_table_str[i]));
					// prep->decrypt();
					// std::cout << prep->toStr() << std::endl;
				}
				break;

			default:
				break;
		}
	}
}


RFont::Contour::Contour()
{
}


RFont::Contour::~Contour()
{
}


void RFont::Contour::convertSplinesToBezier(std::vector<GlyphPoint>& points) const
{
	std::vector<GlyphPoint> temp;
	for (size_t i = 0; i < points.size(); ++i) {
		temp.push_back(points[i]);
		// check next element (end + 1 -> 0)
		unsigned int next_id = (i + 1) % points.size();

		// make sure we could generate a 1 control Bezier curve
		// can not let 2 control point to occur after each other
		if (!(points[i].isOnCurve()) && !(points[next_id].isOnCurve())) {

			// generate a new point between the the two control point
			float x_pos = (points[i].pos.first + points[next_id].pos.first) / 2.0f;
			float y_pos = (points[i].pos.second + points[next_id].pos.second) / 2.0f;

			GlyphPoint new_pos;
			new_pos.pos.first = x_pos;
			new_pos.pos.second = y_pos;
			new_pos.setFlag(GlyphPoint::onCurve);

			// append point to the vector
			temp.push_back(new_pos);
		}
	}

	points.clear();
	points = std::move(temp);
}


void RFont::Contour::convertSplines()
{
	for (size_t i = 0; i < polygons.size(); ++i) {
		convertSplinesToBezier(polygons[i]);
	}
}


std::vector<Triangle> RFont::Contour::getFilledTriangles()
{
	tri.reset(new BasicTri2D());

	for (size_t i = 0; i < polygons.size(); ++i) {
		std::vector<std::pair<float, float>> contour_pos_points;

		for (size_t j = 0; j < polygons[i].size(); ++j) {

			if (polygons[i][j].isOnCurve()) {
				contour_pos_points.push_back(polygons[i][j].pos);
			} else {
				// append to the trianguleted points
				if (pointInsideFilledArea(polygons[i][j])) {
					contour_pos_points.push_back(polygons[i][j].pos);
				}
			}
		}

		// push points to the triangluator
		if (i == 0) {
			tri->addCounture(contour_pos_points);
		} else {
			tri->addHole(contour_pos_points);
		}
	}

	return tri->triangulate();
}


std::vector<Triangle> RFont::Contour::getBezierTriangles() const
{
	std::vector<Triangle> beziers;
	// collect bezier curve triangles
	for (size_t i = 0; i < polygons.size(); ++i) {
		for (size_t j = 0; j < polygons[i].size(); ++j) {
			if (!polygons[i][j].isOnCurve() && j != 0) {
				int next_id = (j + 1) % polygons[i].size();

				Triangle::TriangleType type = Triangle::filled;
				if (pointInsideFilledArea(polygons[i][j])) {
					type = Triangle::negative;
				} else {
					type = Triangle::positive;
				}

				Triangle triangle;
				triangle.a = polygons[i][j - 1].pos;
				triangle.b = polygons[i][j].pos;
				triangle.c = polygons[i][next_id].pos;
				triangle.setTriangleType(type);
				triangle.setCounterClockWise();
				beziers.push_back(triangle);
			}
		}
	}

	return beziers;
}


bool RFont::Contour::pointInsideFilledArea(const GlyphPoint& point) const
{
	if (polygons.size() < 1) {
		return false;
	}
	// checks if it is outside thge holes
	bool insidePoly = RFont::pointInPoligonWithoutCurve(polygons[0], point);
	bool insideHole = false;

	// checks if it is outside thge holes
	for (size_t i = 1; i < polygons.size(); ++i) {
		insideHole |= RFont::pointInPoligonWithoutCurve(polygons[i], point);
	}

	// if inside the contour and outside the holes then it is a negativ curve!
	return insidePoly && !insideHole;
}

} // Runic namespace
