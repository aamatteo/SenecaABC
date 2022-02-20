//************************************************************
// HMITools.hxx
//
// Created on Tue May 15 17:04:08 2012 by Jan Comans
//
// Copyright 2012 Jan Comans -- j.comans@tudelft.nl
//
// License TBD
//************************************************************
#ifndef _HMITOOLS_H_
#define _HMITOOLS_H_

#include <hmi.hxx>

#include <cmath>
#include <iomanip>
#include <list>
#include <sstream>
#include <vector>

#include <boost/foreach.hpp>

#include "ColorMap.hpp"
#include "GLTools.hxx"

class HMIText
{
public:
  HMIText(hmi::Font* font):
    _font(font),_xpos(0),_ypos(0), _xpadding(0), _ypadding(0),  _alignment(0) {}

  HMIText& size(double val) { _font->SetSize(val,val); return *this;}
  HMIText& position(double x, double y) {_xpos=x; _ypos=y; return *this;}
  HMIText& padding(double x, double y) {_xpadding=x;  _ypadding=y; return *this;}

  HMIText& vcenter() { _alignment |= hmi::Font::VCENTER; return *this;}
  HMIText& left()    { _alignment |= hmi::Font::LEFT;    return *this;}
  HMIText& right()   { _alignment |= hmi::Font::RIGHT;   return *this;}

  HMIText& hcenter() { _alignment |= hmi::Font::HCENTER; return *this;}
  HMIText& top()     { _alignment |= hmi::Font::TOP;     return *this;}
  HMIText& bottom()  { _alignment |= hmi::Font::BOTTOM;  return *this;}

  HMIText& smooth(bool flag=true) { _font->SetSmooth(flag); return *this;}

  hmi::BoundingBox draw() { return _font->Print(_xpos+_xpadding,_ypos+_ypadding,_text.str(),_alignment); }

  HMIText& clear()   { _xpos=0; _ypos=0; _xpadding=0; _ypadding=0; _alignment=0; cleartext(); return *this;}
  HMIText& cleartext() { _text.str(""); return *this;}

   template<class T>
   HMIText& operator<<(const T& val) { _text << val; return *this; }
  
private:
  hmi::Font* _font;

  double _xpos, _ypos;
  double _xpadding, _ypadding;
  int    _alignment;
  std::stringstream _text;
};

template <class LabelPolicy>
class VerticalTape
{
public:
  enum alignment { right, left };

public:
  VerticalTape(
    float      box_width,
    float      box_height,
    alignment tape_alignment,
    float      large_tick_resolution,
    float      small_tick_resolution,
    float      pixel_resolution,
    float      large_tick_width,
    float      small_tick_width
    ):    
    _box_width(             box_width ),
    _box_height(            box_height ),
    _tape_alignment(       tape_alignment ),
    _large_tick_resolution( large_tick_resolution ),
    _small_tick_resolution( small_tick_resolution ),
    _pixel_resolution(      pixel_resolution ),
    _large_tick_width(      large_tick_width ),
    _small_tick_width(      small_tick_width )
  {
  }

public:
  void render() const { render(0.0f); }

