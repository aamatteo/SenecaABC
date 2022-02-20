// MCPElement.hxx
//
// base class for screen elements that can be clicked and/or drawn
//
// Olaf Stroosma
// 2%5 JUN 2004

#ifndef MCPElement_hxx
#define MCPElement_hxx

/** base class for screen elements that can be clicked and/or drawn */
class MCPElement  
{
public:
  /** default constructor */
  MCPElement();
  
  /** constructor with non-zero screen area */
  MCPElement(float xl, float xu, float yl, float yu );
  
  /** destructor */
  virtual ~MCPElement();
  
  /** check if click is within screen area */
  virtual bool checkClick(float x, float y, int button);
  
  /** draw the element */
  virtual void draw();

  /** set the value of the element, probably in response to a hardware event */
  virtual void setValue(double d);

  /** enable or disable the element */
  inline void enable(bool b){enabled = b;};
  inline bool isEnabled(){return enabled;};

protected:
  /** screen area for click detection */
  float xmin, xmax, ymin,  ymax;

  /** enabled switch */
  bool enabled;
};

#endif
