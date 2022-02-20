/*	project_utilities.cpp
	
	This class contains a collection of all openGL utilities usfull for the 
	simulation project AE4-361

	created:	April 26, 2002
	Author:		Mark Mulder
	Version:	1.0
*/


#include "project_utilities.h"

GLenum texFormat;

ProjectUtilities::ProjectUtilities()
{
	//do nothing
}

ProjectUtilities::~ProjectUtilities()
{
	//do nothing
}

/* strokeString routine draws a String on the screen using glutStrokeCharacter
   parameters:	x [screen coords]	x-position of the string
				y [screen coords]	y-position of the string
				*msg [String]		pointer to the string
				*font [Glut font]	GLUT_STROKE_ROMAN or GLUT_STROKE_MONO_ROMAN 				
				size				the screen size of the font
*/
void ProjectUtilities::strokeString(double x, double y, char *msg, void *font, double size)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, size);
	//enable anti-aliassing - disable for fast graphics....
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	//end anti-aliassing graphics

	glLineWidth(2.0);
	while (*msg)
	{
		glutStrokeCharacter(font, *msg);
		msg++;
	}

	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
	glLineWidth(1.0);
	glPopMatrix();
}

/*	draw circle routine - draws a circle at (origin_x,origin_y) with radius radius
	parameters: radius
				origin_x [screen coords]
				origin_y [screen coords]
	returns: nothing
*/
void ProjectUtilities::drawCircle(double radius, double origin_x, double origin_y)
{
	int angle;	
	GLint delta_angle = 5;	//circle devided in parts of 5 degrees
	GLdouble x,y;

	glBegin(GL_LINE_LOOP);
	for (angle=0; angle<360 ; angle=angle+delta_angle)
	{
		x = origin_x + cos(3.1415*angle/180)*radius;
		y = origin_y + sin(3.1415*angle/180)*radius;
		glVertex2f(x,y);
	}
	glEnd();
}

/*  drawCompass routine - draws a compass with with radius radius at
						  O(0,0,0) North up, tickmarks and heading degrees.
	parameters:	radius
	returns:	nothing
*/
void ProjectUtilities::drawCompass(double radius)
{
	char temp[10];						//temporary array for text	
	double angle;							//local parameter used in for-loops
	double tick_angle = 5.0;			//tick at every tick_angle degrees
	double big_size = radius*3/100;		//length of big tickmarks relative to radius
	double small_size = radius*1.5/100;	//length of small tichmarks relative to radius
	double font_size = radius*0.035/100;	//size of the heading numbers relative to radius
	int number_angle = 10;				//number at every number_angle degrees	
		
	int big = 1;						//flag to check whether to draw a big or a small tick-mark
	int heading_count = 90;				//zero degrees angle is 90 degrees heading
	double origin_x = 0.0;
	double origin_y = 0.0;

	drawCircle(radius,origin_x,origin_y);
	
	glColor3f(1,1,1); //white
	
	for (angle=0; angle<360; angle=angle+tick_angle)
	{		
		//draw tick-marks
		glPushMatrix();
		glRotatef(angle,0,0,1);
		glBegin(GL_LINES);
		glVertex2f(0,radius);
		if (big)
		{
			glVertex2f(origin_x,origin_y+radius-big_size);
			big = 0;
		}
		else
		{
			glVertex2f(origin_x,origin_y+radius-small_size);
			big = 1;
		}
		glEnd();
		glPopMatrix();
	}
	
	//draw digits
	for (angle=0; angle<360; angle=angle+number_angle)
	{
		if (heading_count<=0)
			heading_count=360;
		
		glPushMatrix();
		
			glRotatef(-90+angle,0.0,0.0,1.0);
			sprintf(temp, "%02d", heading_count/10);
			strokeString(origin_x-radius/38,origin_y+radius-big_size-radius/25,
															temp, GLUT_STROKE_ROMAN, font_size);
			
		glPopMatrix();
		
		heading_count = heading_count - number_angle;
	}	
}

