#ifndef LINEARLIST_H
#define LINEARLIST_H


template <typename ListType>
struct ListNode {
    ListType
            datum;
    ListNode<ListType>
            * next;
};

template <typename ListType>
class LinearList {
private:
    ListNode<ListType>
            * head;
    int
            count;
public:
    LinearList();
    LinearList(const LinearList<ListType>&);
    ~LinearList();

    int size();
    bool isEmpty();

    void clear();

    int search(const ListType&);
    ListType& operator[](int);

    void map(void (*)(ListType&));

    void insert(int, const ListType&);
    void remove(int);

};

#include "linearlist-implementation.h"

#endif //LINEARLIST_H