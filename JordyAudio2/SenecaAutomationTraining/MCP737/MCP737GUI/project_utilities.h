/*	project_utilities.h
	
	This class contains a collection of all openGL utilities usfull for the 
	simulation project AE4-361

	created:	April 26, 2002
	Author:		Mark Mulder
	Version:	1.0
*/


#ifndef GLUT_H
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef __HDOTH__
#define __HDOTH__
typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
#endif

#if !defined(PROJECT_UTILITIES_H)
#define PROJECT_UTILITIES_H


// Error Codes
// file was not found
#define TGA_FILE_NOT_FOUND			13
// color mapped image or image is not RGB uncompressed
#define TGA_BAD_IMAGE_TYPE			14
// dimension is not a power of 2
#define TGA_BAD_DIMENSION			15
// image bits is not 24 or 32
#define TGA_BAD_BITS				16
// image data could not be loaded
#define TGA_BAD_DATA				17


class ProjectUtilities
{
public:
	ProjectUtilities(void);
	~ProjectUtilities(void);

	void strokeString(double x, double y, char *msg, void *font, double size);
	void drawCircle(double radius, double origin_x, double origin_y);
	void drawCompass(double radius);
		
	/*
		Copyright (C) 1999
		For non-commercial use only.

		Date	: 05/05/1999
		Author	: Nate Miller
		Contact	: vandals1@home.com
	*/
	// id is the texture id to bind too
	int loadTGA (const char *name, int id);
private:
	// get the image data
	char *getData (FILE *s, int sz, int iBits);
	// reads in RGB data and returns RGB, 24bit image
	unsigned char *getRGB (FILE *s, int size);
	// reads in RGBA data and returns the same, 32 bit image
	unsigned char *getRGBA (FILE *s, int size);
	// make sure the image is ok without scaling
	int checkSize (int x);
	/*
		end Nate Millers tga-loader methods
	*/

};

#endif
