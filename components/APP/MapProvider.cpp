#include "MapProvider.h"
#include "APP_Config.h"
MapProvider::MapProvider(/* args */)
{
}
//******************************************************
MapProvider::~MapProvider()
{
    
}
//******************************************************
AmapProvider::AmapProvider()
    :MapProvider()
{
}
//******************************************************
AmapProvider::~AmapProvider()
{

}
//******************************************************
string AmapProvider::getTileURL(int x,int y ,int zoom)
{
  string baseHost = "https://restapi.amap.com/v3/staticmap?location=";
  string location = to_string(x)+ "," + to_string(y)+ "&zoom=";
  string zoomStr  = to_string(zoom)+"&size=15*15&markers=mid,,A:";
  string pos      = to_string(x)+ "," + to_string(y);
  string key      = "&key="+ string(MAPKEY);
  string titleURL = baseHost + location + zoomStr + pos + key;
  return titleURL;
}