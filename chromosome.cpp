#include "chromosome.h"
#include <algorithm>
#include <vector>
using namespace std;

chromosome::chromosome(): ch() {
}

void chromosome::countQuality(vector<vector<double>>& graph) {
	bool *part = new bool[graph.size()]();
	vector<int> firstPart = ch;
	for (int p : firstPart) {
		part[p] = true;
	}
	vector<int> secondPart;
	secondPart.reserve(graph.size() - firstPart.size());
	for (int i = 0; i < graph.size(); i++) {
		if (!part[i]) {
			secondPart.push_back(i);
		}
	}
	delete[] part;

	quality = 0;
	for (auto i = firstPart.begin(); i != firstPart.end(); i++) {
		for (auto j = secondPart.begin(); j != secondPart.end(); j++) {
			quality += graph[*i][*j] + graph[*j][*i];
		}
	}
	quality = 1/ (quality + 0.001);
}

chromosome::chromosome(const chromosome& chromosome): ch(chromosome.ch), quality(chromosome.quality) {
}

chromosome & chromosome::operator=(const chromosome& chromosome) {
	ch = chromosome.ch;
	quality = chromosome.quality;
	return *this;
}

chromosome::chromosome(int n, int size, vector<vector<double> >& graph) {
	while (ch.size() != size) {
		int t = rand() % n;
		if (find(ch.begin(), ch.end(), t) == ch.end()) {
			ch.push_back(t);
		}
	}
	countQuality(graph);
}

chromosome chromosome::crossover(const chromosome& c1, const chromosome& c2, int p, bool first, vector<vector<double> > graph) {
	chromosome result;
	const chromosome& cf = first ? c1 : c2;
	const chromosome& cs = first ? c2 : c1;

	for (int i = 0; i < p + 1; i++) {
		result.ch.push_back(cf.ch[i]);
	}

	int position = cs.ch.size() - 1;
	while (result.ch.size() != cs.ch.size()) {
		int t = cs.ch[position];
		if (find(result.ch.begin(), result.ch.begin() + p + 1, t) == (result.ch.begin() + p + 1)) {
			result.ch.push_back(t);
		}
		position--;
	}
	result.countQuality(graph);
	return result;
}

chromosome chromosome::mutate(int i, int j, vector<vector<double>>& graph) const {
	chromosome result(*this);
	int t = result.ch[i];
	result.ch[i] = result.ch[j];
	result.ch[j] = t;
	result.countQuality(graph);
	return result;
}

double chromosome::getQuality() const {
	return quality;
}

ostream& operator<<(ostream& out, chromosome& chromosome) {
	for (int a : chromosome.ch) {
		out << a << " ";
	}
	return out;
}
