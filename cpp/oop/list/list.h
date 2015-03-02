#ifndef LIST_H
#define LIST_H
#include "../univeristy/Student.h"

class List
{
private:
	int __size;
	vector<Student> __list;

public:
	List();
	List(int size);
	void insert(Student& student);
	Student getAt(int index);
	Student get(Student& student);
	bool removeAt(int index);
	bool remove(Student& student);
	bool removeAll();
	int size();
};

#endif //queue.h