//************************************************************
// ColorMap.hpp
//
// Created on Thu Aug 29 14:52:59 2013 by Jan Comans
//
// Copyright 2013 Jan Comans -- jan@comans.be
//
// License: Boost Software License Version 1.0
// See LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt
//************************************************************

#ifndef _COLORMAP_H_
#define _COLORMAP_H_

#include <Colour.hxx>

enum ColorNames
{
  cn_foreground,
  cn_background,

  cn_outline,

  cn_ownship,
  cn_graph_background,
  cn_tape_background,
  
  cn_normal,
  cn_warning,
  cn_danger,

  cn_nav,
  cn_envelope,

  cn_performance,
  cn_active,
  cn_apmode,
  cn_sky,
  cn_ground,
  cn_intentional,
  cn_refbar,
  cn_refbar_dark
};

inline void loadDefaultColorMap()
{
  hmi::Colour::ClearPalette();
  
  hmi::Colour::SetPaletteColour(cn_foreground,        hmi::Colour::White);
  hmi::Colour::SetPaletteColour(cn_background,        hmi::Colour::Black);
  hmi::Colour::SetPaletteColour(cn_outline,           hmi::Colour::Grey);

  hmi::Colour::SetPaletteColour(cn_ownship         ,  hmi::Colour::Yellow);
  hmi::Colour::SetPaletteColour(cn_graph_background,  hmi::Colour::DarkGrey);
  hmi::Colour::SetPaletteColour(cn_tape_background ,  hmi::Colour::Grey);
    
  hmi::Colour::SetPaletteColour(cn_normal,            hmi::Colour::DarkGreen);
  hmi::Colour::SetPaletteColour(cn_warning,           hmi::Colour::Amber);
  hmi::Colour::SetPaletteColour(cn_danger,            hmi::Colour::DarkRed);

  hmi::Colour::SetPaletteColour(cn_nav,               hmi::Colour::Magenta);
  hmi::Colour::SetPaletteColour(cn_envelope,          hmi::Colour::Cyan);

  hmi::Colour::SetPaletteColour(cn_performance, hmi::Colour::DarkGreen);
  hmi::Colour::SetPaletteColour(cn_active,      hmi::Colour::Cyan);
  hmi::Colour::SetPaletteColour(cn_apmode,      hmi::Colour::Green);
  hmi::Colour::SetPaletteColour(cn_sky,         hmi::Colour::Blue);
  hmi::Colour::SetPaletteColour(cn_ground,      hmi::Colour::Brown);
  hmi::Colour::SetPaletteColour(cn_intentional, hmi::Colour::Amber);
  hmi::Colour::SetPaletteColour(cn_refbar,      253./256., 252./256.,  1./256.);
  hmi::Colour::SetPaletteColour(cn_refbar_dark, 111./256., 103./256., 52./256.);
};

inline void loadGrayscaleColorMap()
{
  hmi::Colour::ClearPalette();
  
  hmi::Colour::SetPaletteColour(cn_foreground,       hmi::Colour::Black);
  hmi::Colour::SetPaletteColour(cn_background,       hmi::Colour::White);
  hmi::Colour::SetPaletteColour(cn_outline,          hmi::Colour::Grey);

  hmi::Colour::SetPaletteColour(cn_ownship         , hmi::Colour::Black);
  hmi::Colour::SetPaletteColour(cn_graph_background, hmi::Colour::White);
  hmi::Colour::SetPaletteColour(cn_tape_background , hmi::Colour::Grey);

  hmi::Colour::SetPaletteColour(cn_normal,           hmi::Colour::Grey);
  hmi::Colour::SetPaletteColour(cn_warning,          hmi::Colour::Grey);
  hmi::Colour::SetPaletteColour(cn_danger,           hmi::Colour::DarkGrey);

  hmi::Colour::SetPaletteColour(cn_nav,               hmi::Colour::Grey);
  hmi::Colour::SetPaletteColour(cn_envelope,          hmi::Colour::Grey);

  hmi::Colour::SetPaletteColour(cn_performance, hmi::Colour::DarkGrey);
  hmi::Colour::SetPaletteColour(cn_active,      hmi::Colour::Grey);
  hmi::Colour::SetPaletteColour(cn_apmode,      hmi::Colour::DarkGrey);
  
  hmi::Colour::SetPaletteColour(cn_sky,         hmi::Colour::Blue);
  hmi::Colour::SetPaletteColour(cn_ground,      hmi::Colour::Brown);
  
  hmi::Colour::SetPaletteColour(cn_intentional, hmi::Colour::Amber);
  
  hmi::Colour::SetPaletteColour(cn_refbar,      hmi::Colour::Grey);
  hmi::Colour::SetPaletteColour(cn_refbar_dark, hmi::Colour::DarkGrey);
};


#endif /* _COLORMAP_H_ */
