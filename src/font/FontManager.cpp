#include "FontManager.h"
#include "preference_manager.h"

namespace OpenGC
{
  string FontManager::m_FontPath;
  FontManager *FontManager::m_instance = nullptr;

  FontManager::FontManager()
    : m_NumFonts(0)
  {

  }

  FontManager::~FontManager() {
    // Delete each font in the list
    std::vector<Font*>::iterator iter;
    
    for (iter = m_FontList.begin(); iter != m_FontList.end(); ++iter) {
	delete *iter;
      }
  }

  FontManager *FontManager::getInstance(void) {
    if (nullptr == m_instance) {
      m_instance = new FontManager();
    }

    return m_instance;
  }
  
  /** Loads the default font, i.e. Bitstream Vera */
  int FontManager::LoadDefaultFont()
  {
#ifdef USE_GL_FONTS
    return this->LoadFont("bitstream_vera.glfont");
#else
    return this->LoadFont("bitstream_vera.ttf");
#endif
  }

  int FontManager::LoadFont(const string& name)
  {
    if (m_FontPath == "") {
		
      m_FontPath = PreferenceManager::getInstance()->getString("PathToData") + "Fonts/";
    }
	
    // Concatenate the font name onto the font path
    m_NameWithPath = m_FontPath + name;

    // First, check to see if the font is already loaded
    for(int i = 0; i < m_NumFonts; i++)
      {
	if (m_NameWithPath == m_FontList[i]->GetName())
	  {
	    return i;
	  }
      }

    // Ok, the font isn't loaded, so create a new one
    Font* pFont = new Font;

    if( pFont->LoadFont(m_NameWithPath) )
      {
	// Add the font to the list
	m_FontList.push_back(pFont);

	// Update the number of stored fonts
	m_NumFonts++;

	// Return the index of the new font
	return (m_NumFonts - 1);
      }
    else
      {
	delete pFont;
	// Return the flag that means we failed
	return -1;
      }
  }

  void FontManager::SetSize(int font, double x, double y)
  {
    if( (font >= 0) && (font < m_NumFonts) )
      {
	m_FontList[font]->SetSize(x,y);
      }
  }

  void FontManager::SetRightAligned(int font, bool rightAligned)
  {
    if( (font >= 0) && (font < m_NumFonts) )
      {
	m_FontList[font]->SetRightAligned(rightAligned);
      }
  }

  void FontManager::Print(double x, double y, const char* text, int font)
  {
    if( (font >= 0) && (font < m_NumFonts) )
      {
	m_FontList[font]->Print(x,y,text);
      }
  }

} // end namespace OpenGC
