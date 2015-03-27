

/*********************************************************************
 * INCLUDES
 */
#include "hal_types.h"
#include "osal_snv.h"
  
   
/*********************************************************************
 * CONSTANT
 */
#define INFO_LENGTH   250  

   
#define MAXPAGES   5     
#define SERIAL_LENGTH   3  
#define SERIAL_ADDRESS 0x8E   

#define CASH_ADDRESS    0x90
#define CASH_LENGTH    4

#define INFO_PAGES_ADDR    0x91
#define INFO_PAGES_LEN    1
   
#define ID_LENGTH   16
#define EXIST   1  
#define NOEXIST   0 



#define RecInfo1      0x84
#define RecInfo1len   0x85   

#define RecInfo2      0x86
#define RecInfo2len   0x87

#define RecInfo3      0x88
#define RecInfo3len   0x89

#define RecInfo4      0x8A
#define RecInfo4len   0x8B

#define RecInfo5      0x8C   
#define RecInfo5len   0x8D   
   
   
/*************************************
* uint8 flash_pwd_init( void )
* ��flash�ڲ�����ĳ�ʼ������
* ���ڶ�Ӧλ������Ӧ�ĳ�ʼ���룬8��0
**************************************/
extern uint8 flash_pwd_init( void );




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




/**************************************
* uint8 flash_info_init( void )
* ��flash�ڲ���ʼ�����գ��������ݵĴ洢����
* ��flash�ڲ���ʼ�����գ��������ݵĳ��ȵĴ洢
**************************************/
extern uint8 flash_info_init( void );




/**************************************
* uint8 flash_Rinfo_all_read(void *pBuf)
* ��flash�ڲ���������0x84��ȫ����ȡ
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
extern uint8 flash_Rinfo_all_read(void *pBuf);






/**************************************
* uint8 flash_Tinfo_all_read(void *pBuf)
* ��flash�ڲ��������ݵ�ȫ����ȡ
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
extern uint8 flash_Tinfo_all_read(void *pBuf);





/**************************************
* uint8 flash_Rinfo_all_write(void *pBuf, uint8 add)
* ��flash�ڲ��������ݵ�ȫ��д��addλ��
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
extern uint8 flash_Rinfo_all_write(void *pBuf, uint8 add);





/**************************************
* uint8 flash_Tinfo_all_write(void *pBuf)
* ��flash�ڲ��������ݵ�ȫ��д��
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
extern uint8 flash_Tinfo_all_write(void *pBuf);




/**************************************
* uint8 flash_Rinfo_single_read( uint8 seq, uint8 index )
* ��ȡflash�ڲ��������ݵĴ洢����ĵ�seq���indexλ���������
* ��seqδ�����洢����ĳ��ȣ����ض�Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
extern uint8 flash_Rinfo_single_read(uint8 seq, uint8 index);



/**************************************
* uint8 flash_Tinfo_single_read( uint8 seq )
* ��ȡflash�ڲ��������ݵĴ洢����ĵ�seq��λ���������
* ��seqδ�����洢����ĳ��ȣ����ض�Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
extern uint8 flash_Tinfo_single_read(uint8 seq);




/**************************************
* uint8 flash_Rinfo_single_write(uint8 seq,uint8 index, uint8 value)
* ��flash�ڲ��������ݵĴ洢����ĵ�seq���indexλ��������value
* ��seqδ�����洢����ĳ��ȣ����ض�д�ɹ���Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
extern uint8 flash_Rinfo_single_write(uint8 seq,uint8 index, uint8 value);




/**************************************
* uint8 flash_Tinfo_single_write(uint8 seq, uint8 value)
* ��flash�ڲ��������ݵĴ洢����ĵ�seqλ��������value
* ��seqδ�����洢����ĳ��ȣ����ض�д�ɹ���Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
extern uint8 flash_Tinfo_single_write(uint8 seq, uint8 value);





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





/**************************************
* uint8 flash_Tinfo_short_write(void *pBuf, uint8 len)
* ��flash�ڲ�������������Ľ������ݵĳ���Ϊs
* ����s����д�볤��Ϊlen�����飬��ַ��pBuf
* �������洢���ȵ����ݲ�д
**************************************/
extern uint8 flash_Tinfo_short_write(void *pBuf, uint8 len);


