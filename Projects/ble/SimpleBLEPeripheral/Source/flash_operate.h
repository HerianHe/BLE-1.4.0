/*********************************************************************
* INCLUDES
*/
#include "hal_types.h"
#include "osal_snv.h"


/*********************************************************************
* CONSTANT
*/
#define SERIAL_ADDRESS		0x80
#define SERIAL_LENGTH		3

#define CASH_ADDRESS		0x81
#define CASH_LENGTH			4


#define PASSWORD_ADDRESS	0x90  

#define INFO_LENGTH			150

#define TINFO_ADDRESS		0x91
#define TINFO_LEN_ADDRESS	0x92

#define MAXPAGES			5 

#define R_PAGES_ADDRESS		0x93

#define ID_LENGTH			16

#define RINFO_ADDRESS1		0x94
#define RINFO_ADDRESS2		0x95
#define RINFO_ADDRESS3		0x96
#define RINFO_ADDRESS4		0x97
#define RINFO_ADDRESS5		0x98


    
#define EXIST		1
#define NOEXIST		0
  


#define INFO_PAGES_ADDR    0x91
#define INFO_PAGES_LEN    1

/*********************************************************************
* FUNCTIONS
*/
//���к�**********************************************************************
/**************************************
* uint8 flash_serialNumberInit(void);
* ���кŵĳ�ʼ��
**************************************/
uint8 flash_serialNumberInit(void);

/**************************************
* uint8 flash_generateSerialNumber(void *pBuf);
* ����һ��3λ���кţ������ַ��ʼλpBuf
**************************************/
extern uint8 flash_generateSerialNumber(void *pBuf);

/**************************************
* uint8 flash_getSerialNumber(void *pBuf);
* ��ȡ������3λ���кţ���ֵ�������ַpBuf
**************************************/
extern uint8 flash_getSerialNumber(void *pBuf);
//�������к�******************************************************************




//���************************************************************************
/**************************************
* uint8 flash_cashInit(void);
* ���ĳ�ʼ��
**************************************/
uint8 flash_cashInit();

/**************************************
* uint8 flash_save_cash(void *pBuf);
* �洢���
**************************************/
extern uint8 flash_save_cash(void *pBuf);

/**************************************
* uint8 flash_get_cash(void *pBuf);
* ��ȡ���ŵ�һ��pBuf����������
**************************************/
extern uint8 flash_get_cash(void *pBuf);
//�������********************************************************************





//����************************************************************************
/*************************************
* uint8 flash_pwd_init( void )
* ��flash�ڲ�����ĳ�ʼ������
* ���ڶ�Ӧλ������Ӧ�ĳ�ʼ���룬8��0
**************************************/
extern uint8 flash_pwd_init(void);

/*************************************
* uint8 flash_pwd_write(void *pBuf)
* ��flash�ڲ�д������
* ����pBufΪһ��8λuint8������ĵ�ַ
**************************************/
extern uint8 flash_pwd_write(void *pBuf);

/**************************************
* uint8 flash_pwd_read(void *pBuf)
* ��ȡflash�ڲ����������
* ����pBufΪһ��8λuint8����ĵ�ַ
**************************************/
extern uint8 flash_pwd_read(void *pBuf);

/**************************************
* uint8 flash_pwd_delete(void *pBuf)
* ���flash�ڲ����������
**************************************/
extern uint8 flash_pwd_delete(void);
//��������*******************************************************************





//TINFO************************************************************************
/**************************************
* uint8 flash_Tinfo_init( void )
* ��flash�ڲ���ʼ���������ݵĴ洢
**************************************/
extern uint8 flash_Tinfo_init(void);

/**************************************
* uint8 flash_Tinfo_all_read(void *pBuf)
* ��flash�ڲ��������ݵ�ȫ����ȡ
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
extern uint8 flash_Tinfo_all_read(void *pBuf);

/**************************************
* uint8 flash_Tinfo_short_write(void *pBuf, uint8 len)
* ��flash�ڲ�������������Ľ������ݵĳ���Ϊs
* ����s����д�볤��Ϊlen�����飬��ַ��pBuf
* �������洢���ȵ����ݲ�д
**************************************/
extern uint8 flash_Tinfo_short_write(void *pBuf, uint8 len);

/**************************************
* uint8 flash_Tinfo_single_read( uint8 seq )
* ��ȡflash�ڲ��������ݵĴ洢����ĵ�seq��λ���������
* ��seqδ�����洢����ĳ��ȣ����ض�Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
extern uint8 flash_Tinfo_single_read(uint8 seq);

/**************************************
* uint8 flash_Tinfo_single_write(uint8 seq, uint8 value)
* ��flash�ڲ��������ݵĴ洢����ĵ�seqλ��������value
* ��seqδ�����洢����ĳ��ȣ����ض�д�ɹ���Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
extern uint8 flash_Tinfo_single_write(uint8 seq, uint8 value);
//����TINFOLEN*******************************************************************




//TINFOLEN*******************************************************************
/**************************************
* uint8 flash_Tinfo_Length_init(void��
* ��flash�ڲ���ʼ���������ݵĳ��ȴ洢λ
**************************************/
extern uint8 flash_Tinfo_Length_init(void);

/**************************************
* uint8 flash_Tinfo_Length_set(uint8 length)
* ��flash�ڲ�д�뷢�����ݵĳ��ȴ洢λ
**************************************/
extern uint8 flash_Tinfo_Length_set(uint8 length);

