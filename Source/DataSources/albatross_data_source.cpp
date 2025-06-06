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

#include "albatross_data_source.h"
#include "Constants.h"
#include "Debug.h"

OpenGC::AlbatrossDataSource::AlbatrossDataSource(void)
    : OpenGC::DataSource()
{
    m_airframe->SetStatus_Active(false);
    m_airframe->SetDirector_Active(false);
    m_airframe->SetGot_Data(false);
    m_airframe->SetStatus_Text_NoData("WAITING FOR CONNECTION");

    m_airframe->SetStatus_Text1("YAW");
    m_airframe->SetStatus_Text2("ALT");
    m_airframe->SetStatus_Text3("BNK");
    m_airframe->SetStatus_Text4("VEL");
    m_airframe->SetStatus_Colour1(1);
    m_airframe->SetStatus_Colour2(1);
    m_airframe->SetStatus_Colour3(1);
    m_airframe->SetStatus_Colour4(1);

    LogPrintf("AlbatrossDataSource: NOT CONNECTED\n");
}

OpenGC::AlbatrossDataSource::~AlbatrossDataSource()
{
}

bool OpenGC::AlbatrossDataSource::OnIdle(void) {
    // FIXME actually get data (duh!)
    return false; // should be true once data is coming in
}
