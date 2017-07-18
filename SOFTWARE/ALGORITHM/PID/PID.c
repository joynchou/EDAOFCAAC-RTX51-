/************************************************************
* 组织名称：电子大赛小组
* 文件名称: PID.c
* 作者:     电子大赛小组
* 版本 :    1.0
* 日期:     10/06/17
* 描述:
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
***********************************************************/

#include "PID.h"
#define PID_ALG
#ifdef PID_ALG
#include <math.h>
#define  INTEGRAL_SEPARATE //使用积分分离法

//pid算法的静态结构体

typedef  struct
{
	float setParameter;//设定角度值
	float actualParameter;//实际角度值
	float err;//偏差值
	float err_last;//上一次偏差值
	float Kp;
	float Ki;
	float Kd;//比例，积分，微分系数
	float integral;//积分值,位置式pid算法
	float output;  //实际输出因子
	float Ki_temp;//保存pid三个参数的静态变量
	float Kp_temp;//保存pid三个参数的静态变量
	float Kd_temp; //保存pid三个参数的静态变量
	float parameterUpperLimit;//参数上限
	float parameterInferiorLimit;//参数下限
	u8 state;//pid工作状态
} pid_info;

static pid_info g_pid_n_info[PID_NUM];

/*************************************************
* 函数名称:PID_config
* 描述: pid初始化函数
* 输入:u8 PID_N, float kp, float ki, float kd
* 输出:
* 返回值:
* 其他说明:
*************************************************/
void PID_config(u8 PID_N, float kp, float ki, float kd)//pid算法初始化函数，参数是三个，PID
{
	g_pid_n_info[PID_N].err = 0;
	g_pid_n_info[PID_N].err_last = 0;
	g_pid_n_info[PID_N].output = 0;
	g_pid_n_info[PID_N].integral = 0;
	g_pid_n_info[PID_N].Kp = kp;
	g_pid_n_info[PID_N].Ki = ki;
	g_pid_n_info[PID_N].Kd = kd;
	g_pid_n_info[PID_N].Kp_temp = g_pid_n_info[PID_N].Kp;
	g_pid_n_info[PID_N].Ki_temp = g_pid_n_info[PID_N].Ki;
	g_pid_n_info[PID_N].Kd_temp = g_pid_n_info[PID_N].Kd;
}
//************************************
// Method:    openPID
// FullName:  openPID
// Access:    public 
// Returns:   void
// Qualifier: 打开pid
// Parameter: u8 PID_N
//************************************
void openPID(u8 PID_N)
{
	g_pid_n_info[PID_N].state = ON;
	//add the code here
}
//************************************
// Method:    closePID
// FullName:  closePID
// Access:    public 
// Returns:   void
// Qualifier:关闭pid
// Parameter: u8 PID_N
//************************************
void closePID(u8 PID_N)
{
	g_pid_n_info[PID_N].state = OFF;
	//add the code here

}
//************************************
// Method:    PID
// FullName:  PID
// Access:    public 
// Returns:   bit
// Qualifier: 设置好参数后使用此函数进行pid运算，之后使用get**函数获取计算后的值，需要先打开pid再使用此函数
// Parameter: u8 PID_N
//************************************
bit PID(u8 PID_N)
{


	if (g_pid_n_info[PID_N].state)
	{

		g_pid_n_info[PID_N].err = g_pid_n_info[PID_N].setParameter - g_pid_n_info[PID_N].actualParameter;
		//#ifdef  INTEGRAL_SEPARATE //是否使用积分分离法
		//  if(abs(pid.err)<15.0f)//积分分离法，防止误差过大时积分累积过大造成震荡，同时减小比例和微分
		//    {
		//      pid.Ki        =        Ki_temp;
		//      pid.integral  +=       pid.err;
		//      pid.Kp        =        Kp_temp-0.7f;
		//      pid.Kd        =        Kd_temp-0.5f;
		//    }
		//  else//误差过大时去除积分项和累计误差 ，仅使用比例和微分 ，同时在原基础上加大微分的作用
		//    {
		//      pid.Ki        =        0;
		//      pid.integral  =        0;
		//      pid.Kd        =        Kd_temp+0.5f;
		//    }
		//#else
		g_pid_n_info[PID_N].integral += g_pid_n_info[PID_N].err;
		//#endif
		//PID算法核心
		g_pid_n_info[PID_N].output  = g_pid_n_info[PID_N].Kp*g_pid_n_info[PID_N].err		  \
									+ g_pid_n_info[PID_N].Ki*g_pid_n_info[PID_N].integral     \
									+ g_pid_n_info[PID_N].Kd*(g_pid_n_info[PID_N].err - g_pid_n_info[PID_N].err_last);
		g_pid_n_info[PID_N].err_last = g_pid_n_info[PID_N].err;


		return 1;
	}

}
//************************************
// Method:    setParameterInferiorLimit
// FullName:  setParameterInferiorLimit
// Access:    public 
// Returns:   void
// Qualifier: 设置输入数值下限
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setParameterInferiorLimit(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].parameterInferiorLimit = value;
}

