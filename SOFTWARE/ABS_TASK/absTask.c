#include "../TASK/TASK.h"
#include <rtx51tny.h>                 /* RTX-51 tiny functions & defines      */
#include <stdio.h>
#include <stdlib.h>
#include "../TASK/setup.h"
#include "../../HARDWARE/DEVICES/BUTTON/BUTTON.H"
#include "../../HARDWARE/DEVICES/LED/LED.H"
#include "../../HARDWARE/BSP/USART1.H"
#include "../HARDWARE/DEVICES/SENSOR/ANGLE/ANGLE.h"
#include "../COMMON_SOFTWARE/DATA_SCOPE/DataScope_DP.h"
#include "../COMMON_SOFTWARE/STORAGE/STORAGE.h"
#include "../../HARDWARE/BSP/STC15_PWM.H"
#include "../SOFTWARE/ALGORITHM/PID/PID.H"

#define INIT 0//初始化
#define BUTTON 1//按键检测
#define ANGLE 2//角度控制
#define MODE_1 3//题目一
#define MODE_2 4//题目二

void Task_Init() _task_ INIT
{
	
}

void Task_Button() _task_ BUTTON
{
	
}

void Task_Angle() _task_ ANGLE //获取角度并将角度带入pid算法中计算
{
	openPID(PID_1);
	for (;;)
	{
		PID_setActualParameter(PID_1, getAngle(PRESENT_ANGLE));//设置pid的实际参数,并读取角度
		PID(PID_1);//PID算法
		os_wait(K_IVL,10,0);//将进程周期性堵塞

	}
}

void Task_Mode_1() _task_ MODE_1
{
	
}

void Task_Mode_2() _task_ MODE_2
{
	
}