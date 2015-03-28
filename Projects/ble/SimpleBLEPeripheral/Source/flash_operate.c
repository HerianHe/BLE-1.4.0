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
		osal_memset(pwd, 0, 8);
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
/**************************************
* uint8 flash_Tinfo_init( void )
* ��flash�ڲ���ʼ���������ݵĴ洢
**************************************/
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
        return SUCCESS;
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

/**************************************
* uint8 flash_Tinfo_short_write(void *pBuf, uint8 len)
* ��flash�ڲ�������������Ľ������ݵĳ���Ϊs
* ����s����д�볤��Ϊlen�����飬��ַ��pBuf
* �������洢���ȵ����ݲ�д
**************************************/
uint8 flash_Tinfo_short_write(void *pBuf, uint8 len)
{
	uint8 length = 0;
	length = flash_Tinfo_Length_get();

	//����һ������ΪINFO_LENGTH������
	//uint16* inMem;
	//inMem= (uint16 *)osal_mem_alloc(INFO_LENGTH);
	//osal_memset(inMem,0,INFO_LENGTH);
	uint8 inMem[INFO_LENGTH] = { 0 };

	osal_snv_read(TINFO_ADDRESS, INFO_LENGTH, inMem);
	uint8 i = 0;
	for (i = 0; i<len; i++)
	{
		if ((length + i)<INFO_LENGTH)
		{
			inMem[length + i] = ((uint8 *)pBuf)[i];
		}
		else
		{
			break;
		}
	}
	length = length + len;
	if (length>INFO_LENGTH)
	{
		length = INFO_LENGTH;
	}
#if (defined HAL_LCD) && (HAL_LCD == TRUE)
	HalLcdWriteStringValue("LVALUE = ", length, 10, HAL_LCD_LINE_6);
#endif
	flash_Tinfo_Length_set(length);

	//�ͷ��ڴ�
	osal_snv_write(TINFO_ADDRESS, INFO_LENGTH, inMem);
	//osal_mem_free(inMem);
	return 0;
}

/**************************************
* uint8 flash_Tinfo_single_read( uint8 seq )
* ��ȡflash�ڲ��������ݵĴ洢����ĵ�seq��λ���������
* ��seqδ�����洢����ĳ��ȣ����ض�Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
uint8 flash_Tinfo_single_read(uint8 seq)
{
	uint8 temp[INFO_LENGTH] = { 0 };
	osal_snv_read(TINFO_ADDRESS, INFO_LENGTH, temp);
	if (seq<INFO_LENGTH)
	{
		return temp[seq];
	}
	else{
		return 0xFF;
	}
}

/**************************************
* uint8 flash_Tinfo_single_write(uint8 seq, uint8 value)
* ��flash�ڲ��������ݵĴ洢����ĵ�seqλ��������value
* ��seqδ�����洢����ĳ��ȣ����ض�д�ɹ���Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
uint8 flash_Tinfo_single_write(uint8 seq, uint8 value)
{
	uint8 temp[INFO_LENGTH] = { 0 };
	osal_snv_read(TINFO_ADDRESS, INFO_LENGTH, temp);
	if (seq<INFO_LENGTH)
	{
		temp[seq] = value;
		return osal_snv_write(TINFO_ADDRESS, INFO_LENGTH, temp);
	}
	else
	{
		return 0xFF;
	}
}
//����TINFO*******************************************************************




//TINFOLEN*******************************************************************
/**************************************
* uint8 flash_Tinfo_Length_init(void��
* ��flash�ڲ���ʼ���������ݵĳ��ȴ洢λ
**************************************/
uint8 flash_Tinfo_Length_init(void)
{
	uint8 temp = 0;
	//��ַTINFO_LEN_ADDRESS�Ƿ������ݵĳ��ȵĴ洢����
	int8 ret8 = osal_snv_read(TINFO_LEN_ADDRESS, 1, &temp);
	// ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
	if (NV_OPER_FAILED == ret8)
	{
		// �����ݽṹ���浽flash
		osal_snv_write(TINFO_LEN_ADDRESS, 1, &temp);
		osal_snv_read(TINFO_LEN_ADDRESS, 1, &temp);
	}
	return SUCCESS;
}

/**************************************
* uint8 flash_Tinfo_Length_set(uint8 length)
* ��flash�ڲ�д�뷢�����ݵĳ��ȴ洢λ
**************************************/
uint8 flash_Tinfo_Length_set(uint8 length)
{
	uint8 temp = 0;
	temp = length;
	return osal_snv_write(TINFO_LEN_ADDRESS, 1, &temp);
}

/**************************************
* uint8 flash_Tinfo_Length_get(void)
* ��flash�ڲ���ȡ�������ݵĳ��ȴ洢λ
**************************************/
uint8 flash_Tinfo_Length_get(void)
{
	uint8 temp = 1;
	osal_snv_read(TINFO_LEN_ADDRESS, 1, &temp);
	return temp;
}
//����TINFOLEN*******************************************************************



