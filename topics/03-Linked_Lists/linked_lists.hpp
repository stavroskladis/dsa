#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#include <concepts>
#include <iostream>
#include <memory>

// Concept to ensure T is printable (has operator<< for std::ostream)
template <typename T>
concept Printable = requires(std::ostream& os, const T& t) { os << t; };

template <Printable T>
class Node {
  private:
    T data;

  public:
    std::unique_ptr<Node<T>> next;

    Node(const T& value) : data(value), next(nullptr) {}

    // Getter for data
    const T& getData() const {
        return data;
    }
    T& getData() {
        return data;
    }

    // Stream output operator (friend function)
    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
        os << node.data;
        return os;
    }
};

template <Printable T>
class LinkedList {
  private:
    std::unique_ptr<Node<T>> head;

  public:
    LinkedList() : head(nullptr) {}

    // Allowing recursive destruction of the Nodes can overflow the stack.
    // To pevent this we need an iterative destructor
    ~LinkedList() {
        while (head) {
            auto next = std::move(head->next);
            head = std::move(next);
        }
    }

    // Traverse the list and print all elements
    void print() const {
        const Node<T>* current = head.get();

        while (current) {
            std::cout << *current << " "; // Use operator<<
            current = current->next.get();
        }
        std::cout << std::endl;
    }

    int count() const {
        const Node<T>* current = head.get();
        int count = 0;

        while (current) {
            ++count;
            current = current->next.get();
        }

        return count;
    }

    bool empty() const {
        return head == nullptr;
    }

    void push_front(const T& data) {
        auto new_node = std::make_unique<Node<T>>(data);
        new_node->next = std::move(head);
        head = std::move(new_node);
    }
};

#endif
