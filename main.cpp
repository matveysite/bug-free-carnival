#include <iostream>
#include <vector>
#include <time.h>

#include "chromosome.h"
using namespace std;



int main() {
	srand(time(0));
	int n;
	int populationSize;
	cin >> n;

	vector<vector<double> > graph(n, vector<double>());

	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		for (int j = 0; j < t; j++) {
			double w;
			cin >> w;
			graph.at(i).push_back(w);
		}
	}

	vector<chromosome> population();
	for (int i = 0; i < populationSize; i++) {

	}
}