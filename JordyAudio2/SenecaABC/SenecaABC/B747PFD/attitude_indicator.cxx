#include "attitude_indicator.hxx"
#include <cmath>
#include <stdio.h>

// Because the column obstructed the view on the compass,
// the compass was moved above the attutude indicator.
// Moving this item down was done by: 77.5f-12.0f
attitude_indicator::attitude_indicator(): gl2DObject("attitude_indicator", 69.0f, 66.0f),
    m_att_stock1(0), m_att_stock2(0), m_flightdirbar_stock(0),m_climb_stock(0),
    m_bank(0.0f), m_pitch(0.0f), m_thetaFD(0.0f), m_phiFD(0.0f), m_slip(0.0f),m_climb(0.0f), dx1(0.0f), dy1(0.0f), dx2(0.0f), dy2(0.0f),
    m_FDEngaged(true)
{

}

attitude_indicator::~attitude_indicator()
{

}

void attitude_indicator::init()
{
  //! Attitude indicator stock scene part 1
  m_att_stock1 = glGenLists(1);
  if(m_att_stock1 !=0)
  {
    glNewList(m_att_stock1, GL_COMPILE);

    // Draw Attitude Indicator Outline
    glColor3fv(Black);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(30.0f,30.0f);
    for (int angle = 0; angle <= 90 ; angle = angle + 15)
      glVertex2f( 23.0f + cos (angle * 0.017453f) * 7.0f, 23.0f + sin (angle * 0.017453f) * 7.0f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-30.0f,30.0f);
    for (int angle = 0; angle <= 90 ; angle = angle + 15)
      glVertex2f( -(23.0f + cos (angle * 0.017453f) * 7.0f), 23.0f + sin (angle * 0.017453f) * 7.0f);
    glEnd();


    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-30.0f,-30.0f);
    for (int angle = 0; angle <= 90 ; angle = angle + 15)
      glVertex2f( -(23.0f + cos (angle * 0.017453f) * 7.0f), -(23.0f + sin (angle * 0.017453f) * 7.0f));
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(30.0f,-30.0f);
    for (int angle = 0; angle <= 90 ; angle = angle + 15)
      glVertex2f( (23.0f + cos (angle * 0.017453f) * 7.0f), -(23.0f + sin (angle * 0.017453f) * 7.0f));
    glEnd();


    // Draw Aircraft Symbol and Bank Angle Scale

    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(-0.5f , -0.5f, +0.5f, 0.5f);


    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(-20.0f,-0.5f,-5.0f,0.5f);
    glRectf(-6.7f,-5.0f,-5.0f,0.0f);

    glRectf(20.0f,-0.5f,5.0f,0.5f);
    glRectf(6.7f,-5.0f,5.0f,0.0f);

    glPushMatrix();
    glScalef(1.1f,1.1f,1.1f);
    glRotatef(-50, 0.0, 0.0, 1.0);
    for (int i=0;i<=10;i++)
    {
      if (i == 1 || i == 9)
      {
        glBegin(GL_POLYGON);
        glVertex2f(0.0, 24.0);
        glVertex2f(1.0, 26.0);
        glVertex2f(-1.0, 26.0);
        glEnd();
      }
      else if (i == 5)
      {
        glBegin(GL_POLYGON);
        glVertex2f(0.0, 24.0);
        glVertex2f(2.0, 27.0);
        glVertex2f(-2.0,27.0);
        glEnd();
      }
      else
      {
        glBegin(GL_LINES);
        glVertex2f(0.0, 24.0);
        glVertex2f(0.0, 26.5);
        glEnd();
      }

      glRotatef(10, 0.0, 0.0, 1.0);
    }
    glPopMatrix();
    glEndList();
  }

  //! Attitude indicator stock scene part 2
  m_att_stock2 = glGenLists(1);
  if(m_att_stock2 !=0)
  {
    glNewList(m_att_stock2, GL_COMPILE);

    // earth
    glBegin(GL_POLYGON);
    glColor3fv(Brown);
    glVertex2f(-3000.0, 0.0);
    glVertex2f(3000.0, 0.0 );
    glVertex2f(3000.0, -1500.0);
    glVertex2f(-3000.0, -1500.0);
    glEnd();

    // sky
    glBegin(GL_POLYGON);
    glColor3fv(LightBlue);
    glVertex2f(-3000.0, 0.0);
    glVertex2f(3000.0, 0.0 );
    glVertex2f(3000.0, 1500.0);
    glVertex2f(-3000.0, 1500.0);
    glEnd();


    glColor3fv(White);
    char buf[20];

    // numbers besides pitch ladder
    for (int i=1; i<10; i++)
    {
      snprintf(buf,20,"%i",i*10);
      strokeString(buf, 9,   i*13-1, 3.0);
      strokeString(buf, 9,   -i*13-1, 3.0);
      strokeString(buf, -14, i*13-1, 3.0);
      strokeString(buf, -14, -i*13-1, 3.0);
    }

    // pitch ladder
    glBegin(GL_LINES);
    for (int i=1;i<10;i++)
    {
      // major tick positive
      glVertex2f(-8.0, i*13.0);
      glVertex2f(8.0, i*13.0);

      // minor tick positive
      glVertex2f(-4.0, i*13.0-6.5);
      glVertex2f(4.0, i*13.0-6.5);

      glVertex2f(-2.0, i*13.0-6.5-3.25);
      glVertex2f(2.0, i*13.0-6.5-3.25);

      glVertex2f(-2.0, i*13.0-6.5+3.25);
      glVertex2f(2.0, i*13.0-6.5+3.25);

      // major tick negative
      glVertex2f(-8.0, -i*13.0);
      glVertex2f(8.0, -i*13.0);

      // minor tick negative
      glVertex2f(-4.0, -i*13.0+6.5);
      glVertex2f(4.0, -i*13.0+6.5);

      glVertex2f(-2.0, -i*13.0+6.5-3.25);
      glVertex2f(2.0, -i*13.0+6.5-3.25);

      glVertex2f(-2.0, -i*13.0+6.5+3.25);
      glVertex2f(2.0, -i*13.0+6.5+3.25);
    }
    glEnd();

    // horizon
    glBegin(GL_LINES);
    glVertex2f(-3000.0, 0.0);
    glVertex2f(3000.0, 0.0);
    glEnd();

    glEndList();
  }

  //! Flight Director Bar stock scene
  m_flightdirbar_stock = glGenLists(1);
  if(m_flightdirbar_stock != 0)
  {
    glNewList(m_flightdirbar_stock, GL_COMPILE);
    glColor3fv(Magenta);
    glLineWidth(3.0);// added FV 08jan03 to make f/d bar better visible
    glBegin(GL_LINES);
    glVertex2f(-17.0f, 0.f);
    glVertex2f(17.0f, 0.f);
    glEnd();
    glLineWidth(1.0);// added FV 08jan03
    glEndList();
  }
  //! Climb_director stock
  m_climb_stock = glGenLists(1);
  if(m_climb_stock != 0)
  {
    glNewList(m_climb_stock, GL_COMPILE);
    glColor3f(1.0f, 0.5f, 0.0f);
    //glColor3fv(White);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-5.0f, 0.f);
    glVertex2f(+5.0f, 0.f);
    glEnd();
    glLineWidth(1.0);
    glEndList();
  }



}

