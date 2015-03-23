#include "Student.h"

class Accounting {
public:
    static Accounting& getInstance()
    {
        static Accounting instance;
        return instance;
    }
    void updateScholarship(Student* student);
private:
    Accounting() {}

};