  void render( float value ) const
  {
    GLLineSmooth line_smooth;
    
    const int n_large_ticks =
      static_cast<int>( ceil( _box_height / ( _large_tick_resolution * _pixel_resolution ) ) );

    const int n_small_ticks =
      static_cast<int>( ceil( _box_height / ( _small_tick_resolution * _pixel_resolution ) ) );

    const float base_tick_offset = fmod(value , _large_tick_resolution);
    const float base_tick_value = value - base_tick_offset;

    const float gl_y_shift = -base_tick_offset * _pixel_resolution;

    GLSaveMatrix current_matrix_state;

    GLClipRectangle clip(_box_width/2.0f,0.0f, _box_width, _box_height);

    glTranslatef( 0.0f , gl_y_shift , 0.0f );

    // Draw the small ticks
    {
      const float x_left  = (_tape_alignment == left) ? 0.0f : _box_width-_small_tick_width;
      const float x_right = (_tape_alignment == left) ? _small_tick_width : _box_width;

      for(int tick_index=-n_small_ticks; tick_index<n_small_ticks; ++tick_index)
      {
	const float y_pos =
	  static_cast<float>(tick_index) * _small_tick_resolution * _pixel_resolution;
	
	{
	  GLBegin lines(GL_LINES);
	  glVertex2f( x_left  , y_pos );
	  glVertex2f( x_right , y_pos );
	}

      }
    }

    // Draw the large ticks
    {
      const float x_left  = (_tape_alignment == left) ? 0.0f : _box_width-_large_tick_width;
      const float x_right = (_tape_alignment == left) ? _large_tick_width : _box_width;

      for(int tick_index=-n_large_ticks; tick_index<n_large_ticks; ++tick_index)
      {
	const float y_pos =
	  static_cast<float>(tick_index) * _large_tick_resolution * _pixel_resolution;
	const float label_value =
	  base_tick_value + static_cast<float>(tick_index) * _large_tick_resolution;
	const float x_label = (_tape_alignment == left) ? x_right : x_left;
	
	{
	  GLBegin lines(GL_LINES);
	  glVertex2f( x_left  , y_pos );
	  glVertex2f( x_right , y_pos );
	}

	LabelPolicy::print_label(label_value, x_label,y_pos);
      }
    }
  }
  

private:
  float      _box_width;
  float      _box_height;
  alignment  _tape_alignment;
  float      _large_tick_resolution;
  float      _small_tick_resolution;
  float      _pixel_resolution;
  float      _large_tick_width;
  float      _small_tick_width;
};

class RotaryDigit
{
public:
  RotaryDigit(float label_resolution, float value_resolution,
	      float min_label, float max_label,
	      float stiction,
	      float pixel_spacing,
	      float box_width, float box_height,
	      float x_position, float y_position,
	      float text_size, size_t field_width=2, char fill_char='0'):
    _label_resolution(label_resolution),
    _value_resolution(value_resolution),
    _min_label(min_label),
    _max_label(max_label),
    _stiction(stiction),
    _pixel_spacing(pixel_spacing),
    _box_width(box_width),
    _box_height(box_height),
    _x_position(x_position),
    _y_position(y_position),
    _text_size(text_size),
    _field_width(field_width),
    _fill_char(fill_char)
  {
    for(float label=min_label; label <= max_label ; label+=label_resolution)
      _labels.push_back(label);

    _labels.push_front( max_label );
    _labels.push_front( max_label - label_resolution );

    _labels.push_back( min_label );
    _labels.push_back( min_label + label_resolution );
  }

  
  void render(float value) const
  {
    GLSaveMatrix matrix_state;

    glTranslatef(_x_position,_y_position,0.0f);
    
    GLClipRectangle clip( _box_width/2.0f, 0.0f, _box_width, _box_height );

    // Default translation to account for the padding aplied to the front and back
    glTranslatef( 0.0f , -2.0f * _pixel_spacing, 0.0f );

    // Calculate the base shift
    const float remainder = fmod(value,_value_resolution);
    const float base = value - remainder;
    const float base_shift = base * _pixel_spacing / _value_resolution;
    glTranslatef( 0.0f, -base_shift, 0.0f);

    // If necesary, add some more shift
    if( remainder > _stiction )
    {
      const float shift_zone = _value_resolution - _stiction;
      const float extra_shift  = (remainder-_stiction)*_pixel_spacing/shift_zone;
      glTranslatef( 0.0f, -extra_shift, 0.0f );
    }

    // Draw the labels
    HMIText labeltext(hmi::FontManager::Get(0));
    labeltext.vcenter().left().size(_text_size);

    float ypos = 0.0f;
    BOOST_FOREACH( float label, _labels)
    {
      labeltext.cleartext().position( 0.0f , ypos );
      labeltext << std::setw(_field_width) << std::setfill(_fill_char) << label;
      labeltext.draw();
      ypos += _pixel_spacing;
    }
  }

  
private:
  float _label_resolution;
  float _value_resolution;
  float _min_label;
  float _max_label;
  float _stiction;
  float _pixel_spacing;
  float _box_width;
  float _box_height;
  float _x_position;
  float _y_position;
  float _text_size;
  std::list<float> _labels;
  size_t _field_width;
  char   _fill_char;
};

