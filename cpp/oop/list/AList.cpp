#include "AList.h"


template <typename ListItem>
void AList<ListItem>::add(ListItem li) {
    PrivateListItem *pLItem = new PrivateListItem;
    pLItem->__crnt = li;
    if (_count > -1) {//If the list contains one or more items
        pLItem->__nxt = _first;
        pLItem->__prv = _last;
        _last->__nxt = pLItem;
        _last = pLItem;
        _count++;
    }
    else if (_count == -1) {//If no items are present in the list
        _first = pLItem;
        _first->__nxt = pLItem;
        _first->__prv = pLItem;
        _last = pLItem;
        last->__nxt = pLItem;
        last->__prv = pLItem;
        count = 0;
    }
}


template <typename ListItem>
void AList<ListItem>::removeAt(int index) {
    if (int index) {
        if (index <= _count) {
            PrivateListItem *pLItem = last;
            for (int i = 0; i <= index; i++) {
                pLItem = pLItem->__nxt;
            }
            pLItem->__prv->__nxt = pLItem->__nxt;
            pLItem->__nxt->__prv = pLItem->__prv;
            delete pLItem;
            _count--;
        }
    }
}

template <typename ListItem>
ListItem AList<ListItem>::get(int index) {
    PrivateListItem *pLItem = first;
    if (index <= _count && index > -1) {
        int i = 0;
        while (i < index) {
            pLItem = pLItem->__nxt;
            i++;
        }
    }

    return pLItem->__crnt;
}


template <typename ListItem>
ListItem AList<ListItem>::first(){
    return _first->__crnt;
}

template <typename ListItem>
ListItem AList<ListItem>::Last(){
    return _last->__crnt;
}

template <typename ListItem>
int AList<ListItem>::Count(){
    return _count;
}

template <typename ListItem>
void AList<ListItem>::clear() {
    PrivateListItem *pLItem = first;
    while (count > -1) {
        PrivateListItem *tbdListItem = pLItem;
        pLItem = pLItem->__nxt;
        delete tbdListItem;
        count--;
    }
}

template <typename ListItem>
AList<ListItem>::~AList(){
    if (_count > -1){
        clear();
    }
}