#include "wifi.h"
#include <stdlib.h>
// static CfgParam g_cfgParam;
static CbFunc g_cb;
static SInt8 ReceiveWifiData(CfgParam *g_cfgParam)
{
    g_cfgParam->paramType = 1; // 温度传感器校准系数
    g_cfgParam->size = 4;
    g_cfgParam->value = (UInt8 *)malloc(g_cfgParam->size);
    if(g_cfgParam->value == NULL)
    {
        return -1;
    }
    g_cfgParam->value[0] = 0x9A;
    g_cfgParam->value[1] = 0x99;
    g_cfgParam->value[2] = 0x99;
    g_cfgParam->value[3] = 0x3F;
    return 0;
}

void CreatWifiCb(CbFunc cbFunc)
{
    g_cb = cbFunc;
}
void WifiHandler(void)
{
    CfgParam *cfgParam;
    cfgParam = (CfgParam *)malloc(sizeof(CfgParam));
    if(cfgParam == NULL)
    {
        return;
    }
    if(ReceiveWifiData(cfgParam) != 0)
    {
        free(cfgParam);
        cfgParam = NULL;
        return;
    }
    (*g_cb)(cfgParam);
    free(cfgParam->value);
    cfgParam->value = NULL;
    free(cfgParam);
    cfgParam = NULL;
}
