#ifndef LINKED_LIST
#define LINKED_LIST

#include "list.h"
#include <stdexcept>

template<class T>
class LinkedList;

template<class T>
class ListNode {
    friend class LinkedList<T>;
private:
    T val;
    ListNode *next;
public:
    ListNode() : next(nullptr) {}
    ListNode(T val) : val(val), next(nullptr) {}
};

template<class T>
class LinkedList : public List<T> {
private:
    ListNode<T> *head;  // this implementation has a dummy head (sentry head node)
    size_t num_of_element;

public:
    LinkedList() {
        head = new ListNode<T>();
        num_of_element = 0;
    }

    LinkedList(size_t capacity) : LinkedList<T>() {} // to make test consistent

    // copy constructor
    LinkedList(const LinkedList<T> &other_list) : LinkedList() {
        // Reach both dummy nodes
        ListNode<T>* current = head;
        ListNode<T>* current_other = other_list.head;

        // Loop until end of other list
        while (current_other->next != nullptr)
        {
            // First, peek at the next element of other list
            current_other = current_other->next;

            // Create a copy of other list node into heap (deep copy)
            ListNode<T>* new_node = new ListNode<T>(current_other->val);
            current->next = new_node;
            num_of_element++;

            // Lastly, traverse this list current
            current = current->next;
        }
    }

    // destructor
    virtual ~LinkedList() {
        ListNode<T> *p0 = head, *p1 = head->next;
        if (p1 == nullptr) {
            delete p0;
            return;
        }

        while (p1 != nullptr) {
            delete p0;
            p0 = p1;
            p1 = p1->next;
        }
        delete p0;
    }

    size_t capacity() const override {
        return num_of_element;
    }

    size_t size() const override {
        return num_of_element;
    }

    T &operator[](size_t index) {
        if (index >= num_of_element) {
            throw std::out_of_range("index out of range");
        }
        ListNode<T> *p = head;
        for (size_t i = 0; i < index; i++) {
            p = p->next;
        }
        return p->next->val;
    }

    bool operator==(const LinkedList<T> &other_list) {
        if (num_of_element != other_list.num_of_element) {
            return false;
        }

        ListNode<T> *p1 = head->next;
        ListNode<T> *p2 = other_list.head->next;
        for (size_t i = 0; i < num_of_element; i++) {
            if (p1 == nullptr || p2 == nullptr) {
                return false;
            }

            if (p1->val != p2->val) {
                return false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        return true;
    }

    void push_front(const T &value) override;

    void push_back(const T &value) override;

    void pop_back() override;

    void pop_front() override;

    void remove(T &val) override;

    void merge(const List<T> &other) override;

    void reverse_iterative() override;

    // My own functions
    virtual bool exists(T &val);

    virtual void insert(T &val, int index);
};

#include "linked_list.cpp"

#endif