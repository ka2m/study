#include "Accounting.h"

int evalMoney(short level, short year) {
    int base = 1800;
    switch (level) {
        case 2: base = 2100; break;
        case 3: base = 2500; break;
        default:break;
    }
    return int(base + base * 0.5 * year);
}

void Accounting::updateScholarship(Student* student) {
    short level = 3;

    vector<int> marks = student->getMarks();
    bool hasFour = 0;
    bool hasFive = 0;
    for (int i = 0; i < marks.size(); i++) {
        // any not passed exam or 3
        if (marks[i] <= 3) {
            level = 0;
            break;
        }
        if (marks[i] == 4) {
            level = 1;
            hasFour = 1;
        }
        if (marks[i] == 5) {
            level = 2;
            hasFive = 1;
        }
    }

    if (!level) {
        student->setScholarship(0);
        return;
    }

    if (!hasFour && hasFive) level = 3;

    student->setScholarship(evalMoney(level, student->getYear()));
}


