#include "chromosome.h"

chromosome::chromosome(): ch() {
}

chromosome::chromosome(const chromosome& chromosome): ch(chromosome.ch) {
}

chromosome & chromosome::operator=(const chromosome& chromosome) {
	ch = chromosome.ch;
}

chromosome chromosome::randomCreate() {
	return chromosome();
}