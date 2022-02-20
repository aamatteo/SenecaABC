#ifndef GL2DOBJECT_HXX
#define GL2DOBJECT_HXX

#include <GL/glut.h>
#include <map>
#include <string>
/**
	@author  <j.ellerbroek@tudelft.nl>
*/

// Wrap angle to within [0 360] deg, and round (2 digits)
#ifndef WRAP
#define WRAP(angle) (int(round(angle*100)) % 36000) / 100.0 + (angle < 0.0f ? 360.0f : 0.0f)
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef DEG2RAD
#define DEG2RAD 1.7453291e-2
#endif

#ifndef KTS2MPS
#define KTS2MPS 0.5144444
#endif

#ifndef FT2M
#define FT2M 0.3048
#endif
using namespace std;

class gl2DObject
{
  public:
    enum angle_type {DEGREES, RADIANS};
  protected:
    enum align_type {LEFT=1, HCENTER=2, RIGHT=4, TOP=8, VCENTER=16, CENTER=18, BOTTOM=32}; // CENTER = HCENTER|VCENTER
    
  public: // Constructor, destructor
    gl2DObject(const string& name, float x = 0.0f, float y = 0.0f, float phi = 0.0f, float sx = 1.0f, float sy = 1.0f, bool visible = true);
  
    virtual ~gl2DObject();
  
  protected: // Overloadable functions
    virtual void draw();
    virtual void init();
    
  public: // Inherited public functions
    void          visible(bool vis);
    bool          visible();
    void          setOrientation(float x, float y, float phi);
    void          setScale(float sx, float sy);

    void          display();
    void          setup();

    gl2DObject*   getChild(const string& name);
    void          addChild(gl2DObject* obj);
    const string& name();
    
  protected: // Inherited protected functions
    float strokeString(const char *string, float x = 0.0f, float y = 0.0f, float size = 1.0f, void *font = GLUT_STROKE_ROMAN, int align = 0);
    float strokeStringWidth(const char *string, void *font);
    
    /*! \brief Create a wireframe two-dimensional box
     *
     * Draws a box of width 'w', and height 'h',
     * with the lower-left corner at (x,y) */
    void wireBox(float x, float y, float w, float h, int align = 0);
    
    void circle(float x = 0.0f, float y = 0.0f, float radius = 1.0f, bool fill = false, int segments = 72);
    void pie(float x = 0.0f, float y = 0.0f, float radius = 1.0f, float arc_begin = 0.0f, float arc_end = 180.0f, bool fill = false, int segments = 10);
    
    /*! \brief Create a clipping area
     *
     * Makes a two-dimensional clipping box for 2D GL graphics.
     * outside of this box, items are not drawn.
     * Call this method ONLY from within a PushMatrix method! */
    void selectClippingArea(float x, float y, float w, float h);
    
    /// Deselect a previously created clipping area
    void deselectClippingArea();
  
  protected: // member variables
    float _x, _y, _phi, _sx, _sy;
    bool  _draw;
    
    // Default colors
    static float Red[3];
    static float Green[3];
    static float Blue[3];
    static float White[3];
    static float Black[3];
    static float Yellow[3];
    static float Cyan[3];
    static float Amber[3];
    static float Magenta[3];
    static float Grey[3];
    static float Brown[3];
    static float LightBlue[3];
    
  private:
    map<string, gl2DObject*> _children;
    string                   _name;
};

#endif
