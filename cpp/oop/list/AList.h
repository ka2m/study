#ifndef ALIST_H
#define ALIST_H
template <typename ListItem>
class AList {
private:
	struct PrivateListItem {
		PrivateListItem *__prv;
		PrivateListItem *__nxt;
		ListItem __crnt;
	};

	PrivateListItem *_last;
	PrivateListItem *_first;
	int _count;
public:
	AList();

	~AList();

	ListItem first();

	ListItem last();

	int count();

	void add(ListItem listItem);

	void removeAt(int index);

	ListItem get(int index);

	void clear();
};
#endif //ALIST_H 