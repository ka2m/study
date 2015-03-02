#include "Accounting.h"

int main(void)
{

    Student* s = new Student("Vladislav", "Slepukhin", "Dmitrievich", 0, 1, 0);
    Student* s2 = new Student("Blah", "Blah", "Blah", 0, 2, 4000);

    vector<int> marks1;
    marks1.push_back(5);
    marks1.push_back(5);
    marks1.push_back(5);
    s->setMarks(marks1);

    cout << s->getScholarship();
    Accounting a = Accounting::getInstance();
    a.updateScholarship(s);
    cout << s->getScholarship();

}