//RINFO*******************************************************************
/**************************************
* uint8 flash_RinfoPageAddress(uint8 num)
* ��ȡ�յ��Ĵ洢��Ϣ��numҳ�ĵ�ַ
**************************************/
uint8 flash_RinfoPageAddress(uint8 num)
{
	if ((num >= 0) && (num<MAXPAGES))
	{
		return RINFO_ADDRESS1 + num;
	}
	return RINFO_ADDRESS1;
}

/**************************************
* uint8 flash_Rinfo_init(uint8 Addr)
* ��flash�ڲ���ʼ���������ݴ洢
**************************************/
uint8 flash_Rinfo_init(uint8 Addr)
{
	uint16* temp;
	temp = (uint16 *)osal_mem_alloc(250);
	osal_memset(temp, 0, 250);
	int8 ret8 = osal_snv_read(Addr, INFO_LENGTH, temp);
	// ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
	if (NV_OPER_FAILED == ret8)
	{
		// �����ݽṹ���浽flash
		osal_snv_write(Addr, INFO_LENGTH, temp);
		osal_snv_read(Addr, INFO_LENGTH, temp);
	}
	osal_mem_free(temp);
	return SUCCESS;
}

/**************************************
* uint8 flash_Rinfo_ALLinit(void)
* ��flash�ڲ���ʼ�����н������ݴ洢
**************************************/
uint8 flash_Rinfo_ALLinit(void)
{
	for (int i = 0; i < MAXPAGES; i++)
	{
		flash_Rinfo_init(flash_RinfoPageAddress(i));
	}
        return SUCCESS;
}

////////NFC*******************************************************************
/**************************************
* uint8 flash_Rinfo_all_write(void *pBuf, uint8 add)
* ��flash�ڲ��������ݵ�ȫ��д��addλ��
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
uint8 flash_Rinfo_all_write(void *pBuf, uint8 addr)
{
	return osal_snv_write(addr, INFO_LENGTH, pBuf);
}

/**************************************
* uint8 flash_Recinfo_Compare_Save(void *pBuf)
* ������5ҳflash������д�����ݣ��������ID���л��ߴ洢����
* �򲻴洢��һ�������IDȫΪ0�����������Դ洢
**************************************/
uint8 flash_Recinfo_Compare_Save(void *pBuf)
{
	uint8 uID[ID_LENGTH] = { 0 };
	//��һ�������IDȫΪ0�������������Դ洢
	uint8 availID[ID_LENGTH] = { 0 };
	int availableSEQ = -1;


	uint8 state = NOEXIST;

	for (int i = 0; i<MAXPAGES; i++)
	{
		flash_Recinfo_getID(uID, flash_RinfoPageAddress(i));
		if (osal_memcmp(uID, pBuf, ID_LENGTH))
		{
			state = EXIST;
			continue;
		}
		else{
			if (osal_memcmp(uID, availID, ID_LENGTH))
			{
				availableSEQ = i;
				break;
			}
		}
	}

	if ((state == NOEXIST) && (availableSEQ != -1))
	{
		flash_Rinfo_add_pages();
		flash_Rinfo_all_write(pBuf, flash_RinfoPageAddress(availableSEQ));
	}
	return 0;
}
/**************************************
* uint8 flash_Recinfo_getID(void *pBuf, uint8 addr)
* ��ȡ�յ��Ĵ洢��Ϣaddr�����ֵ�IDֵ
**************************************/
uint8 flash_Recinfo_getID(void *pBuf, uint8 addr)
{
	uint8 inMem[ID_LENGTH] = { 0 };
	osal_snv_read(addr, ID_LENGTH, inMem);

	for (int i = 0; i<ID_LENGTH; i++)
	{
		((uint8 *)pBuf)[i] = inMem[i];
	}
	return 0;
}
////////NFC*******************************************************************


