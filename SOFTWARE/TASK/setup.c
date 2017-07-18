/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\SOFTWARE\TASK\SETUP.C
* 作者:     周晨阳 
* 版本:    
* 日期:     2017/07/18
* 描述:		初始化器件和测试器件使用
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
* 
***********************************************************/

#include "setup.h"
#include "../HARDWARE/DEVICES/SENSOR/ANGLE/ANGLE.h"
#include "../../HARDWARE/DEVICES/BUTTON/BUTTON.h"	
#include "../../HARDWARE/DEVICES/MOTOR/DC_MOTOR/MOTOR.h"
#include "../../HARDWARE/DEVICES/LED/LED.h"
#include "../../HARDWARE/BSP/USART1.h"
#include "../../HARDWARE/BSP/timer.h"
#include "../../HARDWARE/BSP/GPIO.h"
#include "../../HARDWARE/BSP/delay.h"
#include "../../HARDWARE/BSP/STC15_PWM.h"
#include "../../HARDWARE/DEVICES/MOTOR/STEP_MOTOR/STEP_MOTOR.h"
#include "../../HARDWARE/DEVICES/MOTOR/SERVO/SERVO.h"
#include "../../HARDWARE/DEVICES/DISPLAY/1602/LCD1602.H"
#include "../../HARDWARE/COMMON_HARDWARE/fixedPulser.h"



/*************  串口1初始化函数 *****************/
/*************************************************
* 函数名称: void    UART1_init(unsigned long BandRate)
* 描述: 串口1初始化函数
* 输入: unsigned long BandRate ：串口的波特率，请在数值后加字母"L"，防止出问题
* 输出: 调用此函数会发送一段测试语句 “ STC15w4k58s4 UART1 is open ”
* 返回值: 无
* 其他说明: 无
*************************************************/
void    UART1_init(unsigned long BandRate)
{
	COMx_InitDefine     COMx_InitStructure;
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx;
	COMx_InitStructure.UART_BRT_Use = BRT_Timer2;
	COMx_InitStructure.UART_BaudRate = BandRate;
	COMx_InitStructure.UART_RxEnable = ENABLE;
	COMx_InitStructure.BaudRateDouble = DISABLE;
	COMx_InitStructure.UART_Interrupt = ENABLE;
	COMx_InitStructure.UART_Polity = PolityHigh;
	COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31;
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;
	USART_Configuration(USART1, &COMx_InitStructure);
	// PrintString1("STC15w4k58s4's UART1 is open \r\n");   //串口测试
}
void test(void)//器件测试
{
		//stepMotor_Init (STEP_MOTOR_1,1.8f,4,6000);
	//setStepMotorWithRound(STEP_MOTOR_1,30,100);   
//	Init_Str_Motor(SERVO_1,0.5f,2.5f,180,300);
//	//Init_Str_Motor(SERVO_2,0.5f,2.5f,180,300);
//		//open_STR(SERVO_1);
//   //	set_STR_angle(SERVO_1,1);
//	    

//   for(;i<180;i++)
//	{
//	set_STR_angle(SERVO_1,i);
//  open_StepMotor(STEP_MOTOR_1);
//		delay_ms(200);
//		delay_ms(200);
//		delay_ms(200);
//	}
	//open_STR(SERVO_2);
  	int i = 0;
	GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
	PWM_InitTypeDef  PWM_InitStructure;


	GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP

	GPIO_InitStructure.Pin = GPIO_Pin_7;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);  //初始化
	P37 = 1;
	PWM_UNLOCK;
	PWM_InitStructure.PWM_GOTO_ADC = DISABLE;
	PWM_InitStructure.PWM_V_INIT = PWM_LOW;
	PWM_InitStructure.PWM_0ISR_EN = DISABLE;
	PWM_InitStructure.PWM_OUT_EN = ENABLE;
	PWM_InitStructure.PWM_UNUSUAL_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_OUT = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_ISR_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_CMP0_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_P24_EN = DISABLE;
	PWM_InitStructure.PWM_CLOCK = PWM_Clock_NT;
	PWM_InitStructure.PWM_CLOCK_DIV = 15;
	PWM_InitStructure.PWM_SELECTx_IO = PWM_SELECT_N;
	PWM_InitStructure.PWM_ISRx_EN = DISABLE;
	PWM_InitStructure.PWM_T1x_EN = DISABLE;
	PWM_InitStructure.PWM_T2x_EN = DISABLE;
	PWM_InitStructure.PWM_EN = DISABLE;
	PWM_Inilize(PWM_2, &PWM_InitStructure);
	PWM_LOCK;
	setPWM_DIV(PWM_2, 16);//16分频
	set_PWM_period(PWM_2, 50);
	set_PWM_duty(PWM_2, 0.1f);
	open_PWM_N(PWM_2);

	for (i = 100; i < 1000; i++)
	{
		set_PWM_duty(PWM_2, i / 1000.0f);
		delay_ms(200);
		delay_ms(200);
		delay_ms(200);

	}

}
void setup(void)
{
	UART1_init(115200L);
	// timerInit();
	Board_LED_Init();
	Button_config();
	ADC_config(ADC_P10, ADC_540T);
	//LCD1602_Init();
	EA = 1;
  test();

}

