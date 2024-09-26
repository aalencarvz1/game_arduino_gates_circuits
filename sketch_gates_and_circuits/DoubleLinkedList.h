#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <MemoryUsage.h>  // Inclui a biblioteca MemoryUsage
#include <Arduino.h>

template <typename T>
struct Node {
    T* data = nullptr;        // Ponteiro para o objeto do tipo T
    Node<T>* next = nullptr;  // Ponteiro para o próximo nó
    Node<T>* prev = nullptr;  // Ponteiro para o nó anterior
    Node() {
      Serial.println(F("INIT Node<T>::Node"));
      data = nullptr;
      next = nullptr;
      prev = nullptr;
      Serial.println(F("END Node<T>::Node"));
    };
    ~Node(){
      Serial.println(F("INIT Node<T>::~Node"));      
      if (next != nullptr) {
        next->prev = prev;
      }
      if (prev != nullptr) {
        prev->next = next;
      }
      if (data != nullptr) {
        delete data;  // Chama o destrutor do objeto armazenado
      }
      Serial.println(F("END Node<T>::~Node"));
    }
};

template <typename T>
class DoubleLinkedList {
  public:
    Node<T>* head;
    Node<T>* tail;
    const char* tName;
    DoubleLinkedList(const char* typeName) : 
      tName(typeName),
      head(nullptr), 
      tail(nullptr) 
    {
      Serial.println(F("INIT DoubleLinkedList<T>::DoubleLinkedList"));
      Serial.println(F("END DoubleLinkedList<T>::DoubleLinkedList"));
    }

    ~DoubleLinkedList() {
      Serial.println(F("INIT DoubleLinkedList<T>::~DoubleLinkedList"));
      clear();  // Remove todos os nós e libera memória
      Serial.println(F("END DoubleLinkedList<T>::~DoubleLinkedList"));
    }

    void add(T* data) {
      Serial.println(F("INIT DoubleLinkedList<T>::add"));
      Serial.println(tName);
      FREERAM_PRINT; 
      Serial.println(F("antes"));
      Node<T>* newNode = new Node<T>();
      Serial.println(F("depois"));
      FREERAM_PRINT;
      newNode->data = data;      
      newNode->next = nullptr;
      newNode->prev = tail;

      if (newNode->prev != nullptr) {
          newNode->prev->next = newNode;
      }
      tail = newNode;
  
      if (head == nullptr) {
          head = newNode;
      }
      Serial.println(F("END DoubleLinkedList<T>::add"));
    }

    void remove(T* data, bool deleteData = true) {
      Serial.println(F("INIT DoubleLinkedList<T>::remove"));
      Serial.println(tName);
      Node<T>* current = head;

      while (current != nullptr) {
          if (current->data == data) {
              if (current->prev == nullptr) {
                  head = current->next;
              }
              if (current->next == nullptr) {
                  tail = current->prev;
              }
              if (!deleteData) current->data = nullptr; //avoid data delete on node destructor
              delete current;        // Libera o nó
              if (current == tail) {
                tail = nullptr;
              } 
              if (current == head) {
                head = nullptr;
              }
              break;
          }
          current = current->next;
      }
      Serial.println(F("END DoubleLinkedList<T>::remove"));
    }

    void clear() {
      Serial.println(F("INIT DoubleLinkedList<T>::clear"));
      Serial.println(tName);
      Node<T>* current = head;

      while (current != nullptr) {
          Node<T>* nextNode = current->next;
          delete current;        // Libera o nó
          current = nextNode;          
      }
      head = nullptr;
      tail = nullptr;
      Serial.println(F("END DoubleLinkedList<T>::clear"));
    }    
};

#endif
