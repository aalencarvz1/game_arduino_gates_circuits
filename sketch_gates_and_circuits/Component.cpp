#include "Component.h"

Component::Component(const Component* pParent) : 
  parent(pParent) 
{
  if (pParent != nullptr) {
    parent = pParent;
    parent->addChildren(this);
  }
};

Component::~Component() {
  //Serial.println(F("INIT Component::~Component"));
  if (children != nullptr) {
    delete children;
    children = nullptr;
  }
  //Serial.println(F("END Component::~Component"));
};

void Component::addChildren(const Component* pComponent) {
  //Serial.println(F("INIT Component::addChildren"));
  if (children == nullptr) {
    children = new DoubleLinkedList<Component>("Component");
  }
  children->add(pComponent);
  //Serial.println(F("END Component::addChildren"));
}



