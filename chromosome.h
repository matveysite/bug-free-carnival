#pragma once
#include <vector>

class chromosome {
public:
	chromosome();
	chromosome(const chromosome&);
	chromosome& operator=(const chromosome&);
	static chromosome randomCreate();

private:
	std::vector<int> ch;
};