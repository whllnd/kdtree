#include "kdtree.h"

bool kdtree::less(p3 const& a, p3 const& b, int axis) {
	if (0 == axis) { // x
		return (a.v[0] == b.v[0]) ? ((a.v[1] == b.v[1]) ? a.v[2] < b.v[2] : a.v[1] < b.v[1]) : a.v[0] < b.v[0];
	} else if (1 == axis) { // y
		return (a.v[1] == b.v[1]) ? ((a.v[0] == b.v[0]) ? a.v[2] < b.v[2] : a.v[0] < b.v[0]) : a.v[1] < b.v[1];
	} else { // z
		return (a.v[2] == b.v[2]) ? ((a.v[0] == b.v[0]) ? a.v[1] < b.v[1] : a.v[0] < b.v[0]) : a.v[2] < b.v[2];
	}
}

void kdtree::add(p3 const* p, int depth) {

	//int axis(depth % 3);
	//if (root_->v[axis] < p->v[axis]) { // Put it right
	//	if (right_) {
	//		right_->add(p, depth + 1);
	//	} else {
	//		right_ = std::unique_ptr<kdtree>(new kdtree(p));
	//	}
	//} else {
	//	if (left_) {
	//		left_->add(p, depth + 1);
	//	} else {
	//		left_ = std::unique_ptr<kdtree>(new kdtree(p));
	//	}
	//}
}


// Pass a copy, since we need to sort anyway
void kdtree::construct(
	std::vector<p3>::iterator const& s,
	std::vector<p3>::iterator const& e,
	int depth
) {
	// Grab 10% of random points and sort them to find median element
	// ...
	std::size_t size(std::distance(s, e));
	if (1 == size) {
		root_ = &(*s);
		return;
	}

	if (2 == size) {
		if (less(*s, *(s+1), axis)) {
			left_ = &(*s);
			root_ = std::unique_ptr<kdtree>(new kdtree(s+1, e));
		} else {
			root_ = &(*s);
			left_ = std::unique_ptr<kdtree>(new kdtree(s+1, e));
		}
		return;
	}

	// Sort points along current axis
	int axis(depth % 3);
	std::sort(s, e,
		[&](p3 const& a, p3 const& b) {
			return kdtree::less(a, b, axis);
		}
	);

	// Take the median as the root
	int median(size / 2);
	root_ = &(*(s + median));
	left_  = std::unique_ptr<kdtree>(new kdtree(s, s + median, depth + 1));
	right_ = std::unique_ptr<kdtree>(new kdtree(s + median + 1, e, depth + 1));
}
