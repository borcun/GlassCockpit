#include "albatross_data_source.h"
#include "debug.h"

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

bool OpenGC::AlbatrossDataSource::open(void) {
  return true;
}

bool OpenGC::AlbatrossDataSource::onIdle(void) {
    // FIXME actually get data (duh!)
    return false; // should be true once data is coming in
}
