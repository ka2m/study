#include <iostream>

class Queen {
		public:
				int col, row;
				Queen* nb;

				Queen(int aCol, Queen *aNb) {
					col = aCol;
					nb = aNb;
					row = 0;
				}

				~Queen() {
					if (nb) delete nb;
				}

				bool canAttack(int aCol, int aRow);
				bool advance();
				bool findSolution();

				void print();
};
