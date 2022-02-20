#include "gl2dobject.hxx"
#include <cmath>

// Font size as defined by GLUT is 152.381, this is incorrect by a factor of 0.65
// FNT_NORMALIZE scales fonts to a height of 1
#define FNT_NORMALIZE 0.0101


float gl2DObject::Red[]       = { 0.85f, 0.0f , 0.0f };
float gl2DObject::Green[]     = { 0.0f , 0.85f, 0.0f };
float gl2DObject::Blue[]      = { 0.0f , 0.0f , 0.85f};
float gl2DObject::White[]     = { 1.0f , 1.0f , 1.0f };
float gl2DObject::Black[]     = { 0.0f , 0.0f , 0.0f };
float gl2DObject::Yellow[]    = { 1.0f , 1.0f , 0.0f };
float gl2DObject::Cyan[]      = { 0.0f , 1.0f , 1.0f };
float gl2DObject::Amber[]     = { 1.0f , 0.5f , 0.0f };
float gl2DObject::Magenta[]   = { 0.95f, 0.0f , 0.95f};
float gl2DObject::Grey[]      = { 0.4f , 0.4f , 0.4f };
float gl2DObject::Brown[]     = { 0.62f, 0.44f, 0.17f};
float gl2DObject::LightBlue[] = { 0.15f, 0.15f, 0.85f};
// frame 0.5625f, 0.47265f, 0.37109f
gl2DObject::gl2DObject(const string& name, float x, float y, float phi, float sx, float sy, bool visible):
  _x(x), _y(y), _phi(phi), _sx(sx), _sy(sy), _draw(visible), _name(name)
{
}

gl2DObject::~gl2DObject()
{
}

void gl2DObject::visible(bool vis)
{
  _draw = vis;
}

bool gl2DObject::visible()
{
  return _draw;
}

void gl2DObject::setOrientation(float x, float y, float phi)
{
  _x    = x;
  _y    = y;
  _phi  = phi;
}

void gl2DObject::setScale(float sx, float sy)
{
  _sx = sx;
  _sy = sy;
}

void gl2DObject::draw()
{
}

void gl2DObject::init()
{
}

void gl2DObject::display()
{
  if (_draw)
  {
    glPushMatrix();
    glScalef(_sx, _sy, 1.0);
    glTranslatef(_x, _y, 0.0);
    glRotatef(_phi, 0.0f, 0.0f, 1.0f);
    draw();
    glPopMatrix();
    if (!_children.empty())
      for (map<string, gl2DObject*>::iterator i = _children.begin(); i != _children.end(); ++i)
        (i->second)->display();
  }
}

void gl2DObject::setup()
{
  init();
  if (!_children.empty())
    for (map<string, gl2DObject*>::iterator i = _children.begin(); i != _children.end(); ++i)
      (i->second)->setup();
}

gl2DObject* gl2DObject::getChild(const string &name)
{
  return _children[name];
}

void gl2DObject::addChild(gl2DObject* item)
{
  if (!_children[item->name()])
    _children[item->name()] = item;
}

const string& gl2DObject::name()
{
  return _name;
}

float gl2DObject::strokeStringWidth(const char *string, void *font)
{
  int length = 0;
  int currentlength = 0;
  while (*string) 
  {
    if (*string == '\n')
    {
      if (length < currentlength)
        length = currentlength;
      currentlength = 0;
    } else {
      currentlength += glutStrokeWidth(font, *string);
    }
    ++string;
  }
  if (length < currentlength)
    length = currentlength;
  
  return FNT_NORMALIZE * float(length);
}

float gl2DObject::strokeString(const char *string, float x, float y, float size, void *font, int t)
{
  float w = size * strokeStringWidth(string, font);
  float h = size;
  
  glPushMatrix();
  glTranslatef((t&HCENTER ? x - 0.5 * w : (t&RIGHT ? x - w : x)), /* Center, right or left  (default) alignment */
               (t&VCENTER ? y - 0.5 * h : (t&TOP   ? y - h : y)), /* Center, top, or bottom (default) alignment */
               0.0f);
  
  glScalef(size * FNT_NORMALIZE, size * FNT_NORMALIZE, 1.0f);
  while (*string) 
  {
    glutStrokeCharacter(font, *string);
    ++string;
  }
  glPopMatrix();
  return w;
}

void gl2DObject::wireBox(float x, float y, float w, float h, int t)
{
  glPushMatrix();
  glTranslatef((t&HCENTER ? x - 0.5 * w : (t&RIGHT ? x - w : x)), /* Center, right or left  (default) alignment */
               (t&VCENTER ? y - 0.5 * h : (t&TOP   ? y - h : y)), /* Center, top, or bottom (default) alignment */
               0.0f);
  
  glBegin(GL_LINE_LOOP);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(0.0f, h);
  glVertex2f(w,    h);
  glVertex2f(w,    0.0f);
  glEnd();
  
  glPopMatrix();
}

void gl2DObject::selectClippingArea(float x, float y, float w, float h)
{
  double clip_top[4]     = { 0.0, -1.0, 0.0, 0.5*h + y};
  double clip_left[4]    = { 1.0,  0.0, 0.0, 0.5*w - x};
  double clip_right[4]   = {-1.0,  0.0, 0.0, 0.5*w + x};
  double clip_bottom[4]  = { 0.0,  1.0, 0.0, 0.5*h - y};
  glClipPlane(GL_CLIP_PLANE0, clip_top);
  glEnable(GL_CLIP_PLANE0);
  glClipPlane(GL_CLIP_PLANE1, clip_left);
  glEnable(GL_CLIP_PLANE1);
  glClipPlane(GL_CLIP_PLANE2, clip_right);
  glEnable(GL_CLIP_PLANE2);
  glClipPlane(GL_CLIP_PLANE3, clip_bottom);
  glEnable(GL_CLIP_PLANE3);
}

void gl2DObject::deselectClippingArea()
{
  glDisable(GL_CLIP_PLANE0);
  glDisable(GL_CLIP_PLANE1);
  glDisable(GL_CLIP_PLANE2);
  glDisable(GL_CLIP_PLANE3);
}

void gl2DObject::circle(float x, float y, float radius, bool fill, int segments)
{

  if (fill)
    glBegin(GL_POLYGON);
  else
    glBegin(GL_LINE_LOOP);
  for (int i = 0; i < segments ; ++i)
  {
    float angle = float(i) / float(segments) * 2.0f*M_PI;
    glVertex2f(x + radius * cos(angle),
               y + radius * sin(angle));
  }
  glEnd();
}

void gl2DObject::pie(float x, float y, float radius, float arc_begin, float arc_end, bool fill, int segments)
{
  if (fill)
    glBegin(GL_POLYGON);
  else
    glBegin(GL_LINE_LOOP);
  glVertex2f(x, y);
  for (int i = 0; i < segments ; ++i)
  {
    float angle = (arc_begin + float(i) / float(segments) * arc_end)/180.0f * M_PI;
    glVertex2f(x + radius * cos(angle),
               y + radius * sin(angle));
  }
  glEnd();
}
