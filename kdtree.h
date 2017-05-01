#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

struct p3 {
	double v[3];
};

class kdtree {
public:

	kdtree(std::vector<p3>::iterator const& s, std::vector<p3>::iterator e, int depth=0)
	: root_(nullptr)
	{
		construct(s, e, depth);
	}
	kdtree(p3 const* p) : root_(p) {}

	void print(int depth=0) {
		std::cout << std::string(depth, '\t');
		std::cout << "[" << root_->v[0] << " " << root_->v[1] << " " << root_->v[2] << "]" << std::endl;
		if (left_) { left_->print(depth+1); }
		if (right_) { right_->print(depth+1); }
	}

private:

	void construct(std::vector<p3>::iterator const& s, std::vector<p3>::iterator const& e, int depth);
	static bool less(p3 const& a, p3 const& b, int axis);
	void add(p3 const* p, int depth);

	p3 const* root_;
	std::unique_ptr<kdtree> left_;
	std::unique_ptr<kdtree> right_;
};

