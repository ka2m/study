#include "Queen.h"

int main(void) {
		Queen * lastQueen = NULL;
		for (int i = 0; i < 8; i++) {
				lastQueen = new Queen(i, lastQueen);
				lastQueen->findSolution();
		}
		lastQueen->print();
		delete lastQueen;
}
