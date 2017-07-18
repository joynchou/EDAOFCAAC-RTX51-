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
#include "../ALGORITHM/PID/PID.h"

void taskStart() _task_ 0
{
	setup();
	os_delete_task(0);
}

void task2(void) _task_ 2
{
	openPID(PID_1);
	for (;;)
	{
		setActualParameter(PID_1, getAngle(PRESENT_ANGLE));//设置pid的实际参数

		PID(PID_1);

	}


}

}