////////APP*******************************************************************
/**************************************
* uint8 flash_Rinfo_short_read(void *pBuf, uint8 seq, uint8 pageID)
* ��flash�ڲ�������������ĵ�pageIDҳ�ĵ�seq����ʼΪ��0λ��
* ��󣨰���seq����ȡ����9������
* �������洢���ȣ������������
* ��ֵ��pBuf��
* ע�⣺����ʹ�õ�pageID���ڲ��洢��pages����һ����ֵ�������ڲ��洢��5ҳ���ݣ���flash_Rinfo_get_pages()
* �õ���ֵ��5������Ҫ���������ֵ��4��Ҳ����˵���ڲ���5ҳ���ݣ���page�ı���Ǵ�0��4��
**************************************/
uint8 flash_Rinfo_short_read(void *pBuf, uint8 seq, uint8 pageID)
{
	//����һ������ΪINFO_LENGTH������
	uint16* inMem;
	inMem = (uint16 *)osal_mem_alloc(INFO_LENGTH);
	osal_memset(inMem, 0, INFO_LENGTH);

	osal_snv_read(flash_RinfoPageAddress(pageID), INFO_LENGTH, inMem);

	uint8 temp[9] = { 0 };


	uint8 i = 0;
	for (i = 0; i<9; i++)
	{
		if ((seq + i)<INFO_LENGTH)
		{
			temp[i] = inMem[seq + i];
		}
		else
		{
			break;
		}
	}

	for (i = 0; i<9; i++)
	{
		((uint8 *)pBuf)[i] = temp[i];
	}

	//�ͷ��ڴ�
	osal_mem_free(inMem);
	return 0;
}
////////APP*******************************************************************




////////BLE*******************************************************************
/**************************************
* uint8 flash_Rinfo_single_read( uint8 Addr, uint8 index )
* ��ȡflash�ڲ��������ݵĴ洢����ĵ�Addr��indexλ���������
* ��seqδ�����洢����ĳ��ȣ����ض�Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
uint8 flash_Rinfo_single_read(uint8 Addr, uint8 index)
{
	uint8 temp[INFO_LENGTH] = { 0 };
	osal_snv_read(Addr, INFO_LENGTH, temp);
	if (index<INFO_LENGTH)
	{
		return temp[index];
	}
	else{
		return 0xFF;
	}
}

/**************************************
* uint8 flash_Rinfo_single_write(uint8 Addr, uint8 value)
* ��flash�ڲ��������ݵĴ洢����ĵ�Addr���indexλ��������value
* ��seqδ�����洢����ĳ��ȣ����ض�д�ɹ���Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
uint8 flash_Rinfo_single_write(uint8 Addr, uint8 index, uint8 value)
{
	uint8 temp[INFO_LENGTH] = { 0 };
	osal_snv_read(Addr, INFO_LENGTH, temp);
	if (index<INFO_LENGTH)
	{
		temp[index] = value;
		return osal_snv_write(Addr, INFO_LENGTH, temp);
	}
	else
	{
		return Addr;
	}
}
////////BLE*******************************************************************
//����RINFO*******************************************************************


//RPAGES****��ֵ�����ڴ�ŵ�ǰflash���ж�������********************************
/**************************************
* uint8 flash_Rinfo_pages_init(void)
* ��flash�ڲ���ʼ���������ݵ�ҳ���洢λ
**************************************/
uint8 flash_Rinfo_pages_init(void)
{
	uint8 temp = 0;
	int8 ret8 = osal_snv_read(R_PAGES_ADDRESS, 1, &temp);
	// ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
	if (NV_OPER_FAILED == ret8)
	{
		// �����ݽṹ���浽flash
		osal_snv_write(R_PAGES_ADDRESS, 1, &temp);
		osal_snv_read(R_PAGES_ADDRESS, 1, &temp);
	}
	return SUCCESS;
}

/**************************************
* uint8 flash_Rinfo_add_pages(void)
* ��flash�����ӷ������ݵ�ҳ��һҳ
**************************************/
uint8 flash_Rinfo_add_pages(void)
{
	uint8 temp = 0;
	osal_snv_read(R_PAGES_ADDRESS, 1, &temp);
	temp = temp + 1;
	osal_snv_write(R_PAGES_ADDRESS, 1, &temp);
	return temp;
}

/**************************************
* uint8 flash_Rinfo_minus_pages(void)
* ��flash�м�ȥ�������ݵ�ҳ��һҳ
**************************************/
uint8 flash_Rinfo_minus_pages(void)
{
	uint8 temp = 0;
	osal_snv_read(R_PAGES_ADDRESS, 1, &temp);
	if (temp>0)
	{
		temp = temp - 1;
	}
	osal_snv_write(R_PAGES_ADDRESS, 1, &temp);
	return temp;
}

/**************************************
* uint8 flash_Rinfo_get_pages(void)
* ��flash�л�ȡ�������ݵ�ҳ��
**************************************/
uint8 flash_Rinfo_get_pages(void)
{
	uint8 temp = 0;
	osal_snv_read(R_PAGES_ADDRESS, 1, &temp);
	return temp;
}
//����RPAGES*******************************************************************




/**************************************
* uint8 flash_info_init( void )
* ��flash�ڲ���ʼ��������Ϣ
**************************************/
uint8 flash_info_init(void)
{
	flash_serialNumberInit();
	flash_cashInit();
	flash_pwd_init();
	flash_Tinfo_init();
	flash_Tinfo_Length_init();
	flash_Rinfo_pages_init();
	flash_Rinfo_ALLinit();
        return SUCCESS;
}
