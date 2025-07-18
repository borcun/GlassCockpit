/*=========================================================================

  Copyright (c) 2005-2010 Hugo Vincent <hugo.vincent@gmail.com>
  All rights reserved.
  
  This project is distributed under the terms of the GNU General Public License
  Version 3 <http://www.gnu.org/licenses/gpl.html>.
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, specifically version 3 of the License.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  =========================================================================*/

#include <math.h>
#include "data_source_manager.h"
#include "MarkedDial.h"
#include "CircleEvaluator.h"
#include "constants.h"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object)->*(ptrToMember))

namespace OpenGC
{

  MarkedDial::MarkedDial()
  {
    m_Font = FontManager::getInstance()->LoadDefaultFont();

    m_PhysicalPosition.first = 0;
    m_PhysicalPosition.second = 0;

    m_PhysicalSize.first = 30;
    m_PhysicalSize.second = 30;

    m_Scale.first = 1.0;
    m_Scale.second = 1.0;

    m_Min = 0.0, m_Max = 0.0;
    m_TickSpacing = 1.0, m_TickDivisor = 1.0;
    m_DataFn = 0;
  }

  MarkedDial::~MarkedDial()
  {

  }

  void MarkedDial::Render()
  {
    GaugeComponent::Render();

    float value = CALL_MEMBER_FN(DataSourceManager::getInstance()->getDataSource()->GetAirframe(), m_DataFn)();

    if (value < m_Min)
      value = m_Min;
    else if (value > m_Max)
      value = m_Max;

    float R = 11.0;
    float minDegrees = 220.0;
    float maxDegrees = 100.0;

    float maxDegreesUse360 = maxDegrees;
    if (maxDegrees < minDegrees)
      maxDegreesUse360 += 360;

    float negativeoffset = 0;
    if (m_Min < 0)
      negativeoffset = m_Min*-1.0;

    float radians;
    char buf[10];
    //GLUquadric *qobj;

    glLineWidth(2.0);

    glTranslatef(18, 18, 0);

    // gauge
    glColor3ub(51, 51, 76);
    CircleEvaluator *aCircle = CircleEvaluator::getInstance();
    aCircle->SetDegreesPerPoint(10.0);
    aCircle->SetRadius(R);
    aCircle->SetOrigin(0.0, 0.0);
    aCircle->SetArcStartEnd(minDegrees, value / m_Max * (maxDegreesUse360 - minDegrees) + minDegrees);

    aCircle->ResetVertices();
    aCircle->AddVertex(0,0);
    aCircle->Evaluate();
    aCircle->Render(GL_TRIANGLE_FAN);

    /*qobj = gluNewQuadric();
      gluPartialDisk(qobj, 0, R+1, 50, 1, minDegrees, value / m_Max * (maxDegreesUse360-minDegrees));
      gluDeleteQuadric(qobj);*/

    float percentage = value / (m_Max-m_Min) ;
    float degree = minDegrees + ((maxDegreesUse360 - minDegrees) * percentage);
    radians = degree * DEG_TO_RAD;
    glColor3ub(255, 255, 255);
    const float vertices[] = {0,0,   R*sin(radians),R*cos(radians)};
    glVertexPointer(2, GL_FLOAT, 0, &vertices);
    glDrawArrays(GL_LINE_STRIP, 0, 2);

    //circle outside
    glColor3ub(255, 255, 255);
    aCircle->SetArcStartEnd(minDegrees, maxDegrees);

    // FIXME enable mitering
    aCircle->ResetVertices();
    aCircle->Evaluate();
    aCircle->Render(GL_LINE_STRIP);

    /*qobj = gluNewQuadric();
      gluPartialDisk(qobj, R, R+1, 50, 1, minDegrees, maxDegreesUse360-minDegrees);
      gluDeleteQuadric(qobj);*/

    // unit markers
    FontManager::getInstance()->SetSize(m_Font, 4.0, 3.5);
    float percentagev, degreev;

    for (float xs = m_Min; xs <= m_Max; xs += m_TickSpacing)
      {
	percentagev = (xs+negativeoffset) / (m_Max-m_Min) ;
	degreev =  minDegrees+ ((maxDegreesUse360- minDegrees)*percentagev);
	radians=degreev * DEG_TO_RAD;
	glColor3ub(255, 255, 255);
	const float vertices[] = {R*sin(radians),R*cos(radians),   (R-2)*sin(radians),(R-2)*cos(radians)};
	glVertexPointer(2, GL_FLOAT, 0, &vertices);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
		
	if ((fabs(xs) < 1.0) && (fabs(xs) > 0.01))
	  sprintf(buf, "%0.1f",xs);
	else
	  sprintf(buf, "%.0f",xs / m_TickDivisor);
	glTranslatef(-1.5, -2, 0);
	FontManager::getInstance()->Print((R-4.5) * sin(radians) , (R-4.5) * cos(radians), buf, m_Font);			
	glTranslatef(1.5, 2, 0);
      }
  }

} // end namespace OpenGC
