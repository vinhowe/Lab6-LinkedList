#pragma once
#include <sstream>
#include <stdexcept>
#include <string>

#include "LinkedListInterface.h"

using namespace std;

template <typename T>
class LinkedList : public LinkedListInterface<T> {
 public:
  LinkedList() = default;
  virtual ~LinkedList() { clear(); };

  struct Node {
    explicit Node(T data) : data(data){};
    T data;
    Node* next = nullptr;
  };

  /*
  insertHead

  A node with the given value should be inserted at the beginning of the list.

  Do not allow duplicate values in the list.
  */
  void insertHead(T value) override {
    if (find(value)) {
      return;
    }

    Node* newNode = new Node(value);
    // TODO: Check for duplicates
    if (!head) {
      head = newNode;
      return;
    }

    newNode->next = head;
    head = newNode;
  }

  /*
  insertTail

  A node with the given value should be inserted at the end of the list.

  Do not allow duplicate values in the list.
  */
  void insertTail(T value) override {
    if (find(value)) {
      return;
    }

    if (!head) {
      insertHead(value);
      return;
    }

    Node* newNode = new Node(value);
    // TODO: Check for duplicates

    Node* ptr = head;
    while (ptr->next != nullptr) {
      ptr = ptr->next;
    }
    ptr->next = newNode;
  }

  /*
  insertAfter

  A node with the given value should be inserted immediately after the
  node whose value is equal to insertionNode.

  A node should only be added if the node whose value is equal to
  insertionNode is in the list. Do not allow duplicate values in the list.
  */
  void insertAfter(T value, T insertionNode) override {
    if (!head || find(value)) {
      // Either there are no nodes or a node already exists with the value we
      // want
      return;
    }


    Node* ptr = head;
    while (ptr->data != insertionNode) {
      ptr = ptr->next;
      if (ptr == nullptr) {
        return;
      }
    }

    Node* newNode = new Node(value);

    newNode->next = ptr->next;
    ptr->next = newNode;
  }

  /*
  remove

  The node with the given value should be removed from the list.

  The list may or may not include a node with the given value.
  */
  void remove(T value) override {
    if (!head || !find(value)) {
      return;
    }

    if (head->data == value) {
      Node* tempHead = head;
      head = head->next;
      delete tempHead;
      return;
    }

    Node* ptr = head;
    while (ptr->next != nullptr) {
      if (ptr->next->data == value) {
        break;
      }
      ptr = ptr->next;
    }

    Node* removePtr = ptr->next;
    ptr->next = removePtr->next;

    delete removePtr;
  }

  /*
  clear

  Remove all nodes from the list.
  */
  void clear() override {
    while (head != nullptr) {
      remove(head->data);
    }
  }

  /*
  at

  Returns the value of the node at the given index. The list begins at
  index 0.

  If the given index is out of range of the list, throw an out of range
  exception.
  */
  T at(int index) override {
    int i = 0;
    Node* ptr = head;
    while (ptr != nullptr) {
      if (i == index) {
        return ptr->data;
      }
      ptr = ptr->next;
      i++;
    }
    throw out_of_range(to_string(index) + " is out of range");
  }

  /*
  size

  Returns the number of nodes in the list.
  */
  int size() override {
    int size = 0;
    Node* ptr = head;
    while (ptr != nullptr) {
      size++;
      ptr = ptr->next;
    }
    return size;
  }

  /*
  toString

  Returns a string representation of the list, with the value of each node
  listed in order (Starting from the head) and separated by a single space There
  should be no trailing space at the end of the string

  For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
  "1 2 3 4 5"
  */
  string toString() override {
    if (!head) {
      return "";
    }
    ostringstream out;
    Node* ptr = head;
    while (ptr != nullptr) {
      out << ptr->data;
      if (ptr->next != nullptr) {
        out << " ";
      }
      ptr = ptr->next;
    }
    return out.str();
  }

 private:
  Node* head;
  bool find(T value) {
    Node* ptr = head;
    while (ptr != nullptr) {
      if (ptr->data == value) {
        return true;
      }
      ptr = ptr->next;
    }
    return false;
  }
};
