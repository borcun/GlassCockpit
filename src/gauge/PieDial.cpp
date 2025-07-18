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
#include "CircleEvaluator.h"
#include "gl_headers.h"
#include "PieDial.h"
#include "constants.h"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object)->*(ptrToMember))

namespace OpenGC
{
  PieDial::PieDial()
  {
    m_Font = FontManager::getInstance()->LoadDefaultFont();

    m_PhysicalPosition.first = 0;
    m_PhysicalPosition.second = 0;

    m_PhysicalSize.first = 42;
    m_PhysicalSize.second = 34;

    m_Scale.first = 1.0;
    m_Scale.second = 1.0;

    m_DataFn = 0;
    m_Min = 0.0, m_Max = 0.0;
  }

  PieDial::~PieDial()
  {

  }

  void PieDial::Render()
  {
    GaugeComponent::Render();

    float value = CALL_MEMBER_FN(DataSourceManager::getInstance()->getDataSource()->GetAirframe(), m_DataFn)();

    if (value < m_Min)
      value = m_Min;
    if (value > m_Max)
      value = m_Max;

    char buf[10];
    //GLUquadric *qobj;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(20, 20, 0);

    // gauge
    if (value < m_MinYellow)
      glColor3ub(51, 51, 76); // blue-grey
    else if (value < m_MinRed)
      glColor3ub(247, 231, 8); // yellow
    else
      glColor3ub(255, 20, 20); // red

    // Fill of the dial from 0 to the needle
    CircleEvaluator *aCircle = CircleEvaluator::getInstance();
    aCircle->SetDegreesPerPoint(10.0);
    aCircle->SetRadius(R);
    aCircle->SetOrigin(0.0, 0.0);
    aCircle->SetArcStartEnd(minDegrees, value / m_Max * (maxDegrees - minDegrees) + minDegrees);

    aCircle->ResetVertices();
    aCircle->AddVertex(0,0);
    aCircle->Evaluate();
    aCircle->Render(GL_TRIANGLE_FAN);

    // White line that is this needle of the dial
    float degree = minDegrees + ((maxDegrees - minDegrees) * (value / (m_Max-m_Min)));
    float radians = degree * DEG_TO_RAD;
    glColor3ub(255, 255, 255);
    glLineWidth(2.0);
    const float vertices[] = {0, 0, R * sin(radians), R * cos(radians)};
    glVertexPointer(2, GL_FLOAT, 0, &vertices);
    glDrawArrays(GL_LINE_STRIP, 0, 2);

    RenderTicks(aCircle);
    RenderArc(aCircle);
    glTranslatef(-20, -20, 0);

    // white rectangle containing the text
    glColor3ub(255, 255, 255);
    glLineWidth(1.0);
    static const float vertices2[] = {42,20,   20,20,   20,30,   42,30};
    glVertexPointer(2, GL_FLOAT, 0, &vertices2);
    glDrawArrays(GL_LINE_STRIP, 0, 4);

    // text
    FontManager::getInstance()->SetSize(m_Font, 5, 5);
    glColor3ub(255, 255, 255);
    sprintf(buf, "%.0f", value);
    FontManager::getInstance()->Print( 21.9, 22.7, buf, m_Font);

    glPopMatrix();
  }

  void PieDial::RenderTicks(CircleEvaluator *circ)
  {
    // yellow stripe
    float percentagey = m_MinYellow / (m_Max - m_Min) ;
    float degreeyellow = minDegrees + ((maxDegrees - minDegrees) * percentagey);
    glColor3ub(247, 231, 8);
    float radians = degreeyellow * DEG_TO_RAD;
    const float vertices[] = {
      R * sin(radians), R * cos(radians),
      (R + 4) * sin(radians), (R + 4) * cos(radians)
    };
    glVertexPointer(2, GL_FLOAT, 0, &vertices);
    glDrawArrays(GL_LINE_STRIP, 0, 2);

    // red stripe
    float percentager = m_MinRed / (m_Max - m_Min) ;
    float degreered =  minDegrees + ((maxDegrees - minDegrees) * percentager);
    radians = degreered * DEG_TO_RAD;
    glColor3ub(255, 0, 0);
    const float vertices2[] = {
      R * sin(radians), R * cos(radians),
      (R + 4) * sin(radians), (R + 5) * cos(radians)
    };
    glVertexPointer(2, GL_FLOAT, 0, &vertices2);
    glDrawArrays(GL_LINE_STRIP, 0, 2);
  }

  void PieDial::RenderArc(CircleEvaluator *circ)
  {
    // white partial circle 
    glColor3ub(255, 255, 255);
    circ->SetArcStartEnd(minDegrees, maxDegrees);
    // FIXME enable mitering
    glLineWidth(3.0);
    circ->ResetVertices();
    circ->Evaluate();
    circ->Render(GL_LINE_STRIP);
  }

} // end namespace OpenGC
