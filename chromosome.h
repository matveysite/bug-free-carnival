#pragma once
#include <vector>
#include <iostream>

class chromosome {
public:
	chromosome();
	chromosome(const chromosome&);
	chromosome& operator=(const chromosome&);
	chromosome(int, int, const std::vector<std::vector<double>>&);
	static chromosome crossover(const chromosome&, const chromosome&, int, int, bool, const std::vector<std::vector<double>>&);
	chromosome mutate(int, int, const std::vector<std::vector<double>>&) const;
	chromosome inverse(int, int, const std::vector<std::vector<double>>&);
	double getQuality() const;
	friend std::ostream& operator<<(std::ostream&, chromosome&);
private:
	std::vector<int> ch;
	void countQuality(const std::vector<std::vector<double>>&);
	double quality;
};