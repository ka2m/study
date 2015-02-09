#include "Queen.h"

bool Queen::canAttack(int aCol, int aRow) {
		if (col == aCol) return true;
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
				while (this->advance())
					if (!(nb->canAttack(col, row)))
						return true;
		}
		return false;
}

void Queen::print() {
	if (nb) nb->print();
	std::cout << row << " " << col << std::endl;
}




