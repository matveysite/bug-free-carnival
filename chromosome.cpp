#include "chromosome.h"
#include <algorithm>
#include <vector>
using namespace std;

chromosome::chromosome(): ch(), quality(-1) {
}

void chromosome::countQuality(const vector<vector<double>>& graph) {
	quality = 0;
	for (unsigned i = 0; i < graph.size(); i++) {
		for (unsigned j = 0; j < graph.size(); j++) {
			if (ch[i] != ch[j]) {
				quality += graph[i][j];
			}
		}
	}
}

chromosome::chromosome(const chromosome& chromosome): ch(chromosome.ch), quality(chromosome.quality) {
}

chromosome & chromosome::operator=(const chromosome& chromosome) {
	ch = chromosome.ch;
	quality = chromosome.quality;
	return *this;
}

chromosome::chromosome(int n, int partsCount, const vector<vector<double>>& graph) {
	while (ch.size() != n) {
		int i;
		for (i = 0; (i < partsCount) && (ch.size() != n); i++) {
			ch.push_back(i);
		}
		random_shuffle(ch.end() - i, ch.end());
	}
	countQuality(graph);
}

chromosome chromosome::crossover(const chromosome& c1, const chromosome& c2, int p, int partsCount, bool first, const vector<vector<double>> graph) {
	chromosome result;
	const chromosome& cf = first ? c1 : c2;
	const chromosome& cs = first ? c2 : c1;

	for (unsigned i = 0; i < p + 1; i++) {
		result.ch.push_back(cf.ch[i]);
	}

	int *partsNeeded = new int[partsCount]();
	for (unsigned i = p + 1; i < cf.ch.size(); i++) {
		partsNeeded[cf.ch[i]]++;
	}

	for (unsigned i = p + 1; i < cs.ch.size(); i++) {
		int t = cs.ch[i];
		if (partsNeeded[t] != 0) {
			result.ch.push_back(t);
			partsNeeded[t]--;
		}
	}

	for (unsigned i = 0; (i < p + 1) && (result.ch.size() != cs.ch.size()); i++) {
		int t = cs.ch[i];
		if (partsNeeded[t] != 0) {
			result.ch.push_back(t);
			partsNeeded[t]--;
		}
	}

	result.countQuality(graph);
	return result;
}

chromosome chromosome::mutate(int i, int j, const vector<vector<double>>& graph) const {
	chromosome result(*this);
	int t = result.ch[i];
	result.ch[i] = result.ch[j];
	result.ch[j] = t;
	result.countQuality(graph);
	return result;
}

chromosome chromosome::inverse(int start, int end, const vector<vector<double>>& graph) {
	chromosome result(*this);
	for (int i = start; i < (start + end + 1) / 2; i++) {
		swap(result.ch[i], result.ch[end - i + start]);
	}
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
