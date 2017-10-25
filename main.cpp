#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <math.h>

#include "chromosome.h"
using namespace std;

int selectOneFromPopulation(vector<chromosome>& population, double qualitySum, bool best) {
	int i = 0;
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
	srand(time(0));
	int n, populationSize, iterationCount, firstPartSize, maxEpsilonHit;
	double crossoverProbability, mutationProbability;
	cin >> n;
	cin >> populationSize >> iterationCount >> firstPartSize >> crossoverProbability >> mutationProbability >> maxEpsilonHit;

	vector<vector<double> > graph(n, vector<double>());

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
		population.push_back(chromosome(n, firstPartSize, graph));
	}


	//Genetic algorithm iterations
	bool firstIteration = true;
	double epsilon = 0;
	double previousQuality = 0, qualitySum = 0;
	int epsilonHit = 0;

	for (int t = 0; (t < iterationCount) && (epsilonHit < maxEpsilonHit); t++) {
		cout << "Iteration " << t << ": ";
		sort(population.begin(), population.end(), [](const chromosome& a, const chromosome& b) {return a.getQuality() < b.getQuality(); });
		chromosome best = *(population.end() - 1);
		cout << 1/best.getQuality() << endl;
		if (firstIteration) {
			for (int i = 0; i < population.size(); i++) {
				qualitySum += population[i].getQuality();
			};
			firstIteration = false;
			previousQuality = qualitySum;
		}

		//Selection, crossover, mutation
		int selectionSize = population.size() / 3 * 2;
		vector<chromosome> children;
		double childrenQuality = 0;
		for (int k = 0; k < selectionSize; k += 2) {
			if (use(crossoverProbability)) {
				int i = selectOneFromPopulation(population, qualitySum, true);
				int j = i;
				while (j == i) {
					j = selectOneFromPopulation(population, qualitySum, true);
				}
				int crossoverPoint = selectOne(firstPartSize - 1);
				chromosome c1 = chromosome::crossover(population[i], population[j], crossoverPoint, false, graph);
				chromosome c2 = chromosome::crossover(population[i], population[j], crossoverPoint, true, graph);
				if (use(mutationProbability)) {
					c1 = c1.mutate(selectOne(firstPartSize - 1), selectOne(firstPartSize - 1), graph);
				}
				if (use(mutationProbability)) {
					c2 = c2.mutate(selectOne(firstPartSize - 1), selectOne(firstPartSize - 1), graph);
				}
				children.push_back(c1);
				children.push_back(c2);
				childrenQuality += c1.getQuality() + c2.getQuality();
			}
		}
		population.insert(population.end(), children.begin(), children.end());
		qualitySum += childrenQuality;

		//Reduction
		sort(population.begin(), population.end(), [](const chromosome& a, const chromosome& b) {return a.getQuality() < b.getQuality(); });
		while (population.size() != populationSize) {
			int i = selectOneFromPopulation(population, qualitySum, false);
			qualitySum -= population[i].getQuality();
			population.erase(population.begin() + i);
		}
		if (fabs(qualitySum - previousQuality) < epsilon) {
			epsilonHit++;
		}
		else {
			epsilonHit = 0;
		}
		previousQuality = qualitySum;
		epsilon = qualitySum / 10000000;
	}


	//Result output
	chromosome best = *(population.end() - 1);
	//cout << best;
	system("pause");
}