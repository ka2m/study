#include "Queen.h"

bool Queen::canAttack(int aCol, int aRow) {
		if (col == aCol) return true;
		if (row == aRow) return true;
		if (abs(col - aCol) == abs(row - aRow)) return true;

		if (!nb) return false;
		return nb->canAttack(aCol, aRow);
}

bool Queen::advance() {
		if (row < 7) {
				row++;
				return this->findSolution();
		}

		if (!nb) return false;

		if (nb->advance()) {
				row = 1;
				return this->findSolution();
		}

		return false;
}

bool Queen::findSolution() {
		if (!nb) return true;

		if (nb->canAttack(col, row)) {
				while (nb->canAttack(col, row))
					if (!(this->advance()))
						return false;
		}
		return true;
}

void Queen::print() {
	if (nb) nb->print();
	for (int i = 0; i < 8; i++) {
		if (row == i) 
			std::cout << "*"; 
		else
			std::cout << "_";
	}
	std::cout << std::endl;
}