void attitude_indicator::draw()
{
  glLineWidth(1.0);
  selectClippingArea(0.0f, 0.0f, 77.0f, 77.0f);
  glScalef(1.3f,1.3f,1.3f);

  // Draw Attitude Indicator Outline
  glPushMatrix();

  // To rotate bank angle

  glRotatef(m_bank, 0.0f, 0.0f, 1.0f);

  glPushMatrix();
  // To translate pitch (13 mm /10 degrees)
  glTranslatef(0.0f, -1.3f * m_pitch, 0.0f);

  // Draw the horzon, earth, sky and pitch ladder
  glCallList(m_att_stock2);
  glPopMatrix();

  // Draw bank indicator

  glBegin(GL_LINE_LOOP);
  glVertex2f(2.0f,  23.1f);
  glVertex2f(0.0f,  26.4f);
  glVertex2f(-2.0f, 23.1f);
  glEnd();

  // TODO add sideslip (beta) indication // 8 was 4.0 12 &13 was 22 &23

// Oude sideslip indicator

if(m_slip_top==true){
  if (m_slip_beta==true){
     glColor3f(1.0f, 1.0f, 0.0f);}
  else{
// slip maal 10 want verlaagt in beneden indicator
  glColor3f(1.0f, 1.0f, 1.0f);}
  glBegin(GL_LINE_LOOP);
  glVertex2f(-2.0f + 20.0 * m_slip, 22.0f);
  glVertex2f( 2.0f + 20.0 * m_slip, 22.0f);
  glVertex2f( 2.0f + 20.0 * m_slip, 23.1f);
  glVertex2f(-2.0f + 20.0 * m_slip, 23.1f);
  glEnd();}

  glPopMatrix();

  // Draw Attitude Indicator Outline
  glCallList(m_att_stock1);


// Draw new sideslip indicator



if(m_slip_top==false){
   if (m_slip_beta==true){
      glColor3f(1.0f, 1.0f, 0.0f);}
   else{
      glColor3f(1.0f, 1.0f, 1.0f);}
   glBegin(GL_POLYGON);
   glVertex2f(0.0f, 0.0f);
   glVertex2f(m_slip*20.0,m_slip*5.0);
   glVertex2f(m_slip*20.0,-m_slip*5.0);
   glEnd();
   }


// Draw max sustained climbangle
if(m_climb >-99.0/DEG2RAD){

    glPushMatrix();
    // Translate to advised climb position
    glTranslatef(0.0f, -1.3f *(m_pitch - m_climb), 0.0f);
    glRotatef( m_bank, 0.0f, 0.0f, 1.0f);
    glCallList(m_climb_stock);
    glPopMatrix();
   }






  // Draw flight director bars

  if (m_FDEngaged)
  {
    glPushMatrix();
    // Translate to commanded pitch position (13 mm /10 degrees)
    glTranslatef(0.0f, 1.3f * m_thetaFD, 0.0f);
    // Draw the horizontal pitch bar
    glCallList(m_flightdirbar_stock);
    glPopMatrix();

    glPushMatrix();
    // Orthogonal to pitch bar
    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
    // Translate to commanded roll position (7.8 mm /10 degrees)
    glTranslatef(0.0f, 0.2f * m_phiFD, 0.0f);
    // Draw the vertical roll bar
    glCallList(m_flightdirbar_stock);
    glPopMatrix();
  }

  deselectClippingArea();
}

void attitude_indicator::setAttitude(float pitch, float bank)
{
  m_pitch   = pitch / M_PI * 180.0f;
  m_bank    = bank  / M_PI * 180.0f;
}

void attitude_indicator::setSideSlip(float slip, bool Slip_top, bool Slip_beta, float Climb)
{
  // TODO scale slip to set m_slip range, now set at 15 DEG / indicator width
  // m_slip range: [-1 0 1] equal left of, right underneath, and right of bank indicator respectively

//pas demping toe
  m_slip =  slip / DEG2RAD / 15.0;
  m_climb=  Climb /DEG2RAD;
  m_slip_top=Slip_top;
  m_slip_beta=Slip_beta;
}

void attitude_indicator::setFDBarsDeg(float theta, float phi)
{
  m_thetaFD = theta;
  m_phiFD   = phi;
}

void attitude_indicator::setFDBarsRad(float theta, float phi)
{
  m_thetaFD = theta / M_PI * 180.0f;
  m_phiFD   = phi   / M_PI * 180.0f;
}

void attitude_indicator::showFD(bool b)
{
  m_FDEngaged = b;
}
