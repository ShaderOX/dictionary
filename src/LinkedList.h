#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__


template <typename T>
class LinkedList {
  struct LinkedListNode;
public:
  void Insert(T value) {
    LinkedListNode *newNode = new LinkedListNode(value, nullptr);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    }
    else {
      tail->next = newNode;
      tail = newNode;
    }
    length++;
  }

  void PrintList() {
    std::cout << "[ ";
    for (auto curr = head;curr != nullptr; curr = curr->next) {
      std::cout << curr->value << ", ";
    }
    std::cout << "]" << std::endl;
  }

  T *ToArray() {
    T *array = new T[length];
    LinkedListNode *curr = head;
    for (size_t i = 0; i < length; i++) {
      array[i] = curr->value;
      curr = curr->next;
    }
    return array;
  }

  size_t GetLength() {
    return length;
  }

  ~LinkedList() {
    LinkedListNode *curr = head;
    LinkedListNode *tmp;
    while (curr != nullptr) {
      tmp = curr->next;
      delete curr;
      curr = tmp;
    }
  }

private:
  struct LinkedListNode {
    T value;
    LinkedListNode *next;

    LinkedListNode(T value, LinkedListNode *next = nullptr) {
      this->value = value;
      this->next = next;
    }
  };

  LinkedListNode *head = nullptr;
  LinkedListNode *tail = nullptr;
  size_t length = 0;


};


#endif
