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

#define INFO_LENGTH			250  
#define TINFO_ADDRESS		0x90


#define MAXPAGES   5     
  
   

#define CASH_ADDRESS    0x81
#define CASH_LENGTH    4

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

//����TINFO*******************************************************************