// make sure the image is ok without scaling
int ProjectUtilities::checkSize (int x)
{	
	if (x == 2	 || x == 4 || 
		x == 8	 || x == 16 || 
		x == 32  || x == 64 ||
		x == 128 || x == 256 || x == 512 ||
		x == 1024)
		return 1;
	else return 0;
	
}
// reads in RGBA data and returns the same, 32 bit image
unsigned char *ProjectUtilities::getRGBA(FILE *s, int size)
{
	unsigned char *rgba;
	unsigned char temp;
	int bread;
	int i;

	rgba =(unsigned char*) malloc (size * 4); // allocate memory for image

	//  no memory allocated?
	if (rgba == NULL)
		return 0;

	bread = fread (rgba, sizeof (unsigned char), size * 4, s); 
	
	// make sure that all of the data is where it should be
	if (bread != size * 4)
	{
		free (rgba);
		return 0;
	}
	for (i = 0; i < size * 4; i += 4 )
	{
		temp = rgba[i];
		rgba[i] = rgba[i + 2];
		rgba[i + 2] = temp;
	}

	texFormat = GL_RGBA;
	return rgba;
}
// reads in RGB data and returns RGB, 24bit image
unsigned char *ProjectUtilities::getRGB (FILE *s, int size)
{
	unsigned char *rgb;
	unsigned char temp;
	int bread;
	int i;

	rgb = (unsigned char*) malloc (size * 3); // allocate memory for image
	
	//  no memory allocated?
	if (rgb == NULL)
		return 0;

	bread = fread (rgb, sizeof (unsigned char), size * 3, s); // read in the image data

	// make sure that all of the data is where it should be
	if (bread != size * 3)
	{
		// Bytes read != Bytes requested
		free (rgb);
		return 0;
	}

	for (i = 0; i < size * 3; i += 3)
	{
		temp = rgb[i];
		rgb[i] = rgb[i + 2];
		rgb[i + 2] = temp;
	}
	
	texFormat = GL_RGB;

	return rgb;
}
// get the image data
char *ProjectUtilities::getData (FILE *s, int sz, int iBits)
{
	if (iBits == 32)
		return (char*) getRGBA (s, sz);
	else if (iBits == 24)
		return (char*) getRGB (s, sz);	
	else
	  return NULL;// [OS]
}

// loads a 24bit or 32 bit targa file and uploads it to memory
// id is the texture id to bind too
int ProjectUtilities::loadTGA (const char *name, int id)
{
	unsigned char type[4];
	unsigned char info[7];
	unsigned char *imageData = NULL;
	int imageWidth, imageHeight;
	int imageBits, size;
	FILE *s;
	
	// Could not open the file!
	if (!(s = fopen (name, "r+bt")))
		return TGA_FILE_NOT_FOUND;

	fread (&type, sizeof (char), 3, s); // read in colormap info and image type, byte 0 ignored
	fseek (s, 12, SEEK_SET);			// seek past the header and useless info
	fread (&info, sizeof (char), 6, s);

	// make sure that the colormap is 0 and type is 2, unmapped RGB
	if (type[1] != 0 || type[2] != 2)
		return TGA_BAD_IMAGE_TYPE;

	imageWidth = info[0] + info[1] * 256; // image width
	imageHeight = info[2] + info[3] * 256; // image height
	imageBits =	info[4]; // pixel depth

	size = imageWidth * imageHeight; // image size

	// Erased by us
	// Dimension imageWidth x imageHeight is not a valid dimension!!
	if (!checkSize (imageWidth) || !checkSize (imageHeight))
		return TGA_BAD_DIMENSION;

	// Image bits != Supported bits 
	if (imageBits != 32 && imageBits != 24)
		return TGA_BAD_BITS;

	// get the image data
	imageData = (unsigned char*) getData (s, size, imageBits);
	
	fclose (s);

	// something went wrong
	if (imageData == NULL)
		return TGA_BAD_DATA;

	// OpenGL texture variables, change for various apps
	glBindTexture (GL_TEXTURE_2D, id);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D (GL_TEXTURE_2D, 0, texFormat, imageWidth, imageHeight, 0, texFormat, GL_UNSIGNED_BYTE, imageData);

	// release our image data since it has already been uploaded
	free (imageData);

	return 1;
}
