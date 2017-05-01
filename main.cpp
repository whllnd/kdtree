#include "kdtree.h"

int main() {

	std::vector<p3> pts;
	for (std::size_t i(0); i < 5; i++) {
		pts.push_back(p3{ rand() % 10, rand() % 10, rand() % 10 });
		std::cout << "[" << pts.back().v[0] << " " << pts.back().v[1] << " " << pts.back().v[2] << "]" << std::endl;
	}
	std::cout << "---" << std::endl;
	kdtree kd(pts.begin(), pts.end());
	for (std::size_t i(0); i < pts.size(); i++) {
		std::cout << "[" << pts[i].v[0] << " " << pts[i].v[1] << " " << pts[i].v[2] << "]" << std::endl;
	}
	kd.print();

}