class LinearIndicator
{
public:
  enum alignment { bottom, middle, top };
  
  // typedef std::pair< hmi::Colour , std::pair< float , float > > ColorRegion;
  struct ColorRegion
  {
    ColorNames                color;
    std::pair< float , float > range;
    bool                       color_indicator;

    ColorRegion( const ColorNames& c, std::pair< float , float > r, bool ci ):
      color(c), range(r), color_indicator(ci)
    {
    }
    
  };
  
  typedef std::vector< ColorRegion > ColorRegions;

public:
  LinearIndicator( float width, alignment hline_alignment, float end_tick_size,
		   size_t n_ticks, float tick_size,
		   const std::string& label="",
		   float x_position = 0.0f, float y_position=0.0f):
    _width( width ),
    _alignment( hline_alignment ),
    _end_tick_size( end_tick_size ),
    _n_ticks( n_ticks ),
    _tick_size( tick_size ),
    _label( label ),
    _x_position( x_position ),
    _y_position( y_position )
  {
  }

  ColorRegions& colorRegions() { return _color_regions; }

  void renderStatic() const
  {
    {
      GLSaveMatrix original_state;
      glTranslatef( _x_position, _y_position, 0.0f );

      hmi::Colour::PaletteColour(cn_foreground);
      GLLineWidth width(1.5f);
      GLLineSmooth smooth;

      if( _alignment == middle )
      {
	const float end_tick_y_top    =  _end_tick_size/2.0f;
	const float end_tick_y_bottom = -_end_tick_size/2.0f;
	// Shift the small ticks a bit to compensate for line thickness
	const float tick_y_top    =  _tick_size/2.0f -1.0f;
	const float tick_y_bottom = -_tick_size/2.0f -1.0f;

	// Draw the horizontal line
	{
	  GLBegin lines(GL_LINES);
	  glVertex2f( -_width/2.0f, 0.0f );
	  glVertex2f(  _width/2.0f, 0.0f );
	}

	// The intermedite ticks (if necesary)
	if( _n_ticks )
	{
	  const float tick_spacing = _width / static_cast<float>( _n_ticks + 1 );
	  for(size_t tick=1; tick <= _n_ticks ; ++tick )
	  {
	    const float tick_x = -_width/2.0f + tick_spacing * static_cast<float>( tick );
	    GLBegin lines(GL_LINES);
	    glVertex2f( tick_x , tick_y_top );
	    glVertex2f( tick_x , tick_y_bottom );
	  }
	}

	// Draw the color regions
	BOOST_FOREACH( ColorRegion color_region, _color_regions)
	{
	  hmi::Colour::PaletteColour(color_region.color);
	  const float start_x = -_width/2.0f + _width * color_region.range.first;
	  const float stop_x  = -_width/2.0f + _width * color_region.range.second;

	  GLBegin quad(GL_QUADS);
	  glVertex2f( start_x , -2.5f );
	  glVertex2f( start_x ,  2.5f );
	  glVertex2f( stop_x  ,  2.5f );
	  glVertex2f( stop_x  , -2.5f );
	
	}

	hmi::Colour::PaletteColour(cn_foreground);
	// The end ticks
	{
	  GLBegin lines(GL_LINES);
	  glVertex2f( -_width/2.0f, end_tick_y_bottom );
	  glVertex2f( -_width/2.0f, end_tick_y_top );
	  glVertex2f(  _width/2.0f, end_tick_y_bottom );
	  glVertex2f(  _width/2.0f, end_tick_y_top );
	}
      }
      else
      {
	const float end_tick_y = _alignment==bottom? _end_tick_size : -_end_tick_size;
	const float tick_y     = _alignment==bottom? _tick_size     : -_tick_size;

	// The intermedite ticks (if necesary)
	if( _n_ticks )
	{
	  const float tick_spacing = _width / static_cast<float>( _n_ticks + 1 );
	  for(size_t tick=1; tick <= _n_ticks ; ++tick )
	  {
	    const float tick_x = -_width/2.0f + tick_spacing * static_cast<float>( tick );
	    GLBegin lines(GL_LINES);
	    glVertex2f( tick_x , 0.0f );
	    glVertex2f( tick_x , tick_y );
	  }
	}

	// Draw the color regions
	BOOST_FOREACH( ColorRegion color_region, _color_regions)
	{
	  hmi::Colour::PaletteColour(color_region.color);
	  const float start_x = -_width/2.0f + _width * color_region.range.first;
	  const float stop_x  = -_width/2.0f + _width * color_region.range.second;

	  GLBegin quad(GL_QUADS);
	  glVertex2f( start_x , 0.0f );
	  glVertex2f( start_x , 5.0f );
	  glVertex2f( stop_x  , 5.0f );
	  glVertex2f( stop_x  , 0.0f );
	
	}

	hmi::Colour::PaletteColour(cn_foreground);
	// The end ticks
	{
	  GLBegin lines(GL_LINES);
	  glVertex2f( -_width/2.0f, 0.0f );
	  glVertex2f( -_width/2.0f, end_tick_y );
	  glVertex2f(  _width/2.0f, 0.0f );
	  glVertex2f(  _width/2.0f, end_tick_y );
	}

	// Draw the horizontal line
	{
	  GLBegin lines(GL_LINES);
	  glVertex2f( -_width/2.0f, 0.0f );
	  glVertex2f(  _width/2.0f, 0.0f );
	}
      }
            
    }
  }

