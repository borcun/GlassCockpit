#include "raster_map_tile.h"

OpenGC::RasterMapTile::RasterMapTile(unsigned char *image, unsigned int width, unsigned int height)
  : m_Image(image), m_Width(width), m_Height(height)
{

}

OpenGC::RasterMapTile::~RasterMapTile() {

}
