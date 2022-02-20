//************************************************************
// GLTools.hxx
//
// Created on Thu May  3 09:18:37 2012 by Jan Comans
//
// Copyright 2012 Jan Comans -- j.comans@tudelft.nl
//
// License TBD
//************************************************************

#ifndef _GLTOOLS_H_
#define _GLTOOLS_H_

#include <GL/gl.h>
#include <cmath>
#include <vector>

#include <boost/foreach.hpp>

#include <Eigen/Eigen>

// Automatic push and pop
class GLSaveMatrix
{
public:
  GLSaveMatrix() { glPushMatrix(); }
  ~GLSaveMatrix(){ glPopMatrix();  }
};

class GLBlend
{
public:
  GLBlend()
  {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
  }

  ~GLBlend()
  {
    glDisable(GL_BLEND);
  }
};

// Automatic line smooth enable/disable
class GLLineSmooth
{
public:
  GLLineSmooth()  { glEnable(GL_LINE_SMOOTH);}
  ~GLLineSmooth() { glDisable(GL_LINE_SMOOTH);}

private:
  GLBlend enable_blend;
};


// Automatic polygon smooth enable/disable
class GLPolygonSmooth
{
public:
  GLPolygonSmooth() { glEnable(GL_POLYGON_SMOOTH); glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);}
  ~GLPolygonSmooth(){ glDisable(GL_POLYGON_SMOOTH);}

private:
  GLBlend enable_blend;
};

// Automatic line width set/reset
class GLLineWidth
{
public:
  GLLineWidth(GLfloat width):
    _old_width(1.0f)
  {
    glGetFloatv(GL_LINE_WIDTH,&_old_width);
    glLineWidth(width*scale_factor);
  }

  ~GLLineWidth() { glLineWidth(_old_width); }

  static GLfloat scale_factor;

private:
  GLfloat _old_width;
};

class GLBegin
{
public:
  GLBegin(int mode) { glBegin(mode); }
  ~GLBegin()        { glEnd();       }
};

class GLClipRectangle
{
public:
  GLClipRectangle(float x, float y, float w, float h)
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

  ~GLClipRectangle()
  {
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    glDisable(GL_CLIP_PLANE2);
    glDisable(GL_CLIP_PLANE3);
  }
};

class GLStencilMask
  {
  public:
    GLStencilMask(bool debug=false):_debug(debug)
    {
      if(!_debug)
      {
        // Enable the stencil buffer and clear it to 0
        glClearStencil(0);
        glEnable(GL_STENCIL_TEST);
        glClear(GL_STENCIL_BUFFER_BIT);
        // Disable drawing to the color and depth buffer
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glGetBooleanv(GL_DEPTH_WRITEMASK,&_previous_depth_mask);
        glDepthMask(GL_FALSE);
        // Always pass stencil test and set stencil bit for drawn area
        glStencilFunc(GL_ALWAYS, 0x01, 0x01);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
      }
    }

    void finish()
    {
      if(!_debug)
      {
        // Enable drawing to the color and depth buffer again
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(_previous_depth_mask);

        // Stencil buffer is 1 for in the bottom part, only draw when bits are 0
        glStencilFunc(GL_EQUAL, 0x1, 0x1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
      }
    }

    ~GLStencilMask()
    {
      if(!_debug)
      {
        // Disable stencils
        glClear(GL_STENCIL_BUFFER_BIT);
        glDisable(GL_STENCIL_TEST);
      }
    }

  private:
    bool _debug;
    GLboolean _previous_depth_mask;
  };


class GLRectangle
{
public:
  GLRectangle(float bottom, float top, float left, float right):
    _bottom(bottom), _top(top), _left(left), _right(right) {}

  void drawPoints()  const { GLBegin points(GL_POINTS);      insert_vertices(); }
  void drawOutline() const { GLBegin lineloop(GL_LINE_LOOP); insert_vertices(); }
  void drawFill()    const { GLBegin quad(GL_QUADS);         insert_vertices(); }

private:
  float _bottom, _top, _left, _right;

  void insert_vertices() const
  {
    glVertex2f( _left  , _bottom );
    glVertex2f( _left  , _top    );
    glVertex2f( _right , _top    );
    glVertex2f( _right , _bottom );
  }
};

class GLQuad
{
public:
  GLQuad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3):
    _x0(x0),_y0(y0),_x1(x1),_y1(y1),_x2(x2),_y2(y2),_x3(x3),_y3(y3) {}

  GLQuad(const Eigen::Vector2d& first,
	 const Eigen::Vector2d& second,
	 const Eigen::Vector2d& third,
	 const Eigen::Vector2d& fourth):
    _x0(first[0]), _y0(first[1]),
    _x1(second[0]), _y1(second[1]),
    _x2(third[0]), _y2(third[1]),
    _x3(fourth[0]), _y3(fourth[1]){}
  
  void drawPoints()  const { GLBegin points(GL_POINTS);      insert_vertices(); }
  void drawOutline() const { GLBegin lineloop(GL_LINE_LOOP); insert_vertices(); }
  void drawFill()    const { GLBegin quad(GL_QUADS);         insert_vertices(); }

private:
  float _x0, _y0, _x1, _y1, _x2, _y2, _x3, _y3;
  void insert_vertices() const
  {
    glVertex2f( _x0 , _y0 );
    glVertex2f( _x1 , _y1 );
    glVertex2f( _x2 , _y2 );
    glVertex2f( _x3 , _y3 );
  }
};