/**************************************
* uint8 flash_Tinfo_Length_get(void)
* ��flash�ڲ���ȡ�������ݵĳ��ȴ洢λ
**************************************/
extern uint8 flash_Tinfo_Length_get(void);
//����TINFO*******************************************************************

//RINFO*******************************************************************
/**************************************
* uint8 flash_Rinfo_page_clear(uint8 page)
*��flash�ڲ��Ľ��������pageҳ����
**************************************/
extern uint8 flash_Rinfo_page_clear(uint8 page);

/**************************************
* uint8 flash_Rinfo_all_clear(void)
*��flash�ڲ��Ľ�������ȫ������
**************************************/
extern uint8 flash_Rinfo_all_clear(void);

/**************************************
* uint8 flash_RinfoPageAddress(uint8 num)
* ��ȡ�յ��Ĵ洢��Ϣ��seqҳ�ĵ�ַ
**************************************/
extern uint8 flash_RinfoPageAddress(uint8 num);

/**************************************
* uint8 flash_Rinfo_init(uint8 Addr��
* ��flash�ڲ���ʼ���������ݴ洢
**************************************/
uint8 flash_Rinfo_init(uint8 Addr);

/**************************************
* uint8 flash_Rinfo_ALLinit(void)
* ��flash�ڲ���ʼ�����н������ݴ洢
**************************************/
extern uint8 flash_Rinfo_ALLinit(void);



////////NFC*******************************************************************
/**************************************
* uint8 flash_Rinfo_all_write(void *pBuf, uint8 addr)
* ��flash�ڲ��������ݵ�ȫ��д��addλ��
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
extern uint8 flash_Rinfo_all_write(void *pBuf, uint8 addr);

/**************************************
* uint8 flash_Rinfo_all_write(void *pBuf, uint8 addr)
**************************************/
extern uint8 flash_Rinfo_all_read(void *pBuf, uint8 pages);

/**************************************
* uint8 flash_Recinfo_getID(void *pBuf, uint8 addr)
* ��ȡ�յ��Ĵ洢��Ϣaddr�����ֵ�IDֵ
**************************************/
uint8 flash_Recinfo_getID(void *pBuf, uint8 addr);

/**************************************
* uint8 flash_Recinfo_Compare_Save(void *pBuf)
* ������5ҳflash������д�����ݣ��������ID���л��ߴ洢����
* �򲻴洢��һ�������IDȫΪ0�����������Դ洢
**************************************/
extern uint8 flash_Recinfo_Compare_Save(void *pBuf);
////////NFC*******************************************************************


////////APP*******************************************************************
/**************************************
* uint8 flash_Rinfo_short_read(void *pBuf, uint8 seq, uint8 pages)
* ��flash�ڲ�������������ĵ�pageҳ�ĵ�seq����ʼΪ��0λ��
* ��󣨰���seq����ȡ����9������
* �������洢���ȣ������������
* ��ֵ��pBuf��
**************************************/
extern uint8 flash_Rinfo_short_read(void *pBuf, uint8 seq, uint8 pages);
////////APP*******************************************************************


////////BLE*******************************************************************
/**************************************
* uint8 flash_Rinfo_single_read( uint8 Addr, uint8 index )
* ��ȡflash�ڲ��������ݵĴ洢����ĵ�Addr��indexλ���������
* ��seqδ�����洢����ĳ��ȣ����ض�Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
extern uint8 flash_Rinfo_single_read(uint8 Addr, uint8 index);

/**************************************
* uint8 flash_Rinfo_single_write(uint8 Addr,uint8 index, uint8 value)
* ��flash�ڲ��������ݵĴ洢����ĵ�Addr���indexλ��������value
* ��seqδ�����洢����ĳ��ȣ����ض�д�ɹ���Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
extern uint8 flash_Rinfo_single_write(uint8 Addr, uint8 index, uint8 value);
////////BLE*******************************************************************
//����RINFO*******************************************************************



//RPAGES****��ֵ�����ڴ�ŵ�ǰflash���ж�������********************************
/**************************************
* uint8 flash_Rinfo_pages_init(void)
* ��flash�ڲ���ʼ���������ݵ�ҳ���洢λ
**************************************/
uint8 flash_Rinfo_pages_init(void);

/**************************************
* uint8 flash_Rinfo_add_pages(void)
* ��flash�����ӷ������ݵ�ҳ��һҳ
**************************************/
extern uint8 flash_Rinfo_add_pages(void);

/**************************************
* uint8 flash_Rinfo_minus_pages(void)
* ��flash�м�ȥ�������ݵ�ҳ��һҳ
**************************************/
extern uint8 flash_Rinfo_minus_pages(void);

/**************************************
* uint8 flash_Rinfo_minus_pages(void)
* ��flash�л�ȡ�������ݵ�ҳ��
**************************************/
extern uint8 flash_Rinfo_get_pages(void);

/**************************************
* uint8 flash_Rinfo_get_pages(void)
* ��flash�л�ȡ�������ݵ�ҳ��
**************************************/
extern uint8 flash_Rinfo_get_pages(void);
//����RPAGES*******************************************************************



/**************************************
* uint8 flash_info_init( void )
* ��flash�ڲ���ʼ��������Ϣ
**************************************/
extern uint8 flash_info_init(void);
