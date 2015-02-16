#include "Accounting.h"

int main(void)
{
    Student* s = new Student("Vladislav", "Slepukhin", "Dmitrievich", 0, 1, 0);
    Accounting ac = ac.getInstance();
    cout << s->getScholarship() << endl;
    
    vector<int> marks;
    for (int i = 0; i < 5; i++)
        marks.push_back(5);
    s->setMarks(marks);

    ac.updateScholarship(s);

    cout << s->getScholarship();
}

