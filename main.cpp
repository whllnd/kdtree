#include "kdtree.h"

int main() {

	std::vector<std::unique_ptr<p3 const>> pts{
		std::unique_ptr<p3 const>(new p3{2, 3, 1}),
		std::unique_ptr<p3 const>(new p3{2, 2, 1}),
		std::unique_ptr<p3 const>(new p3{1, 1, 0}),
		std::unique_ptr<p3 const>(new p3{5, 6, 3})
	};
	kdtree kd(pts);
	kd.print();
}
