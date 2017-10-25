#pragma once
#include <vector>
#include <iostream>

class chromosome {
public:
	chromosome(const chromosome&);
	chromosome& operator=(const chromosome&);
	chromosome(int, int, std::vector<std::vector<double>>&);
	static chromosome crossover(const chromosome&, const chromosome&, int, bool, std::vector<std::vector<double>>);
	chromosome mutate(int, int, std::vector<std::vector<double>>&) const;
	double getQuality() const;
	friend std::ostream& operator<<(std::ostream&, chromosome&);
private:
	chromosome();
	std::vector<int> ch;
	void countQuality(std::vector<std::vector<double>>&);
	double quality;
};