  void renderDynamic(float position_top_pct, float position_bottom_pct = -1.0f) const
  {
    {
      GLSaveMatrix original_state;
      glTranslatef( _x_position, _y_position, 0.0f );

      hmi::Colour::PaletteColour(cn_foreground);
      GLLineWidth width(1.5f);
      GLLineSmooth smooth;

      // The label is not dynamic, but can't be put in a display, therfore we treat
      // it as dynamic
      HMIText labeltext(hmi::FontManager::Get(0));
      labeltext.bottom().hcenter().size(0.18).position(0.0f, 1.5f*_end_tick_size);
      labeltext << _label;
      labeltext.draw();

      const float indicator_height = _end_tick_size*1.2;
      const float indicator_width  = indicator_height;

      // Draw the top indicator when necesary
      if(position_top_pct >= 0.0f)
      {
	const float indicator_x_pos = -_width/2.0f + position_top_pct * _width;

	setIndicatorColor(position_top_pct);
	
	GLBegin polygons(GL_POLYGON);
	glVertex2f( indicator_x_pos , 0.0f );
	glVertex2f( indicator_x_pos - indicator_width/2.0f , indicator_height );
	glVertex2f( indicator_x_pos + indicator_width/2.0f , indicator_height );
      }

      // Draw the bottom indicator when necesary
      if(position_bottom_pct >= 0.0f)
      {
	const float indicator_x_pos = -_width/2.0f + position_bottom_pct * _width;

	setIndicatorColor(position_bottom_pct);
	
	GLBegin polygons(GL_POLYGON);
	glVertex2f( indicator_x_pos , 0.0f );
	glVertex2f( indicator_x_pos - indicator_width/2.0f , -indicator_height );
	glVertex2f( indicator_x_pos + indicator_width/2.0f , -indicator_height );
      }
    }
  }

private:
  void setIndicatorColor(float pct) const
  {
    hmi::Colour::PaletteColour(cn_foreground);

    BOOST_FOREACH(ColorRegion color_region, _color_regions)
    {
      const float lower_bound = color_region.range.first;
      const float upper_bound = color_region.range.second;

      if( color_region.color_indicator && pct >= lower_bound && pct < upper_bound )
	hmi::Colour::PaletteColour(color_region.color);
    }
  };

private:
  float _width;
  alignment _alignment;
  float _end_tick_size;
  size_t _n_ticks;
  float _tick_size;
  std::string _label;
  float _x_position;
  float _y_position;
  ColorRegions _color_regions;
  
};

#endif /* _HMITOOLS_H_ */
