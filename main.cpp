#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <math.h>

#include "chromosome.h"
using namespace std;

int selectOneFromPopulation(vector<chromosome>& population, bool best) {
	unsigned i = 0;
	double r = 1.*abs(rand()) / RAND_MAX;
	double curr = 0;

	while ((i < population.size()) && (r >= curr)) {
		//curr += population[i].getQuality() / qualitySum;
		curr += 2. * (i + 1) / (population.size() + 1) / population.size();
		i++;
	}
	return best ? i - 1 : population.size() - i;
}

int selectOne(int n) {
	return rand() % n;
}

bool use(double p) {
	double r = 1.*rand() / RAND_MAX;
	return r <= p;
}

int main() {
	int n, populationSize, iterationCount, maxEpsilonHit, partsCount;
	double selectionFactor, crossoverProbability, mutationProbability, inversionProbability;

	srand(time(0));
	cin >> n;
	cin >> populationSize >> iterationCount >> partsCount >> crossoverProbability >> inversionProbability >> mutationProbability >> maxEpsilonHit >> selectionFactor;

	vector<vector<double>> graph(n, vector<double>());

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double w;
			//cin >> w;
			w = use(.3) ? 10.*rand() / RAND_MAX : 0;
			graph.at(i).push_back(w);
		}
	}

	vector<chromosome> population;


	//Initial population
	for (int i = 0; i < populationSize; i++) {
		population.push_back(chromosome(n, partsCount, graph));
	}
	sort(population.begin(), population.end(), [](const chromosome& a, const chromosome& b) {return a.getQuality() > b.getQuality(); });
	auto best = population.end() - 1;
	chromosome bestChromosomeEver = *best;

	//Genetic algorithm iterations
	double epsilon = 1;
	double previousQuality;
	int epsilonHit = 0;
	int selectionSize = (int)(population.size() * selectionFactor);
	chromosome *children = new chromosome[2 * ((selectionSize + 1) / 2)];

	for (int t = 0; (t < iterationCount) && (epsilonHit < maxEpsilonHit); t++) {
		if (!(t % 10)) {
			cout << "Iteration " << t << ": " << best->getQuality() << endl;
		}
		previousQuality = best->getQuality();

		//Selection, crossover, inversion, mutation
		int childrenCount = 0;
		for (int k = 0; k < selectionSize; k += 2) {
			if (use(crossoverProbability)) {
				int i = selectOneFromPopulation(population, true);
				int j = i;
				while (j == i) {
					j = selectOneFromPopulation(population, true);
				}

				//crossover
				int crossoverPoint = selectOne(n - 1);
				chromosome c1 = chromosome::crossover(population[i], population[j], crossoverPoint, partsCount, false, graph);
				chromosome c2 = chromosome::crossover(population[i], population[j], crossoverPoint, partsCount, true, graph);

				//inversion
				if (use(inversionProbability)) {
					c1 = c1.inverse(selectOne(n - 1), selectOne(n - 1), graph);
				}
				if (use(inversionProbability)) {
					c2 = c2.inverse(selectOne(n - 1), selectOne(n - 1), graph);
				}

				//mutation
				if (use(mutationProbability)) {
					c1 = c1.mutate(selectOne(n - 1), selectOne(n - 1), graph);
				}
				if (use(mutationProbability)) {
					c2 = c2.mutate(selectOne(n - 1), selectOne(n - 1), graph);
				}

				children[childrenCount] = c1;
				children[childrenCount + 1] = c2;
				childrenCount += 2;
			}
		}
		population.insert(population.end(), children, children + childrenCount);

		//Reduction
		sort(population.begin(), population.end(), [](const chromosome& a, const chromosome& b) {return a.getQuality() > b.getQuality(); });
		while (population.size() != populationSize) {
			int i = selectOneFromPopulation(population, false);
			population.erase(population.begin() + i);
		}

		best = population.end() - 1;
		if (fabs(best->getQuality() - previousQuality) < epsilon) {
			epsilonHit++;
		}
		else {
			epsilonHit = 0;
		}

		if ((best->getQuality() < bestChromosomeEver.getQuality()) || (bestChromosomeEver.getQuality() == -1)) {
			bestChromosomeEver = *best;
		}
	}

	cout << bestChromosomeEver.getQuality() << endl;
	system("pause");
}