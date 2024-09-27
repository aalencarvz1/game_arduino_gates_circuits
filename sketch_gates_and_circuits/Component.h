#ifndef COMPONENT_H
#define COMPONENT_H

#include "DoubleLinkedList.h"

class Component{
  protected:
    Component* parent = nullptr;
    DoubleLinkedList<Component>* children = nullptr;    
  public:
    Component() {};
    Component(const Component* pParent);
    virtual ~Component();    
    virtual void addChildren(const Component* pComponent);
};

#endif //COMPONENT_H