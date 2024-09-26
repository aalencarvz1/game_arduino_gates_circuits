#ifndef VISUALCOMPONENT_H
#define VISUALCOMPONENT_H

#include "Component.h"
#include "DoubleLinkedList.h"
#include "TouchScreenController.h"

mover o clique evento para ca, devido a inclusao circular

class VisualComponent : public Component{
  protected:
    double x;
    double y;
    double r;
    double width = 0;
    double height = 0;
    bool isCircular = false;
    char* text = nullptr;
    double roundedRadius = 5;
    int lineColor = TFT_WHITE;
    int backgroundColor = -1;//transparent
    int lineWidth = 1;
    TouchScreenClickEvent* onClick = nullptr;    
  public:    

    //constructors
    using Component::Component;
    VisualComponent(const double& pX,const double& pY) : x(pX), y(pY) {};
    VisualComponent(const double& pX,const double& pY,const double& pR);
    VisualComponent(const double& pX,const double& pY,const double& pWidth,const double& pHeight) : x(pX), y(pY), width(pWidth), height(pHeight) {};
    ~VisualComponent();

    //inline setters
    virtual void setX(const double& pX){x=pX;};
    virtual void setY(const double& pY){y=pY;};
    virtual void setR(const double& pR){r=pR;};   
    virtual void setWidth(const double& pWidth){width=pWidth;};
    virtual void setHeight(const double& pHeight){height=pHeight;};    
    virtual void setText(const char* pText){text=pText;};
    virtual void setRoundedRadius(const double& pRoundedRadius){roundedRadius=pRoundedRadius;};
    virtual void setBackgroundColor(const int& pBackgroundColor){backgroundColor=pBackgroundColor;};
    virtual void setLineColor(const int& pLineColor){lineColor=pLineColor;};
    virtual void setLineWidth(const int& pLineWidth){lineWidth=pLineWidth;};

    //inline getters
    virtual const double getX() const {return x;};
    virtual const double getY() const {return y;};
    virtual const double getR() const {return r;};   
    virtual const double getWidth() const {return width;};
    virtual const double getHeight() const {return height;};
    virtual const char* getText() const {return text;};
    virtual const double getRoundedRadius() const {return roundedRadius;};
    virtual const int getBackgroundColor() const {return backgroundColor;};
    virtual const int getLineColor() const {return lineColor;};
    virtual const int getLineWidth() const {return lineWidth;};

    //bare setters
    virtual void setOnClick(const void (*&staticOnClick)());
    /*virtual void setOnClick(const ICallback*& onClickCallback = nullptr);*/


    virtual void removeOnClick();
    
    virtual void draw();
};

#endif //VISUALCOMPONENT_H