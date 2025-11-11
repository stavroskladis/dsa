#ifndef LINKED_LISTS_HPP
#define LINKED_LISTS_HPP

#include <concepts>
#include <iostream>
#include <memory>

// Concept to ensure T is printable (has operator<< for std::ostream)
template <typename T>
concept Printable = requires(std::ostream& os, const T& t) { os << t; };

template <typename T>
class Node {
  private:
    T data;

  public:
    std::unique_ptr<Node<T>> next;

    explicit Node(const T& value) : data(value), next(nullptr) {}
    explicit Node(T&& value) : data(std::move(value)), next(nullptr) {}
    Node(Node&& other) noexcept
        : data(std::move(other.data)), next(std::move(other.next)) {}
    Node& operator=(Node&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            next = std::move(other.next);
        }
        return *this;
    }
    // Copy Node ctor and copy Node assignment are auto deleted due to unique_ptr

    constexpr const T& getData() const noexcept {
        return data;
    }
    constexpr T& getData() noexcept {
        return data;
    }

    // Stream output operator for Node.
    // Requires T to be printable (built-in types work automatically,
    // custom types need operator<< overloaded).
    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node)
        requires Printable<T>
    {
        os << node.data;
        return os;
    }

    friend bool operator==(const Node<T>& lhs, const Node<T>& rhs) {
        return lhs.data == rhs.data;
    }

    // DRY principle, consistency  and maintainability, use operator==
    // If we change the equality operator, no change needed here
    friend bool operator!=(const Node<T>& lhs, const Node<T>& rhs) {
        return !(lhs == rhs);
    }
};

template <typename T>
class LinkedList {
  private:
    std::unique_ptr<Node<T>> head;

    void clear_impl() {
        while (head) {
            auto next = std::move(head->next);
            head = std::move(next);
        }
    }

  public:
    constexpr LinkedList() : head(nullptr) {}

    // Move constructor and move assignment are explicitly deleted
    LinkedList(LinkedList&&) = delete;
    LinkedList& operator=(LinkedList&&) = delete;

    // Copy constructor and copy assignment are auto deleted due to unique_ptr

    // Allowing recursive destruction of the Nodes can overflow the stack.
    // To prevent this we need an iterative destructor
    ~LinkedList() {
        clear_impl();
    }

    void clear() noexcept {
        clear_impl();
    }

    // Traverse the list and print all elements.
    // We constrain only the print method instead of the class for flexibility.
    // Built-in types (int, string, etc.) work automatically.
    // Custom types require an overloaded operator<< for std::ostream.
    void print() const
        requires Printable<T>
    {
        const Node<T>* current = head.get();

        while (current) {
            std::cout << *current << " "; // Use operator<<
            current = current->next.get();
        }
        std::cout << std::endl;
    }

    constexpr int size() const noexcept {
        const Node<T>* current = head.get();
        int size = 0;

        while (current) {
            ++size;
            current = current->next.get();
        }

        return size;
    }

    constexpr bool empty() const noexcept {
        return head == nullptr;
    }

    void push_front(const T& data) {
        auto new_node = std::make_unique<Node<T>>(data);
        new_node->next = std::move(head);
        head = std::move(new_node);
    }
};

#endif
