/**
 * *****************************************************************************
 * @file        main.c
 * @brief
 * @author      wenbo.zhang (1992552138@qq.com)
 * @date        2024-01-23
 * @copyright   xxxx技有限公司
 * *****************************************************************************
 */
#include <stdio.h>
#include "ARMCM4.h"
#include "stdint.h"
#include <string.h>
#include <stdbool.h>
#include "sensor/temp_humi.h"
#include "sensor/co2.h"
#include "sensor/pm25.h"
#include "sensor/sensor_common.h"
#include "sensor/wifi.h"
#include <stdlib.h>
#define WORK_BOOK 0
#if 1
// #define APB2_BUS_BASE ((UInt32)0x40010000U)  
// #define GPIO_BASE (APB2_BUS_BASE + 0x0000800U)  
// #define GPIOG (GPIO_BASE + 0x00001800U)  
// #define GPIO_CTLO(gpiox) (*(volatile UInt32 *)((UInt32)(gpiox)+0x00U))  
// #define REG32(addr) ((volatile UInt32 *)(UInt32)(addr)) 
struct __FILE
{
  int handle; /* Add whatever needed */
};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
  return ITM_SendChar(ch);
}

volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY;
int fgetc(FILE *f)
{
  while (ITM_CheckChar() != 1)
    __NOP();
  return (ITM_ReceiveChar());
}
int ferror(FILE *f)
{
  /* Your implementation of ferror */
  return EOF;
}

void _ttywrch(int ch)
{
  fputc(ch, &__stdout);
}

// int __backspace()
//{
//	return 0;
// }
void _sys_exit(int return_code)
{
  while (1)
    ; /* endless loop */
}
#endif

float GetTemCofHmi(void)
{
  return 1.2f;
}
void ParaseCfgParam(CfgParam *cfgParam)
{
  if(cfgParam->paramType == 1) // 温度传感器校准系数
  {
    float *tempCof = (float *)cfgParam->value;
    printf("*tempCof = %f",*tempCof);
    SetTemCof(*tempCof);
  }
}
typedef struct
{
    uint8_t id;
    uint8_t humi;
    float temp;
} TempHumiSensor1;

void Version(void)
{
  const char version[] = {"SF_20240930_0.01"};
  printf("SF_Version:%s\r\n",version);
}
SInt32 Sum(SInt32 a, SInt32 b)
{
    return a + b;
}
void Handle(SInt32 (*pSum)(SInt32 a, SInt32 b))
{
    SInt32 sum = (*pSum)(1,2);
    printf("sum = %d\r\n",sum);
}
typedef SInt32 (*PFUNC)(SInt32 a, SInt32 b);
void g_Handle(PFUNC psum)
{
    SInt32 sum = (*psum)(3,4);
    printf("sum = %d\r\n",sum);
}
#define testAddr (*(UInt32 *)0x20000400)

