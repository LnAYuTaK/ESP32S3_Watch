#pragma once 
#include "request.h"
#include "httprequestparser.h"
using namespace httpparser;
using namespace std;
class MapProvider
{
public:
    MapProvider();
    ~MapProvider();
    //获取URL
    virtual string getTileURL(int x, 
                              int y, 
                              int zoom) = 0; 
private:
};

//Test 
#define AMAPLON 116.481485
#define AMAPLAT 39.990464
//高德地图
class AmapProvider : public MapProvider
{
public:
   AmapProvider(/* args */);
   ~AmapProvider();
   string getTileURL( int x,int y , int zoom)override;
   HttpRequestParser parse() {return this->_parser;}
private:
   HttpRequestParser _parser;
};

enum MAPTYPE
{
    AMAP,
    GOOGLEMAP,
    BINMAP
};

