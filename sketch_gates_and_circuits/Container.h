#ifndef CONTAINER_H
#define CONTAINER_H

#include "VisualComponent.h"

class Container : public VisualComponent{
  public:
    using VisualComponent::VisualComponent;
    void draw() override;
};

#endif //CONTAINER_H