/**************************************
* uint8 flash_Tinfo_short_read(void *pBuf, uint8 seq)
* ��flash�ڲ�������������ĵ�seq����ʼΪ��0λ����󣨰���seq����ȡ����5������
* �������洢���ȣ������������
* ��ֵ��pBuf��
**************************************/
extern uint8 flash_Tinfo_short_read(void *pBuf, uint8 seq);



/**************************************
* uint8 flash_Rinfo_Length_init(uint8 seq)
* ��flash�ڲ���ʼ���������ݵ�seqλ�ĳ��ȴ洢λ
**************************************/
extern uint8 flash_Rinfo_Length_init(uint8 seq);

/**************************************
* uint8 flash_Rinfo_init(uint8 seq��
* ��flash�ڲ���ʼ���������ݴ洢
**************************************/
uint8 flash_Rinfo_init(uint8 seq);


/**************************************
* uint8 flash_Rinfo_Length_set(uint8 length)
* ��flash�ڲ�д��������ݵĳ��ȴ洢λ
**************************************/
extern uint8 flash_Rinfo_Length_set(uint8 length);





/**************************************
* uint8 flash_Rinfo_Length_get(void)
* ��flash�ڲ���ȡ�������ݵĳ��ȴ洢λ
**************************************/
extern uint8 flash_Rinfo_Length_get(void);




/**************************************
* uint8 flash_Rinfo_short_write(void *pBuf, uint8 len)
* ��flash�ڲ�������������Ľ������ݵĳ���Ϊs
* ����s����д�볤��Ϊlen�����飬��ַ��pBuf
* �������洢���ȵ����ݲ�д
**************************************/
extern uint8 flash_Rinfo_short_write(void *pBuf, uint8 len);




/**************************************
* uint8 flash_Rinfo_short_read(void *pBuf, uint8 seq, uint8 pages)
* ��flash�ڲ�������������ĵ�pageҳ�ĵ�seq����ʼΪ��0λ��
* ��󣨰���seq����ȡ����9������
* �������洢���ȣ������������
* ��ֵ��pBuf��
**************************************/
extern uint8 flash_Rinfo_short_read(void *pBuf, uint8 seq, uint8 pages);

/**************************************
* uint8 flash_Recinfo_getID(void *pBuf, uint8 add)
* ��ȡ�յ��Ĵ洢��Ϣseq�����ֵ�IDֵ
**************************************/
uint8 flash_Recinfo_getID(void *pBuf, uint8 add);


/**************************************
* uint8 flash_Recinfo_Compare_Save(void *pBuf)
* ������5ҳflash������д�����ݣ��������ID���л��ߴ洢����
* �򲻴洢��һ�������IDȫΪ0�����������Դ洢
**************************************/
extern uint8 flash_Recinfo_Compare_Save(void *pBuf);


/**************************************
* uint8 flash_RinfoPageAddress(uint8 seq)
* ��ȡ�յ��Ĵ洢��Ϣ��seqҳ�ĵ�ַ
**************************************/
extern uint8 flash_RinfoPageAddress(uint8 seq);

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



/**************************************
* uint8 flash_RINFO_pagesInit(void);
* ��ʼ���洢ҳ��
**************************************/
uint8 flash_RINFO_pagesInit();


/**************************************
* uint8 flash_RINFO_addpages(void);
*���Ӵ洢ҳ�������ӵ�MAXPAGES��ֹͣ
**************************************/
extern uint8 flash_RINFO_addpages();


/**************************************
* uint8 flash_RINFO_getpages(void);
* ��ȡ�洢ҳ��
**************************************/
extern uint8 flash_RINFO_getpages();

/**************************************
* uint8 flash_RINFO_setpages(uint8 pages);
* ���ô洢ҳ��
**************************************/
extern uint8 flash_RINFO_setpages(uint8 pages);