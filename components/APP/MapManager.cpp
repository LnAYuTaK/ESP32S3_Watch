#include "MapManager.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "MapProvider.h"
#include "freertos/task.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "ff.h"

#include "esp_tls.h"
#include "esp_crt_bundle.h"

#include "HAL_Manager.h"
#include <fstream>
#include <stdio.h >
#include <iostream>

#include "HttpResponseParser.h"
using namespace httpparser;
using namespace std;

#define UrlReq "https://restapi.amap.com/v3/staticmap?location=116.481485,39.990464&zoom=10&size=100*100&markers=mid,,A:116.481485,39.990464&key=92c5ae34b6cd89cd935056692d84cddb"
#define SERVER  "restapi.amap.com"

static const char REQUEST[] ="GET " UrlReq " HTTP/1.1\r\n"
                             "Host: "SERVER"\r\n"
                             "User-Agent: esp-idf/1.0 esp32\r\n"
                             "\r\n";
const static char * TAG  = "MAPServer" ;
MapManager::MapManager(Application* app, ModuleBox* moduleBox)
    :Module(app, moduleBox)
    ,_positionMgr(nullptr)
    ,_provide(nullptr)
{
  //Test
  this->setMapProvider(nullptr);
}
//******************************************************
MapManager::~MapManager()
{ 

     
}
//******************************************************
//切换不同的地图
void MapManager::setMapProvider(MapProvider *mapProvider)
{
    this->_provide = new AmapProvider();
}
//******************************************************
//这里负责连接所需要的HAL层或者APP层组件
esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{

 return ESP_OK;
}
//******************************************************
static void https_get_request(esp_tls_cfg_t cfg)
{
    char buf[8092*2];
    int ret, len;
    struct esp_tls *tls = esp_tls_conn_http_new(UrlReq, &cfg);
    if (tls != NULL) 
    {
        ESP_LOGW(TAG, "Connection established...");
    } else {
        ESP_LOGW(TAG, "Connection failed...");
         esp_tls_conn_delete(tls);  
    }
    size_t written_bytes = 0;
    do {
        ret = esp_tls_conn_write(tls,
                                 REQUEST + written_bytes,
                                 sizeof(REQUEST) - written_bytes);
        if (ret >= 0) {
            ESP_LOGI(TAG, "%d bytes written", ret);
            written_bytes += ret;
        } else if (ret != ESP_TLS_ERR_SSL_WANT_READ  && ret != ESP_TLS_ERR_SSL_WANT_WRITE) {
            ESP_LOGE(TAG, "esp_tls_conn_write  returned: [0x%02X](%s)", ret, esp_err_to_name(ret));
            esp_tls_conn_delete(tls);
        }
    } while (written_bytes < sizeof(REQUEST));
    ESP_LOGI(TAG, "Reading HTTP response...");
    do {
        len = sizeof(buf) - 1;
            bzero(buf, sizeof(buf));
        ret = esp_tls_conn_read(tls, (char *)buf, len);
        if (ret == ESP_TLS_ERR_SSL_WANT_WRITE  || ret == ESP_TLS_ERR_SSL_WANT_READ) {
            continue;
        }
        if (ret < 0) {
            ESP_LOGE(TAG, "esp_tls_conn_read  returned [-0x%02X](%s)", -ret, esp_err_to_name(ret));
            break;
        }
        if (ret == 0) {
            ESP_LOGI(TAG, "connection closed");
            break;
        }
        len = ret;
        ESP_LOGI(TAG, "%d bytes read", len);
        Response response;
        HttpResponseParser parser;
        HttpResponseParser::ParseResult res = parser.parse(response, buf, buf + len);
        if( res == HttpResponseParser::ParsingCompleted )
        {
            cout << response.inspect() << endl;
            ofstream pngfile;
            
            pngfile.open("/SD/test.png",ios::binary|ios::out);
            for (auto c : response.content)
            {
                pngfile << c;
            }
            pngfile.close();
        }
    } while (1);
}
//******************************************************
static void MapTask(void *arg)
{  
    esp_tls_cfg_t configTls = {};
    configTls.crt_bundle_attach = esp_crt_bundle_attach,
    https_get_request(configTls);
    //CAll MapUpdata
    vTaskDelete(NULL);
}
void MapManager::setModuleBox(ModuleBox * moduleBox)
{
    // MapTask();
    //这里负责连接所需要的HAL层或者APP层组件
    xTaskCreate(&MapTask,
                         "Map",
                         1024*20,
                         NULL,
                         7,
                         NULL);
}








