/*=========================================================================

  Copyright (c) 2001-2004 Damion Shelton
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

#include "Globals.h"

OpenGC::Globals *OpenGC::Globals::m_instance = nullptr;
OpenGC::DataSource *OpenGC::Globals::data_source = nullptr;
OpenGC::MessageableList *OpenGC::Globals::messageable_list = nullptr;

OpenGC::Globals::Globals(void) {
  messageable_list = new MessageableList();
  data_source = nullptr;
}

OpenGC::Globals::~Globals() {
  if (nullptr != data_source) {
    delete data_source;
    data_source = nullptr;
  }
  
  if (nullptr != messageable_list) {
    delete messageable_list;
    messageable_list = nullptr;
  }
}

OpenGC::Globals *OpenGC::Globals::getInstance(void) {
  if (nullptr == m_instance) {
    m_instance = new Globals();
  }

  return m_instance;
}