char *strcpyTest(char dest[],char src[])
{
    UInt32 index = 0;
    while(src[index] != '\0')
    {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}

typedef struct TempHumiListNode_t
{
    UInt8 id;
    UInt8 humi;
    float temp;
    struct TempHumiListNode_t *next;
    struct TempHumiListNode_t *prev;
}TempHumiListNode;

/**
 * @brief       初始化传感器及返回头节点的地址
 * 
 * @return      TempHumiListNode* 
 */
TempHumiListNode *InitSensorList(void)
{
    TempHumiListNode *header = (TempHumiListNode *)malloc(sizeof(TempHumiListNode));
    if(header == NULL)
    {
        return NULL;
    }
    header->id = 0;
    header->next = header;
    header->prev = header;
    return header;
}

/**
 * @brief       寻找传感器
 * 
 * @return      TempHumiListNode* 
 */
TempHumiListNode *FindTempHumiSensor(void)
{
    TempHumiListNode *note = (TempHumiListNode *)malloc(sizeof(TempHumiListNode));
    if(note == NULL)
    {
        return NULL;
    }
    static UInt8 l_SensorId_ui8 = 100;
    note->id = l_SensorId_ui8;
    l_SensorId_ui8--;
    note->temp = 20.5f;
    note->humi = 40;
    return note;
}

void AddSensorNode(TempHumiListNode *header, TempHumiListNode *node)
{
    #if 0
    TempHumiListNode *current = header;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = node;
    node->next = NULL;
    #else
    TempHumiListNode *prev = header;
    TempHumiListNode *current = header->next;
    while(current != NULL)
    {
        prev = current;
        current = current->next;
    }
    prev->next = node;
    node->next = NULL;
    #endif
}

void PrintSensorData(TempHumiListNode *header)
{
    TempHumiListNode *current;
    current = header->next;
    while(current != NULL)
    {
        printf("Sensor id:%d,temp = %.1f,humi = %d.\r\n",
                current->id,current->temp,current->humi);
        current = current->next;
    }
}

void DelSensorNode(TempHumiListNode *header,UInt8 id)
{
    TempHumiListNode *prev = header;
    TempHumiListNode *current = header->next;
    while(current != NULL)
    {
        if(current->id == id)
        {
            break;
        }
        prev = current;
        current = current->next;
    }
    if(current == NULL)
    {
        printf("Can not find sensor.\r\n");
    }
    prev->next = current->next;
    free(current);
    current = NULL;
}

void AddNode(TempHumiListNode *oldNote, TempHumiListNode *newNote)
{
    newNote->next = oldNote->next;
    newNote->prev = oldNote;
    oldNote->next->prev = newNote;
    oldNote->next = newNote;
}

void AddNoteToHead(TempHumiListNode *header, TempHumiListNode *node)
{
    AddNode(header,node);
}

void AddNoteToTail(TempHumiListNode *header, TempHumiListNode *node)
{
    AddNode(header->prev,node);
}

void PrintSensorDataDouble(TempHumiListNode *header)
{
    TempHumiListNode *current;
    current = header->next;
    printf("\n*****printf list began*****!\n");
    if(current == header)
    {
        printf("List has no node!\r\n");
        return;
    }
    while(current != header)
    {
        printf("SensorDouble id:%d,temp = %.1f,humi = %d.\r\n",
                current->id,current->temp,current->humi);
        current = current->next;
    }
    printf("\n*****printf list end*****!\n");
}

void DelDataDouble(TempHumiListNode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void DelSensorNodeDouble(TempHumiListNode *header, UInt8 id)
{
    TempHumiListNode *current;
    current = header->next;
    while(current != header)
    {
        if(current->id == id)
        {
            break;
        }
        current = current->next;
    }
    if(current == header)
    {
        printf("Can not find sensor %d.\n",id);
    }
    DelDataDouble(current);
    free(current);
    current = NULL;
}

/**
 * @brief       通用链表结构体
 * 
 */
typedef struct List
{
    struct List *prev;
    struct List *next;
}List;

/**
 * @brief       初始化通用链表
 * 
 * @param       header ：通用链表头节点
 */
void InitList(List *header)
{
    header->prev = header;
    header->next = header;
}

/**
 * @brief       将节点添加到已有节点的后面
 * 
 * @param       oldNote :已有节点
 * @param       newNote :待添加节点
 */
void AddNote(List *oldNote, List *newNote)
{
    newNote->next = oldNote->next;
    newNote->prev = oldNote;
    oldNote->next->prev = newNote;
    oldNote->next = newNote;
}

/**
 * @brief       将节点添加到链表尾部
 * 
 * @param       header ：头节点
 * @param       note ：待添加节点
 */
void AddNoteToTailGeneral(List *header, List *note)
{
    AddNote(header->prev,note);
}

/**
 * @brief       将节点添加到头节点的后面
 * 
 * @param       header ：头节点
 * @param       note ：待添加节点
 */
void AddNodeTohead(List *header, List *note)
{
    AddNote(header,note);
}

static List *g_tempHumiHeader;

typedef struct TempHumiSensorGeneral
{
    UInt8 id;
    UInt8 humi;
    float temp;
    List list;
}TempHumiSensorGeneral;

/**
 * @brief       初始化
 * 
 * @return      true 
 * @return      false 
 */
bool InitTempHumiSensor(void)
{
    g_tempHumiHeader = (List *)malloc(sizeof(List));
    if(g_tempHumiHeader == NULL)
    {
        return FALSE;
    }
    InitList(g_tempHumiHeader);
    return TRUE;
}
static TempHumiListNode *g_hander;

/**
 * @brief       寻找传感器
 * 
 * @return      TempHumiSensorGeneral* 
 */
TempHumiSensorGeneral *FindTempHumiSensorGeneral(void)
{
    TempHumiSensorGeneral *sensor = (TempHumiSensorGeneral *)(malloc(sizeof(TempHumiSensorGeneral)));
    if(sensor == NULL)
    {
        return NULL;
    }
    static UInt8 id = 100;
    sensor->id = id;
    id--;
    sensor->humi = 40;
    sensor->temp = 20.5f;
    return sensor;
}

/**
 * @brief       添加传感器，如温湿度传感器或者CO2传感器，如果用到CO2传感器只需要更新1个类似函数即可
 * 
 * @param       sensor 
 */
void AddTempHumiSensor(TempHumiSensorGeneral *sensor)
{
    AddNoteToTailGeneral(g_tempHumiHeader,&sensor->list);
}


int main(void)
{
    if(!InitTempHumiSensor())
    {
        return -1;
    }
    TempHumiSensorGeneral *l_sensor;
    for(UInt8 i = 0; i < 3; i++)
    {
        l_sensor = FindTempHumiSensorGeneral();
        if(l_sensor == NULL)
        {
            continue;
        }
        AddTempHumiSensor(l_sensor);
    }
    g_hander = InitSensorList();
    if(g_hander == NULL)
    {
        return -1;
    }
     TempHumiListNode *node;
    // for(UInt8 i = 0; i < 3; i++)
    // {
    //     node = FindTempHumiSensor();
    //     if(node == NULL)
    //     {
    //         continue;
    //     }
    //     AddSensorNode(g_hander,node);
    // }
    // PrintSensorData(g_hander);
    // DelSensorNode(g_hander,100);
    // DelSensorNode(g_hander,98);
    // PrintSensorData(g_hander);
    // for (UInt8 i = 0; i < 3; i++)
    // {
    //     node = FindTempHumiSensor();
    //     if (node == NULL)
    //     {
    //         continue;
    //     }
    //     AddSensorNode(g_hander, node);
    // }
    // PrintSensorData(g_hander);
    for(UInt8 i = 0; i < 3; i++)
    {
        node = FindTempHumiSensor();
        if (node == NULL)
        {
            continue;
        }
        AddNoteToHead(g_hander,node);
    }
    PrintSensorDataDouble(g_hander);

    node = FindTempHumiSensor();
    AddNoteToTail(g_hander,node);

    node = FindTempHumiSensor();
    AddNoteToHead(g_hander,node);
    PrintSensorDataDouble(g_hander);
    
    DelSensorNodeDouble(g_hander,97);
    DelSensorNodeDouble(g_hander,96);
    PrintSensorDataDouble(g_hander);
#if WORK_BOOK
    // 第五章，多个鞋码对应的脚长,
    const float SCALE  = 0.3333f;
    const float ADJUST = 7.31f;
    UInt8 shoe       = 0; // 鞋码
    while (shoe < 20)
    {
        foot[shoe] = shoe * SCALE + ADJUST; // 不同的鞋码输出20只脚
        shoe++;
    }
#else
    /*值传递：函数传什么值就是什么值，而函数内部的数据不被修改，通过外部的值来赋予形参真实的数据。
    地址传递：函数传什么地址的数据不影响内部数据的输出，还是取内部数据，外部数据不影响内部数据的计算。*/
    #if 0
    testAddr = 0x12345678;
    testAddr++;
    UInt32 l_a = 0x1413061D;
    volatile UInt8 *l_b;
    l_b = (UInt8*)&l_a;
    UInt8 day = *l_b;
    printf("l_b = %#X.\n",day);
    l_b++;
    UInt8 month = *l_b;
    printf("l_b1 = %#X.\n",month);
    l_b++;
    UInt8 year_low = *l_b;
    printf("l_b2 = %#X.\n",year_low);
    l_b++;
    UInt8 year_high = *l_b;
    printf("l_b3 = %#X.\n",year_high);
    printf("testAddr = 0x%#x.\n",testAddr);
    float tempData = 1.0f;
    UInt8 humiData = 5;
    UInt32 sensorId12 = 0x1234;
    GetTempHumi(&sensorId12,&tempData,&humiData);
    printf("Sensor = %#x,tempData = %0.1f,humiData = %d\r\n", 
            sensorId12, tempData, humiData);
    #endif
    #if 0
    TempHumiSensor1 tempHumiData;
    TempHumiSensor1 *tempHumiPtr;
    tempHumiPtr = &tempHumiData;
    tempHumiPtr->temp = 20.5f;
    (*tempHumiPtr).temp = 21.5f;
    printf("&tempHumiData = 0x%p,&tempHumiPtr = 0x%p\r\n", 
            &tempHumiData, &tempHumiPtr);
    printf("&tempHumiData.temp = 0x%p,&tempHumiPtr->temp = 0x%p\r\n", 
            &tempHumiData.temp, &tempHumiPtr->temp);
    #endif
    char *src = "malloc for m failed.";
    char dest[sizeof(*src)];
    strcpyTest(dest,src);
    printf("dest = %s,src = %d\n",dest,sizeof(*src));
    AirQuality airQualdata;
    AirQuality *airQualdata1; 
    printf("sizeof(airQualdata) = %d,sizeof(*airQualdata1) = %d\r\n",sizeof(airQualdata),sizeof(airQualdata1));
//    TempHumiSensor tempHumiData;
    airQualdata.tempHumiData.id = 0x1234;
    GetTempHumi(&airQualdata.tempHumiData);
    airQualdata.co2Level = GetCo2Level();
    airQualdata.pm25Level = GetPm25Level();
    printf("ID = %d,temp = %0.1f,humi = %d\r\n",
            airQualdata.tempHumiData.id,airQualdata.tempHumiData.temp,airQualdata.tempHumiData.humi);
    UInt8 l_buffer[5] = {3,2,1,5,4};
    // float l_buffer1[5] = {3,2,1,5,4};
    float getTem_flt = 0;
    //float l_data_flt = CalRawAvg(l_buffer1,5);
    getTem_flt = GetcelTem(airQualdata.tempHumiData.id);
    printf("getTem_flt = %.1f\r\n",getTem_flt);
//    printf("l_data_flt = %.1f\r\n",l_data_flt);
    printf("&l_buffer = %p\r\n",l_buffer);
    for(UInt8 i = 0; i < 5; i++)
    {
        printf("&l_buffer[%d] = %p,l_buffer[%d] = %d\r\n",i,&l_buffer[i],i,l_buffer[i]);
    }
    for(UInt8 i = 0; i < 5; i++)
    {
        printf("l_buffer[%d] = %d\r\n",i,*(l_buffer +i));
    }
    UInt8 *l_ptr;
    l_ptr = l_buffer;
    printf("l_ptr = %p\r\n",l_ptr);
    for(UInt8 j = 0; j < 5; j++)
    {
        printf("j = %d,&l_ptr = %p,l_ptr = %d\r\n",j,(l_ptr + j),(*(l_ptr + j)));
    }
    for(UInt8 k = 0; k < 5; k++)
    {
        printf("k = %d,&l_ptr = %p,l_ptr = %d\r\n",k,(&l_ptr[k]),l_ptr[k]);
    }
    float f = 1.2f;
    UInt8 *p;
    p = (UInt8 *)&f;
    printf("*p = %#x.\n",*p);
    p++;
    printf("*p = %#x.\n",*p);
    p++;
    printf("*p = %#x.\n",*p);
    p++;
    printf("*p = %#x.\n",*p);
    UInt8 value[4] = {0x9A,0x99,0x99,0x3F};
    float *sum;
    sum = (float *)value;
    printf("*sum = %f\n",*sum);
    // pSum = Sum;
    // printf("pSum = 0x%p,Sum = 0x%p\r\n",pSum,Sum);
    // SInt32 sum1 = (*pSum)(1, 2);
    // printf("sum = %d\r\n",sum1);
    Handle(Sum);
    g_Handle(Sum);
    CreatWifiCb(ParaseCfgParam);
    WifiHandler();
    UInt32 *l_p = (UInt32 *)malloc(4);
    l_p[0] = 0x12345678;
    free(l_p);
    CfgParam CfgParam1;
    printf("sizeof(CfgParam1) = %d\r\n",sizeof(CfgParam1));
    printf("&pramType = 0x%p,&value = 0x%p,&size = 0x%p\r\n", &CfgParam1.paramType,
           &CfgParam1.value, &CfgParam1.size);
    CfgParam1.value = (UInt8 *)malloc(5);
    CfgParam1.value[0] = 0x01;
    CfgParam1.value[1] = 0x02;
    CfgParam1.value[2] = 0x03;
    CfgParam1.value[3] = 0x04;
    CfgParam1.value[4] = 0x05;
    char fmt[] = "malloc for m failed!\r\n";
    printf("strlen = %d\r\n",strlen(fmt));
    fmt[0] = 'M';
    printf("fmt[0] = %c,fmt[1] = %c,fmt[2] = %c\r\n",
    fmt[0],fmt[1],fmt[2]);
    Version();
#endif
    return 0;
}

