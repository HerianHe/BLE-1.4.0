/*********************************************************************
* INCLUDES
*/
#include "hal_adc.h"
#include "hal_flash.h"
#include "hal_types.h"
#include "comdef.h"
#include "OSAL.h"
#include "osal_snv.h"
#include "hal_assert.h"
#include "saddr.h"
#include "bcomdef.h"
#include "OSAL_PwrMgr.h"

#include "OnBoard.h"
#include "hal_adc.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_lcd.h"
#include "flash_operate.h"

/**************************************
* uint8 led_start_social(void);
* ��ʼ�罻ģʽ
**************************************/
extern uint8 led_start_social(void);

/**************************************
* uint8 led_info_rec(void);
* �յ���Ϣ
**************************************/
extern uint8 led_info_rec(void);

/**************************************
* uint8 led_notif(uint8 rank);
* �յ���Ϣ
**************************************/
uint8 led_notif(uint8 rank);