//************************************
// Method:    setParameterUpperLimit
// FullName:  setParameterUpperLimit
// Access:    public 
// Returns:   void
// Qualifier: 设置输入数值上限
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setParameterUpperLimit(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].parameterUpperLimit = value;

}

//************************************
// Method:    setActualParameter
// FullName:  setActualParameter
// Access:    public 
// Returns:   void
// Qualifier: 设置实际输入数值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setActualParameter(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].actualParameter = value;

}

//************************************
// Method:    setKi
// FullName:  setKi
// Access:    public 
// Returns:   void
// Qualifier: 设置PID的Ki值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setKi(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].Ki = value;
}

//************************************
// Method:    setKp
// FullName:  setKp
// Access:    public 
// Returns:   void
// Qualifier: 设置PID的Kp值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setKp(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].Kp = value;
}

//************************************
// Method:    setKd
// FullName:  setKd
// Access:    public 
// Returns:   void
// Qualifier: 设置PID的Kd值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setKd(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].Kd = value;
}

//************************************
// Method:    setParameter
// FullName:  setParameter
// Access:    public 
// Returns:   void
// Qualifier: 设置PID的目标数值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setParameter(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].setParameter = value;
}


//************************************
// Method:    getParameter
// FullName:  getParameter
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的目标数值
// Parameter: u8 PID_N
//************************************
float	getParameter(u8 PID_N)
{
	return  g_pid_n_info[PID_N].setParameter;
}

//************************************
// Method:    getErr
// FullName:  getErr
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的这一次误差值
// Parameter: u8 PID_N
//************************************
float getErr(u8 PID_N)
{
	return  g_pid_n_info[PID_N].err;
}

//************************************
// Method:    getErrLast
// FullName:  getErrLast
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的上一次误差值
// Parameter: u8 PID_N
//************************************
float getErrLast(u8 PID_N)
{
	return  g_pid_n_info[PID_N].err_last;
}
//************************************
// Method:    getKp
// FullName:  getKp
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的Kp值
// Parameter: u8 PID_N
//************************************
float getKp(u8 PID_N)
{
	return  g_pid_n_info[PID_N].Kp;
}

//************************************
// Method:    getKi
// FullName:  getKi
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的Ki值
// Parameter: u8 PID_N
//************************************
float getKi(u8 PID_N)
{
	return  g_pid_n_info[PID_N].Ki;
}

//************************************
// Method:    getKd
// FullName:  getKd
// Access:    public 
// Returns:   float
// Qualifier: 读取pid的Kd参数值
// Parameter: u8 PID_N
//************************************
float getKd(u8 PID_N)
{
	return  g_pid_n_info[PID_N].Kd;
}

//************************************
// Method:    getOutput
// FullName:  getOutput
// Access:    public 
// Returns:   float
// Qualifier: 读取pid输出值
// Parameter: u8 PID_N
//************************************
float getOutput(u8 PID_N)
{
	return  g_pid_n_info[PID_N].output;
}

//************************************
// Method:    getIntegral
// FullName:  getIntegral
// Access:    public 
// Returns:   float
// Qualifier: 读取pid积分值
// Parameter: u8 PID_N
//************************************
float getIntegral(u8 PID_N)
{
	return  g_pid_n_info[PID_N].integral;
}
#endif

