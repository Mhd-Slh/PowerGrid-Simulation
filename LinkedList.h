#pragma once

template<typename T>
class Node {
public:
    Node* next;
    T data;
};

template<typename T>
class LinkedList
{
private:
    Node<T>* head;

public:
    //Constructor, initialized to automatically create the head when the List is created
    LinkedList() : head(nullptr) {}

    //Deconstructor, to automatically deallocate the memory of every node in the List after the ending of the code
    ~LinkedList() {}

    //insert(T x), inserts new nodes with specified data after the head (at the front)
    void insert(T x)
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = x;

        if (!head || (*x < *head->data))
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node<T>* current = head;

        while (current->next && *current->next->data < *x)
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    //emptyList(), deletes all nodes in the List
    void emptyList()
    {
        Node<T>* current = head;

        while (current)
        {
            Node<T>* toDelete = current;

            current = current->next;

            delete toDelete->data;
            delete toDelete;
        }

        head = nullptr;
    }

    // Iterator for LinkedList
    class Iterator
    {
    private:
        Node<T>* current;

    public:
        Iterator(Node<T>* start) : current(start) {}

        T operator*() const { return current->data; }

        Iterator& operator++()
        {
            if (current) current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }

};