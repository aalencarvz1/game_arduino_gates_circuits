#ifndef VISUALCOMPONENT_H
#define VISUALCOMPONENT_H

#include "Component.h"
#include "DoubleLinkedList.h"
#include "TouchScreenController.h"

//#include "ClickEvent.h"
class ClickEvent; //forward declaration to avoid circular dependency
class Border; //forward declaration;

class VisualComponent : public Component{
  protected:
    double x;
    double y;
    double r;
    double width = 0;
    double height = 0;    
    double roundedRadius = 5;
    double margin = 0;    
    double padding = 0;    
    int backgroundColor = -1;//-1  = none
    char* text = nullptr;
    bool circular = false;    
    Border* border = nullptr;
    ClickEvent* onClick = nullptr;    
  public:    

    //constructors
    using Component::Component;
    VisualComponent(const Component* pParent, const double& pX,const double& pY) : Component(pParent), x(pX), y(pY) {};
    VisualComponent(const Component* pParent, const double& pX,const double& pY,const double& pR);
    VisualComponent(const Component* pParent, const double& pX,const double& pY,const double& pWidth,const double& pHeight) : Component(pParent), x(pX), y(pY), width(pWidth), height(pHeight) {};
    virtual ~VisualComponent();

    //inline setters
    virtual void setX(const double& pX){x=pX;};
    virtual void setY(const double& pY){y=pY;};
    virtual void setR(const double& pR){r=pR;};   
    virtual void setWidth(const double& pWidth){width=pWidth;};
    virtual void setHeight(const double& pHeight){height=pHeight;};    
    virtual void setRoundedRadius(const double& pRoundedRadius);
    virtual void setMargin(const double& pMargin){margin=pMargin;};
    virtual void setPadding(const double& pPadding){padding=pPadding;};
    virtual void setBackgroundColor(const int& pBackgroundColor){backgroundColor=pBackgroundColor;};
    virtual void setBorder(const Border* pBorder);
    virtual void setText(const char* pText){text=pText;};
    
  
    //inline getters
    virtual const double getX() const {return x;};
    virtual const double getY() const {return y;};
    virtual const double getR() const {return r;};   
    virtual const double getWidth() const {return width;};
    virtual const double getHeight() const {return height;};    
    virtual const double getRoundedRadius() const {return roundedRadius;};    
    virtual const double getMargin() const {return margin;};
    virtual const double getPadding() const {return padding;};
    virtual const int getBackgroundColor() const {return backgroundColor;};
    virtual const Border* getBorder() const {return border;};
    virtual const char* getText() const {return text;};
    virtual const bool isCircular() const {return circular;};

    //bare setters
    virtual void setOnClick(const void (*staticOnClick)());
    virtual void setOnClick(const ICallback* onClickCallback);


    virtual void removeOnClick();
    virtual void createBorder(const double& borderWidth = 1, const int& borderColor = TFT_WHITE);
    
    virtual void draw();
};

class Border : public VisualComponent{
  protected:
    int borderWidth = 1;
    int color = TFT_DARKGREY;
  public:
    using VisualComponent::VisualComponent;
    virtual void setBorderWidth(const int& pBorderWidth){borderWidth=pBorderWidth;};
    virtual void setColor(const int& pColor){color=pColor;};    

    virtual const int getBorderWidth() const {return borderWidth;};
    virtual const int getColor() const {return color;};
    virtual void draw() override;
};

#endif //VISUALCOMPONENT_H