#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/geometries/point.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)
namespace bg = boost::geometry;
using boost::geometry::dsv;
using boost::geometry::get;
typedef boost::tuple<double, double> point;
typedef boost::geometry::model::polygon<point> polygon;
typedef boost::geometry::model::referring_segment<point> segment;
typedef boost::geometry::model::point<float, 2, bg::cs::cartesian> cPoint;

template<typename Point>
void get_coordinates(Point const& p) {
	std::cout << get<0>(p) << " , " << get<1>(p) << std::endl;

}

template<typename Segment>
void get_segments(Segment const& s) {

	std::cout << dsv(s) << std::endl;
	std::cout << "Distance " << dist(s, point(2.0, 1.3)) << endl;
}

double dist(segment s, point p) {

	return boost::geometry::distance(point(2.0, 1.3), s);

}

int main() {

	polygon poly;
	boost::geometry::read_wkt(
			"polygon((2.0 1.3, 2.4 1.7, 2.8 1.8, 3.4 1.2, 3.7 1.6, 3.4 2.0, 4.1 3.0, 5.3 2.6, 5.4 1.2, 4.9 0.8, 2.9 0.7, 2.0 1.3))",
			poly);

	polygon hull;
	boost::geometry::convex_hull(poly, hull);

	// Now I know I can `dsv()` and print to the screen like this:

	std::cout << "hull: " << dsv(hull) << std::endl;

	// And/Or I can use my function with for_each_point()

	boost::geometry::for_each_point(boost::geometry::exterior_ring(hull),
			get_coordinates<point>);
	boost::geometry::for_each_segment(boost::geometry::exterior_ring(hull),
			get_segments<segment>);
	// std::cout <<"within"<<boost::geometry::overlaps(point(2.0,1.3),poly);

	return 0;
}
