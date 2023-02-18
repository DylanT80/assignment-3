#include "linked_list.h"

template<class T>
void LinkedList<T>::push_front(const T &value) {
    ListNode<T>* temp = head->next;
    ListNode<T>* new_node = new ListNode<T>(value);

    new_node->next = temp;
    head->next = new_node;
    num_of_element++;
}

template<class T>
void LinkedList<T>::push_back(const T &value) {
    // Reach dummy node
    ListNode<T>* current = head;
    // Loop until end of list
    while(current->next != nullptr)
        current = current->next;
    // Add new node
    current->next = new ListNode<T>(value);
    num_of_element++;
}

template<class T>
void LinkedList<T>::pop_back() {
    // No elements in list
    if (size() == 0)
        return;
    // If list is of one size
    if (size() == 1)
    {
        ListNode<T>* temp = head->next;
        head->next = nullptr;
        delete temp;
        num_of_element--;
        return;
    }
    // 1+ list size
    // Reach dummy node
    ListNode<T>* current = head;
    // Loop until node before last node (2nd to last node)
    while(current->next->next != nullptr)
        current = current->next;
    // Delete the last node
    ListNode<T>* temp = current->next;
    current->next = nullptr;
    delete temp;
    num_of_element--;

}

template<class T>
void LinkedList<T>::pop_front() {
    // No elements in list
    if (size() == 0)
        return;
    // One element in list is same as pop_back function
    if (size() == 1)
    {
        pop_back();
        return;
    }
    // 1+ list size
    // Delete first element
    ListNode<T>* temp = head->next;
    head->next = head->next->next;
    delete temp;
    num_of_element--;
}

template<class T>
void LinkedList<T>::remove(T &val) {
    // If list is of one size
    if (size() == 1)
    {
        ListNode<T>* temp = head->next;
        // If first element is not target, return
        if (temp->val != val)
            return;
        // Same functionality as pop_front
        pop_front();
        return;
    }
    while (exists(val))
    {    // If list is of 1+ size
        ListNode<T> *current = head;
        // Loop until current is node before target node
        while (current->next->val != val && current->next != nullptr) {
            current = current->next;
        }
        if (current->next->val == val) {
            ListNode<T> *temp = current->next;
            current->next = current->next->next;
            delete temp;
            num_of_element--;
        }
    }
}

/*
 * merge in ascending order
 */
template<class T>
void LinkedList<T>::merge(const List<T> &ot) {
    // Dynamic cast to Linked List
    auto &other_list = (LinkedList<T> &) ot;

    // Reach dummy nodes of both lists
    ListNode<T>* current = head;
    ListNode<T>* current_other =  other_list.head;

    // Keep track of position in list
    int position = 0;

    // Loop until one or both lists are done iterating itself
    while (current->next != nullptr && current_other->next != nullptr)
    {
        // Compare values
        T& value = current->next->val;
        T& other_value = current_other->next->val;
        // If original list is smaller
        if (value < other_value)
        {
            current = current->next;
        }
        // If other list is smaller, insert other value at current position
        else
        {
            insert(other_value, position);
            current_other = current_other->next;
            // Update "this" current to not lose it positioning since its altered when inserting new node
            // New current is the newly added node since it delays its path by 1 node
            current = current->next;
        }
        // Increase position by 1
        position++;
    }
    // Add the rest of the other list if needed
    while (current_other->next != nullptr)
    {
        current_other = current_other->next;
        push_back(current_other->val);
    }
}

template<class T>
void LinkedList<T>::reverse_iterative() {
    // Keep track of original list size and a counter to loop
    int temp = size();
    int counter = temp;
    // Loop until end of original size of list
    for (int i = 0; i < counter; i++)
    {
        // Push first element to original size index
        insert(head->next->val,temp);
        // Pop the front
        pop_front();
        // Adjust temp size since pop reduces the original sie index by 1
        temp--;
    }
}
// My own functions

// Checks if value is in the list
// True if value is in list
// False if value is not in list
template<class T>
bool LinkedList<T>::exists(T &val)
{
    ListNode<T>* current = head;
    // Loop through the whole list
    // Return true if value found
    while (current->next != nullptr)
    {
        current = current->next;
        // Check if value is found
        if (current->val == val)
            return true;
    }
    // Return false if value not in list
    return false;
}

template<class T>
void LinkedList<T>::insert(T &val, int index)
{
    // Same as pushing to the front
    if (index == 0)
    {
        push_front(val);
        return;
    }

    // Within the list
    ListNode<T>* current = head;
    // Loop until current is the node before target position
    for (int i = 0; i < index; i++)
        current = current->next;
    // Add new node to position index
    ListNode<T>* new_node = new ListNode(val);
    new_node->next = current->next;
    current->next = new_node;
    num_of_element++;
}