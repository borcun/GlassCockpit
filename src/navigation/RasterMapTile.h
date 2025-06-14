#ifndef RasterMapTile_h
#define RasterMapTile_h

/** Represents one tile in a raster map.
 */

namespace OpenGC {

  class RasterMapTile
  {
  public:
    RasterMapTile(unsigned char *image, unsigned int width, unsigned int height);
	
    unsigned char *Image() { return m_Image; }
    unsigned int Width() { return m_Width; }
    unsigned int Height() { return m_Height; }

  private:
    unsigned char *m_Image;
    unsigned int m_Width, m_Height;
  };
	
} // end namespace OpenGC

#endif // RasterMapTile_h