class GLTriangle
{
public:
  GLTriangle(float x0, float y0, float x1, float y1, float x2, float y2):
    _x0(x0),_y0(y0),_x1(x1),_y1(y1),_x2(x2),_y2(y2){}

  GLTriangle(const Eigen::Vector2d& first,
	     const Eigen::Vector2d& second,
	     const Eigen::Vector2d& third):
    _x0(first[0]), _y0(first[1]),
    _x1(second[0]), _y1(second[1]),
    _x2(third[0]), _y2(third[1]){}
  

  void drawPoints()  const { GLBegin points(GL_POINTS);      insert_vertices(); }
  void drawOutline() const { GLBegin lineloop(GL_LINE_LOOP); insert_vertices(); }
  void drawFill()    const{ GLBegin quad(GL_TRIANGLES);     insert_vertices(); }
    
private:
  float _x0,_y0,_x1,_y1,_x2,_y2;

  void insert_vertices() const
  {
    glVertex2f( _x0 , _y0 );
    glVertex2f( _x1 , _y1 );
    glVertex2f( _x2 , _y2 );
  }
};

class GLLine
{
public:
  GLLine(float x0, float y0, float x1, float y1):
    _x0(x0), _y0(y0), _x1(x1), _y1(y1) {}

  void drawPoints()  const { GLBegin points( GL_POINTS ); insert_vertices(); }
  void drawOutline() const { GLBegin lines(  GL_LINES  ); insert_vertices(); }
  void drawFill()    const { drawOutline(); }

private:
  float _x0,_y0,_x1,_y1;

  void insert_vertices() const
  {
    glVertex2f( _x0, _y0 );
    glVertex2f( _x1, _y1 );
  }
};

class GLCircle
{
public:
  GLCircle(float x, float y, float radius, float start_angle, float stop_angle, size_t n_steps):
    center_(std::make_pair(x,y))
  {
    const float increment = (stop_angle - start_angle) / static_cast<float>(n_steps);
    for(size_t step=0; step<=n_steps; ++step)
    {
      const float angle = start_angle + static_cast<float>(step) * increment;
      points_.push_back(std::make_pair( x + radius*sin(angle) , y + radius*cos(angle) ));
    }
  }

  void drawPoints()  const { GLBegin points(GL_POINTS);       insert_vertices(); }
  void drawOutline() const { GLBegin lines(GL_LINES);         insert_vertices(); }
  void drawFill()    const { GLBegin circle(GL_TRIANGLE_FAN); insert_center(); insert_vertices(); }
  
private:
  typedef std::pair<float,float> Point;

  Point              center_;
  std::vector<Point> points_;

  void insert_center() const
  {
    glVertex2f( center_.first, center_.second );
  }
  
  void insert_vertices() const
  {
    BOOST_FOREACH(const Point& point, points_)
      glVertex2f( point.first, point.second );      
  }  
};
  

// Circle drawing
inline void circlePoints(float radius, float start_angle, float stop_angle, size_t n_steps)
{
  const float increment = (stop_angle - start_angle) / static_cast<float>(n_steps);
  for(size_t step=0; step<=n_steps; ++step)
  {
    const float angle = start_angle + static_cast<float>(step) * increment;
    glVertex2f( radius*sin(angle) , radius*cos(angle) );
  }
}

inline float clipValue(float value, float min, float max)
{
  if( value > max ) return max;
  if( value < min ) return min;
  return value;
}




#endif /* _GLTOOLS_H_ */


