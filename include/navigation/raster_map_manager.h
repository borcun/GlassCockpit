#pragma once

#include <string>
#include "raster_map_tile.h"

namespace OpenGC {
  const unsigned int READ_BUFFER_SIZE = 64U * 1024U;
  
  /** This class reads and parses cache sets. For now, only MGMap caches generated
   *  by the MapTileCacher.perl script (in Util/, version 1.35) tested.
   */	
  class RasterMapManager {
  public:
    typedef enum {
      RMM_CACHE_MGMAPS = 0
    } CacheFormat;

    static RasterMapManager *getInstance(void);
    virtual ~RasterMapManager();
    /** Set cache path. MapType should be e.g. "GoogleTer" to suit your cache */
    void SetCachePath(CacheFormat format, const std::string& path, const std::string& mapType);
    /** Get tile at specified tile coordinates and zoom level. Note this may be map-type/format specific */
    RasterMapTile *GetTile(const unsigned int zoom, const unsigned int x, const unsigned int y);
    /** Get tile coordinates for the tile containing specified lat/long in a certain zoom level.
     *  (x, y) are the tile coordinate, (fx, fy) are the fractional coordinate within the tile. */
    void GetTileCoordsForLatLon(unsigned int& x, unsigned int& y, float& fx, float& fy, double lat, double lon, const unsigned int zoom);
    /** Set the cache of read-in tiles to be at most cacheSizeBytes (default is no cache) */
    void SetCacheMemorySize(const unsigned int cacheSizeBytes);
	
  private:
    static RasterMapManager *m_instance;  
    bool m_Ready;
    std::string m_CachePrefix;
    std::string m_MapType;
    unsigned char m_ReadBuffer[READ_BUFFER_SIZE];

    // Note: returned image pointer will be invalidated after a new image is read
    unsigned char *DecodeJPEG(unsigned char *readBuffer, unsigned int length, unsigned int& width, unsigned int& height);
    // Note: returned image pointer will be invalidated after a new image is read
    unsigned char *DecodePNG(unsigned char *readBuffer, unsigned int length, unsigned int& width, unsigned int& height);

    RasterMapManager();
  };	
}
