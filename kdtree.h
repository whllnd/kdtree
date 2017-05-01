#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

struct p3 {
	double x, y, z;
};

class kdtree {
public:

	kdtree(std::vector<std::shared_ptrp3 const*> pts, int depth=0) {
		construct(pts, depth);
	}
	kdtree(p3 const* p) : root_(std::shared_ptr<p3>(p)) {}

	void print(int depth=0) {
		std::cout << std::string(depth, '\t');
		std::cout << "[" << root_->x << " " << root_->y << " " << root_->z << "]" << std::endl;
		if (left_) { left_->print(depth+1); }
		if (right_) { right_->print(depth+1); }
	}

private:

	void construct(std::vector<p3 const*> pts, int depth);
	void add(p3 const* p);
	static bool sort(p3 const* a, p3 const* b, int axis);

	std::shared_ptr<p3> root_;
	std::unique_ptr<kdtree> left_;
	std::unique_ptr<kdtree> right_;
};

