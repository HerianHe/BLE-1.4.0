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
#include "FlashOperate.h"


/*********************************************************************
* FUNCTIONS
*/


//���к�**********************************************************************
/**************************************
* uint8 flash_serialNumberInit(void);
* ���кŵĳ�ʼ��
**************************************/
uint8 flash_serialNumberInit()
{
	uint8 serial[SERIAL_LENGTH] = { 0 };
	//��ַ0x8E�����к�
	int8 ret8 = osal_snv_read(SERIAL_ADDRESS, SERIAL_LENGTH, serial);
	// ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
	if (NV_OPER_FAILED == ret8)
	{
		// �����ݽṹ���浽flash
		flash_generateSerialNumber(serial);
		osal_snv_write(SERIAL_ADDRESS, SERIAL_LENGTH, serial);
		osal_snv_read(SERIAL_ADDRESS, SERIAL_LENGTH, serial);
	}
	return SUCCESS;
}

/**************************************
* uint8 flash_generateSerialNumber(void *pBuf);
* ����һ��3λ���кţ������ַ��ʼλpBuf
**************************************/
uint8 flash_generateSerialNumber(void *pBuf)
{
	uint8 serial[SERIAL_LENGTH] = { 0 };
	uint16 fulserial[SERIAL_LENGTH] = { 0 };

	for (int i = 0; i<SERIAL_LENGTH; i++)
	{
		fulserial[i] = osal_rand();
		serial[i] = LO_UINT16(fulserial[i]);
	}
	for (int i = 0; i<SERIAL_LENGTH; i++)
	{
		((uint8 *)pBuf)[i] = serial[i];
	}
	return 0;
}

/**************************************
* uint8 flash_getSerialNumber(void *pBuf);
* ��ȡ������3λ���кţ���ֵ�������ַpBuf
**************************************/
uint8 flash_getSerialNumber(void *pBuf)
{
	return osal_snv_read(SERIAL_ADDRESS, SERIAL_LENGTH, pBuf);
}
//�������к�******************************************************************






//���************************************************************************
/**************************************
* uint8 flash_cashInit(void);
* ���ĳ�ʼ��
**************************************/
uint8 flash_cashInit()
{
	uint8 cash[CASH_LENGTH] = { 0 };
	int8 ret8 = osal_snv_read(CASH_ADDRESS, CASH_LENGTH, cash);
	// ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
	if (NV_OPER_FAILED == ret8)
	{
		// �����ݽṹ���浽flash
		osal_snv_write(CASH_ADDRESS, CASH_LENGTH, cash);
		osal_snv_read(CASH_ADDRESS, CASH_LENGTH, cash);
	}
	return SUCCESS;
}

/**************************************
* uint8 flash_save_cash(void *pBuf);
* �洢���
**************************************/
uint8 flash_save_cash(void *pBuf)
{
	return osal_snv_write(CASH_ADDRESS, CASH_LENGTH, pBuf);
}

/**************************************
* uint8 flash_get_cash(void *pBuf);
* ��ȡ���ŵ�һ��pBuf����������
**************************************/
uint8 flash_get_cash(void *pBuf)
{
	uint8 cash[CASH_LENGTH] = { 0 };
	osal_snv_read(CASH_ADDRESS, CASH_LENGTH, cash);
	for (int i = 0; i<CASH_LENGTH; i++)
	{
		((uint8 *)pBuf)[i] = cash[i];
	}
	return SUCCESS;
}
//�������********************************************************************




//����************************************************************************
/*************************************
* uint8 flash_pwd_init( void )
* ��flash�ڲ�����ĳ�ʼ������
* ���ڶ�Ӧλ������Ӧ�ĳ�ʼ���룬8��0
**************************************/
uint8 flash_pwd_init(void)
{
	uint8 pwd[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int8 ret8 = osal_snv_read(PASSWORD_ADDRESS, 8, pwd);
	// ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED ,
	// ������������ص���Ϊ��һ����¼������У� �Ӷ����ò����ĳ�������
	if (NV_OPER_FAILED == ret8)
	{
		// �����ݽṹ���浽flash
		osal_memset(PASSWORD_ADDRESS, 0, 8);
		osal_snv_write(PASSWORD_ADDRESS, 8, pwd);
		osal_snv_read(PASSWORD_ADDRESS, 8, pwd);
	}
	return SUCCESS;
}

/*************************************
* uint8 flash_pwd_write(void *pBuf)
* ��flash�ڲ�д������
* ����pBufΪһ��8λuint8������ĵ�ַ
**************************************/
uint8 flash_pwd_write(void *pBuf)
{
	return osal_snv_write(PASSWORD_ADDRESS, 8, pBuf);
}

/**************************************
* uint8 flash_pwd_read(void *pBuf)
* ��ȡflash�ڲ����������
* ����pBufΪһ��8λuint8����ĵ�ַ
**************************************/
uint8 flash_pwd_read(void *pBuf)
{
	return osal_snv_read(PASSWORD_ADDRESS, 8, pBuf);
}

/**************************************
* uint8 flash_pwd_delete(void *pBuf)
* ���flash�ڲ����������
**************************************/
uint8 flash_pwd_delete(void)
{
	uint8 pwd[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	return osal_snv_write(PASSWORD_ADDRESS, 8, pwd);
}
//��������*******************************************************************



//TINFO************************************************************************
uint8 flash_Tinfo_init(void)
{
	uint16* T_info;
	T_info = (uint16 *)osal_mem_alloc(250);
	osal_memset(T_info, 0, 250);

	int8 ret8 = osal_snv_read(TINFO_ADDRESS, INFO_LENGTH, T_info);
	// ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
	if (NV_OPER_FAILED == ret8)
	{
		// �����ݽṹ���浽flash
		osal_memset(T_info, 0, INFO_LENGTH);
		osal_snv_write(TINFO_ADDRESS, INFO_LENGTH, T_info);
		osal_snv_read(TINFO_ADDRESS, INFO_LENGTH, T_info);
	}
	//��ʼ��������Ϣ�ĳ���
	osal_mem_free(T_info);
}

/**************************************
* uint8 flash_Tinfo_all_read(void *pBuf)
* ��flash�ڲ��������ݵ�ȫ����ȡ
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
uint8 flash_Tinfo_all_read(void *pBuf)
{
	return osal_snv_read(TINFO_ADDRESS, INFO_LENGTH, pBuf);
}
//����TINFO*******************************************************************
