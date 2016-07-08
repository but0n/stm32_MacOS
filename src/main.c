/*************************************************************************************
* Test-program for Olimex “STM32-H103”, header board for “STM32F103RBT6”.
* After program start green LED (LED_E) will blink.
*
* Program has to be compiled with optimizer setting "-O0".
* Otherwise delay via while-loop will not work correctly.
*************************************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"

#define SYSVCC 330 //单片机系统电压, ADC基准电压
#define TIMES 16
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
//      第一路数码管连接的端口以及各个引脚
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
#define LED0_PORT GPIOA

#define LED0_PIN_a GPIO_Pin_0
#define LED0_PIN_b GPIO_Pin_1
#define LED0_PIN_c GPIO_Pin_2
#define LED0_PIN_d GPIO_Pin_3
#define LED0_PIN_e GPIO_Pin_4
#define LED0_PIN_f GPIO_Pin_5
#define LED0_PIN_g GPIO_Pin_6
#define LED0_PIN_h GPIO_Pin_7
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
//      第二路数码管连接的端口以及各个引脚
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
#define LED1_PORT GPIOB

#define LED1_PIN_a GPIO_Pin_8
#define LED1_PIN_b GPIO_Pin_9
#define LED1_PIN_c GPIO_Pin_10
#define LED1_PIN_d GPIO_Pin_11
#define LED1_PIN_e GPIO_Pin_12
#define LED1_PIN_f GPIO_Pin_13
#define LED1_PIN_g GPIO_Pin_14
#define LED1_PIN_h GPIO_Pin_15


#define NUM_CLR(port) GPIO_ResetBits((port), GPIO_Pin_All)  //关闭数码管

//  数码管bit map
unsigned int numberMap[2][10] = {
    {
        LED0_PIN_a | LED0_PIN_b | LED0_PIN_c | LED0_PIN_d | LED0_PIN_e | LED0_PIN_f,
        LED0_PIN_b | LED0_PIN_c,
        LED0_PIN_a | LED0_PIN_b | LED0_PIN_g | LED0_PIN_e | LED0_PIN_d,
        LED0_PIN_a | LED0_PIN_b | LED0_PIN_g | LED0_PIN_c | LED0_PIN_d,
        LED0_PIN_f | LED0_PIN_g | LED0_PIN_b | LED0_PIN_c,
        LED0_PIN_a | LED0_PIN_f | LED0_PIN_g | LED0_PIN_c | LED0_PIN_d,
        LED0_PIN_a | LED0_PIN_f | LED0_PIN_e | LED0_PIN_d | LED0_PIN_c | LED0_PIN_g,
        LED0_PIN_a | LED0_PIN_b | LED0_PIN_c,
        LED0_PIN_a | LED0_PIN_b | LED0_PIN_c | LED0_PIN_d | LED0_PIN_e | LED0_PIN_f | LED0_PIN_g,
        LED0_PIN_a | LED0_PIN_b | LED0_PIN_c | LED0_PIN_d | LED0_PIN_f | LED0_PIN_g
    },
    {
        LED1_PIN_a | LED1_PIN_b | LED1_PIN_c | LED1_PIN_d | LED1_PIN_e | LED1_PIN_f,
        LED1_PIN_b | LED1_PIN_c,
        LED1_PIN_a | LED1_PIN_b | LED1_PIN_g | LED1_PIN_e | LED1_PIN_d,
        LED1_PIN_a | LED1_PIN_b | LED1_PIN_g | LED1_PIN_c | LED1_PIN_d,
        LED1_PIN_f | LED1_PIN_g | LED1_PIN_b | LED1_PIN_c,
        LED1_PIN_a | LED1_PIN_f | LED1_PIN_g | LED1_PIN_c | LED1_PIN_d,
        LED1_PIN_a | LED1_PIN_f | LED1_PIN_e | LED1_PIN_d | LED1_PIN_c | LED1_PIN_g,
        LED1_PIN_a | LED1_PIN_b | LED1_PIN_c,
        LED1_PIN_a | LED1_PIN_b | LED1_PIN_c | LED1_PIN_d | LED1_PIN_e | LED1_PIN_f | LED1_PIN_g,
        LED1_PIN_a | LED1_PIN_b | LED1_PIN_c | LED1_PIN_d | LED1_PIN_f | LED1_PIN_g
    }
};

//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
//      函数名:         delay
//      功能描述:       延时ms
//      输入参数:       nCount: 延时的时间，单位是ms
//      返回值:         无
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
void delay(volatile unsigned int nCount) {
    for(nCount*=12000; nCount != 0; nCount--); //delay ms
}
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
//      函数名:         delayUs
//      功能描述:       延时us
//      输入参数:       time(16bit):   延时的时间，单位是us
//      返回值:         无
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
void delayUs(unsigned short time) {
    unsigned short i=0;
    while(time--) {
        i=10;
        while(i--);
  }
}
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
//      函数名:         LED_Config
//      功能描述:       配置所需的GPIO
//      输入参数:       无
//      返回值:         无
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
void LED_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    //使能数码管所需要的GPIO端口时钟

    GPIO_InitTypeDef GPIO_InitStructure;    //定义GPIO初始化结构体变量
    //所使用的引脚
    GPIO_InitStructure.GPIO_Pin =   LED0_PIN_a | LED0_PIN_b | LED0_PIN_c | LED0_PIN_d | LED0_PIN_e | LED0_PIN_f | LED0_PIN_g | LED0_PIN_h;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;   //推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //最高输出速率 50MHz
    GPIO_Init(LED0_PORT, &GPIO_InitStructure);          //初始化第一路的数码管

    GPIO_InitStructure.GPIO_Pin =   LED1_PIN_a | LED1_PIN_b | LED1_PIN_c | LED1_PIN_d | LED1_PIN_e | LED1_PIN_f | LED1_PIN_g | LED1_PIN_h;
    GPIO_Init(LED1_PORT, &GPIO_InitStructure);          //初始化第二路的数码管
}

void adc_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | RCC_APB2Periph_GPIOB, ENABLE);
    //使能芯片内部数模转换以及读取电压用的IO口时钟
    GPIO_InitTypeDef GPIO_InitStructure;    //初始化两路的IO口
    GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_1 | GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AIN;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //初始化并使能ADC1的通道9, 该通道使用的IO口是B1
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode =                ADC_Mode_Independent;//ADC1 和 ADC2 工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode =        DISABLE;//禁用了模数转换工作的扫描模式（多通道）
    ADC_InitStructure.ADC_ContinuousConvMode =  ENABLE;//使模数转换工作在连续模式
    ADC_InitStructure.ADC_ExternalTrigConv =    ADC_ExternalTrigConv_None;//模数转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign =           ADC_DataAlign_Right;//ADC 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel =        1;//进行规则转换的 ADC 通道的数目
    ADC_Init(ADC1, &ADC_InitStructure);             //按照以上配置初始化 ADC1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_1Cycles5);
    //设置 ADC1 的规则组通道，设置它们的转化顺序和采样时间

    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    //初始化并使能ADC2的通道8, 该通道使用的IO口是B0
    ADC_InitStructure.ADC_Mode =                ADC_Mode_Independent;//ADC1 和 ADC2 工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode =        DISABLE;//禁用了模数转换工作的扫描模式（多通道）
    ADC_InitStructure.ADC_ContinuousConvMode =  ENABLE;//使模数转换工作在连续模式
    ADC_InitStructure.ADC_ExternalTrigConv =    ADC_ExternalTrigConv_None;//模数转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign =           ADC_DataAlign_Right;//ADC 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel =        1;//进行规则转换的 ADC 通道的数目
    ADC_Init(ADC2, &ADC_InitStructure);             //按照以上配置初始化 ADC2
    ADC_RegularChannelConfig(ADC2, ADC_Channel_8, 1, ADC_SampleTime_1Cycles5);
    //设置 ADC2 的规则组通道，设置它们的转化顺序和采样时间

    ADC_Cmd(ADC2, ENABLE);
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);
}
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
//      函数名:         adc_read
//      功能描述:       读取16次adc数据, 取平均值
//      输入参数:       pin(8bit):选择通道 1或0
//      返回值:         返回读取的数据 (16bit)
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
unsigned short adc_read(unsigned char pin) {
    unsigned short data = 0;

    unsigned char count;
    for (count = 0; count < TIMES; count++) {
        if(pin) {
            while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//等待信号
            data += ADC_GetConversionValue(ADC1);//读取并累加
        }
        else {
            while(ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);//等待信号
            data += ADC_GetConversionValue(ADC2);//读取并累加
        }
    }
    data >>= 4;//除以16

    return data;
}
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
//      函数名:         display
//      功能描述:       显示数据
//      输入参数:       两路的数值: value0(32bit), value1(32bit)
//      返回值:         无
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
void display(unsigned int value0, unsigned int value1) {

    unsigned char num_bit[2][3] = {{0,0,0}, {0,0,0}};


    num_bit[0][0] = value0 / 100;       //百位
    num_bit[0][1] = value0 % 100 / 10;  //十位
    num_bit[0][2] = value0 % 10;        //各位

    num_bit[1][0] = value1 / 100;
    num_bit[1][1] = value1 % 100 / 10;
    num_bit[1][2] = value1 % 10;

    unsigned char num_length;
    for(num_length = 0; num_length < 3; num_length++) { //分别显示三位, 第一位带小数点
        NUM_CLR(LED1_PORT);
        NUM_CLR(LED0_PORT);
        delay(200);
        GPIO_SetBits(LED0_PORT, numberMap[0][num_bit[0][num_length]]);
        GPIO_SetBits(LED1_PORT, numberMap[1][num_bit[1][num_length]]);
        if(!num_length) {
            GPIO_SetBits(LED0_PORT, LED0_PIN_h);
            GPIO_SetBits(LED1_PORT, LED1_PIN_h);
        }
        delay(300);
    }
    NUM_CLR(LED0_PORT);
    NUM_CLR(LED1_PORT);
    GPIO_SetBits(LED0_PORT, LED0_PIN_g);    //结束标志
    GPIO_SetBits(LED1_PORT, LED1_PIN_g);    //结束标志
    delay(400);

}

int main() {
	LED_Config();      //初始化数码管
    adc_Config();      //初始化数模转换片上外设
    GPIO_SetBits(LED0_PORT, numberMap[0][8]);   //测试数码管连接是否有异常
    GPIO_SetBits(LED1_PORT, numberMap[1][8]);
    delay(500);

    while (1) {
        unsigned short data0 = adc_read(0);     //读取adc数据
        data0 = (unsigned int)(((unsigned int)data0)*SYSVCC>>12);  //处理数据, 将读到的数据映射在0到330的范围中 (ADC分辨率为12位)
        unsigned short data1 = adc_read(1);
        data1 = (unsigned int)(((unsigned int)data1)*SYSVCC>>12);
        display(data0 , data1);

    }

}
