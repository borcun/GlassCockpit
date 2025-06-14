/**
 * The base class for all objects that occupy a location on the surface of the earth
 */

#pragma once

#include <stdio.h>
#include <string>

namespace OpenGC {
  class GeographicObject {
  public:
    GeographicObject() : m_DegreeLat(0.0f), m_DegreeLon(0.0f), m_AltitudeMeters(0.0f) {}
    virtual ~GeographicObject() { }
    
    /** Set names */
    void SetIdentification(const std::string& s) { m_Identification = s; }
    void SetFullname(const std::string& s) { m_FullName = s; }
    /** Set physical parameters */
    void SetDegreeLat(float degree) {m_DegreeLat = degree;}
    void SetDegreeLon(float degree) {m_DegreeLon = degree;}
    void SetAltitudeMeters(float alt) { m_AltitudeMeters = alt; }

    /** Set mercator map coordinates */
    void SetMercatorMeters(float n, float e) {
      m_MercatorNorthingMeters = n;
      m_MercatorEastingMeters = e;
    }

    /** Get mercator map coordinates */
    void GetMercatorMeters(float &n, float &e) {n = m_MercatorNorthingMeters; e = m_MercatorEastingMeters;}
    /** Accessors for physical parameters */
    float GetAltitudeMeters() { return m_AltitudeMeters; }
    float GetDegreeLat() { return m_DegreeLat; }
    float GetDegreeLon() { return m_DegreeLon; }
    /** Accessors for IDs */
    std::string GetIdentification() { return m_Identification; }
    std::string GetFullName() { return m_FullName; };

  protected:
    /** Physical parameters */
    float m_DegreeLat, m_DegreeLon, m_AltitudeMeters;
    /** Mercator map coordinates in meters */
    float m_MercatorNorthingMeters, m_MercatorEastingMeters;
    /** Brief name, e.g. "KPIT" */
    std::string m_Identification;
    /** Full name, e.g. "Pittsburgh International Airport" */
    std::string m_FullName;
  };
}
