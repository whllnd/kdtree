#include "kdtree.h"

bool kdtree::sort(p3 const* a, p3 const* b, int axis) {
	if (0 == axis) { // x
		if (a->x == b->x) {
			if (a->y == b->y) {
				return a->z < b->z;
			} else {
				return a->y < b->y;
			}
		} else {
			return a->x < b->x;
		}
	} else if (1 == axis) { // y
		if (a->y == b->y) {
			if (a->x == b->x) {
				return a->z < b->z;
			} else {
				return a->x < b->x;
			}
		} else {
			return a->y < b->y;
		}
	} else {
		if (a->z == b->z) {
			if (a->x == b->x) {
				return a->y < b->y;
			} else {
				return a->x < b->x;
			}
		} else {
			return a->z < b->z;
		}
	}
}

void kdtree::add(p3 const* pts) { }


// Pass a copy, since we need to sort anyway
void kdtree::construct(std::vector<std::shared_ptr<p3>> pts, int depth) {

	// Grab 10% of random points and sort them to find median element
	//std::size_t p(pts.size() * 0.1);
	//for (std::size_t i(0); i < p; p++) {
	//	std::size_t ridx(rand() % pts.size());
	std::cout << pts.size() << std::endl;
	if (1 == pts.size()) {
		root_ = std::shared_ptr<p3>(pts[0]);
		return;
	}

	// Sort points along current axis
	int axis(depth % 3);
	std::sort(pts.begin(), pts.end(),
		std::bind(&kdtree::sort, std::placeholders::_1, std::placeholders::_2, axis)
	);

	if (2 == pts.size()) {
		root_ = std::shared_ptr<p3>(pts[0]);
		right_ = std::unique_ptr<kdtree>(new kdtree(pts[1]));
		return;
	}

	// Take the median as the root
	int median(pts.size() / 2);
	std::cout << "m: " << median << std::endl;
	root_ = pts.at(median);
	left_ = std::unique_ptr<kdtree>(new kdtree(std::vector<p3 const*>(&pts[0], &pts[median]), depth + 1));
	right_ = std::unique_ptr<kdtree>(new kdtree(std::vector<p3 const*>(&pts[median+1], &pts[pts.size()]), depth + 1));
}
