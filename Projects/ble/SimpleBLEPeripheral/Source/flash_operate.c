#include "hal_adc.h"
#include "hal_flash.h"
#include "hal_types.h"
#include "comdef.h"
#include "OSAL.h"
#include "osal_snv.h"
#include "hal_assert.h"
#include "saddr.h"
#include "flash_operate.h"
#include "bcomdef.h"
#include "OSAL_PwrMgr.h"

#include "OnBoard.h"
#include "hal_adc.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_lcd.h"
#include "flash_operate.h"

  
/*************************************
* uint8 flash_pwd_init( void )
* ��flash�ڲ�����ĳ�ʼ������
* ���ڶ�Ӧλ������Ӧ�ĳ�ʼ���룬8��0
**************************************/
uint8 flash_pwd_init( void )
{
	uint8 pwd[8]= { 1, 2, 3, 4, 5, 6, 7, 8};
	int8 ret8 = osal_snv_read(0x80, 8, pwd);
    // ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED ,
    // ������������ص���Ϊ��һ����¼������У� �Ӷ����ò����ĳ�������
    if(NV_OPER_FAILED == ret8)
    {
        // �����ݽṹ���浽flash
        osal_memset(pwd, 0, 8);
        osal_snv_write(0x80, 8, pwd); 
        osal_snv_read(0x80, 8, pwd);
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
	return osal_snv_write(0x80, 8, pBuf);
}

/**************************************
* uint8 flash_pwd_read(void *pBuf)
* ��ȡflash�ڲ����������
* ����pBufΪһ��8λuint8����ĵ�ַ
**************************************/
uint8 flash_pwd_read(void *pBuf)
{
	return osal_snv_read(0x80, 8, pBuf);
}

/**************************************
* uint8 flash_pwd_delete(void *pBuf)
* ���flash�ڲ����������
**************************************/
uint8 flash_pwd_delete(void)
{
	uint8 pwd[8]= { 0, 0, 0, 0, 0, 0, 0, 0};
	return osal_snv_write(0x80, 8, pwd);
}



/**************************************
* uint8 flash_info_init( void )
* ��flash�ڲ���ʼ�����գ��������ݵĴ洢����
* ��flash�ڲ���ʼ�����գ��������ݵĳ��ȵĴ洢
**************************************/
uint8 flash_info_init( void )
{
    uint16* T_info;
    T_info= (uint16 *)osal_mem_alloc(250);
    osal_memset(T_info,0,250);
    //��ַ0x82�Ƿ��ͳ�ȥ����Ϣ
    int8 ret8 = osal_snv_read(0x82, INFO_LENGTH, T_info);
    // ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
    if(NV_OPER_FAILED == ret8)
    {
        // �����ݽṹ���浽flash
        osal_memset(T_info, 0, INFO_LENGTH);
        osal_snv_write(0x82, INFO_LENGTH, T_info); 
        osal_snv_read(0x82, INFO_LENGTH, T_info);
    }
    //��ʼ��������Ϣ�ĳ���
    flash_Tinfo_Length_init();
    osal_mem_free(T_info);

    //��ʼ�����кŴ洢��ַ
    flash_serialNumberInit();
    
    //��ʼ�����洢
    flash_cashInit();
    
    //��ʼ��������Ϣ
    flash_Rinfo_init(RecInfo1);
    flash_Rinfo_Length_init(RecInfo1len);
    flash_Rinfo_init(RecInfo2);
    flash_Rinfo_Length_init(RecInfo2len);
    flash_Rinfo_init(RecInfo3);
    flash_Rinfo_Length_init(RecInfo3len);
    flash_Rinfo_init(RecInfo4);
    flash_Rinfo_Length_init(RecInfo4len);
    flash_Rinfo_init(RecInfo5);
    flash_Rinfo_Length_init(RecInfo5len);
    //��ʼ��ҳ��
    flash_RINFO_pagesInit();
    return SUCCESS;
}

/**************************************
* uint8 flash_Rinfo_all_read(void *pBuf)
* ��flash�ڲ���������0x84��ȫ����ȡ
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
uint8 flash_Rinfo_all_read(void *pBuf)
{
	return osal_snv_read(0x84, INFO_LENGTH, pBuf);
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
	return osal_snv_read(0x82, INFO_LENGTH, pBuf);
}

/**************************************
* uint8 flash_Rinfo_all_write(void *pBuf, uint8 add)
* ��flash�ڲ��������ݵ�ȫ��д��addλ��
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
uint8 flash_Rinfo_all_write(void *pBuf, uint8 add)
{
	return osal_snv_write(add, INFO_LENGTH, pBuf);
}

/**************************************
* uint8 flash_Tinfo_all_write(void *pBuf)
* ��flash�ڲ��������ݵ�ȫ��д��
* ������һ������INFO_LENGTH�������ַ
* ����ֵ��osal flash������ֵ������μ�API�ĵ�
* һ��ʹ�óɹ���SUCCESS
**************************************/
uint8 flash_Tinfo_all_write(void *pBuf)
{
	return osal_snv_write(0x82, INFO_LENGTH, pBuf);
}




/**************************************
* uint8 flash_Rinfo_single_read( uint8 seq, uint8 index )
* ��ȡflash�ڲ��������ݵĴ洢����ĵ�seq���indexλ���������
* ��seqδ�����洢����ĳ��ȣ����ض�Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
uint8 flash_Rinfo_single_read(uint8 seq, uint8 index)
{
	uint8 temp[INFO_LENGTH]={0};
        osal_snv_read(seq, INFO_LENGTH, temp);
        if(seq<INFO_LENGTH)
        {
          return temp[index];
        }else{
          return 0xFF;
        }
}




/**************************************
* uint8 flash_Tinfo_single_read( uint8 seq )
* ��ȡflash�ڲ��������ݵĴ洢����ĵ�seq��λ���������
* ��seqδ�����洢����ĳ��ȣ����ض�Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
uint8 flash_Tinfo_single_read(uint8 seq)
{
	uint8 temp[INFO_LENGTH]={0};
        osal_snv_read(0x82, INFO_LENGTH, temp);
	if(seq<INFO_LENGTH)
        {
          return temp[seq];
        }else{
          return 0xFF;
        }
}





/**************************************
* uint8 flash_Rinfo_single_write(uint8 seq, uint8 value)
* ��flash�ڲ��������ݵĴ洢����ĵ�seq���indexλ��������value
* ��seqδ�����洢����ĳ��ȣ����ض�д�ɹ���Ӧֵ
* ��seq�����洢����ĳ��ȣ�����0xFF
**************************************/
uint8 flash_Rinfo_single_write(uint8 seq,uint8 index, uint8 value)
{
	uint8 temp[INFO_LENGTH]={0};
        osal_snv_read(seq, INFO_LENGTH, temp);
        if(seq<INFO_LENGTH)
        {
          temp[index]=value;
          return osal_snv_write(seq, INFO_LENGTH, temp);
        }else
        {
          return seq;
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
	uint8 temp[INFO_LENGTH]={0};
        osal_snv_read(0x82, INFO_LENGTH, temp);
        if(seq<INFO_LENGTH)
        {
          temp[seq]=value;
          return osal_snv_write(0x82, INFO_LENGTH, temp);
        }else
        {
          return 0xFF;
        }
}


/**************************************
* uint8 flash_Tinfo_Length_init(void��
* ��flash�ڲ���ʼ���������ݵĳ��ȴ洢λ
**************************************/
uint8 flash_Tinfo_Length_init(void)
{
    uint8 temp=0;
    //��ַ0x83�Ƿ������ݵĳ��ȵĴ洢����
    int8 ret8 = osal_snv_read(0x83, 1, &temp);
    // ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
    if(NV_OPER_FAILED == ret8)
    {
        // �����ݽṹ���浽flash
        osal_snv_write(0x83, 1, &temp); 
        osal_snv_read(0x83, 1, &temp);
    }
    return SUCCESS;
}




/**************************************
* uint8 flash_Tinfo_Length_set(uint8 length)
* ��flash�ڲ�д�뷢�����ݵĳ��ȴ洢λ
**************************************/
uint8 flash_Tinfo_Length_set(uint8 length)
{
	uint8 temp=0;
        temp=length;
        return osal_snv_write(0x83, 1, &temp);
}




/**************************************
* uint8 flash_Tinfo_Length_get(void)
* ��flash�ڲ���ȡ�������ݵĳ��ȴ洢λ
**************************************/
uint8 flash_Tinfo_Length_get(void)
{
        uint8 temp=1;
        osal_snv_read(0x83, 1, &temp);
        return temp;
}




/**************************************
* uint8 flash_Tinfo_short_write(void *pBuf, uint8 len)
* ��flash�ڲ�������������Ľ������ݵĳ���Ϊs
* ����s����д�볤��Ϊlen�����飬��ַ��pBuf
* �������洢���ȵ����ݲ�д
**************************************/
uint8 flash_Tinfo_short_write(void *pBuf, uint8 len)
{
        uint8 length=0;
        length=flash_Tinfo_Length_get();
        
        //����һ������ΪINFO_LENGTH������
        //uint16* inMem;
        //inMem= (uint16 *)osal_mem_alloc(INFO_LENGTH);
        //osal_memset(inMem,0,INFO_LENGTH);
        uint8 inMem[INFO_LENGTH]={0};
        
        osal_snv_read(0x82, INFO_LENGTH, inMem);
        uint8 i=0;
        for(i=0;i<len;i++)
        {
          if((length+i)<INFO_LENGTH)
          {
            inMem[length+i]=((uint8 *)pBuf)[i];
          }else
          {
            break;
          }
        }
        length=length+len;
        if(length>INFO_LENGTH)
        {
          length=INFO_LENGTH;
        }
	#if (defined HAL_LCD) && (HAL_LCD == TRUE)
        HalLcdWriteStringValue( "LVALUE = ", length, 10, HAL_LCD_LINE_6 );
	#endif
        flash_Tinfo_Length_set(length);
        
        //�ͷ��ڴ�
        osal_snv_write(0x82, INFO_LENGTH, inMem);
        //osal_mem_free(inMem);
        return 0;
}



/**************************************
* uint8 flash_Tinfo_short_read(void *pBuf, uint8 seq)
* ��flash�ڲ�������������ĵ�seq����ʼΪ��0λ����󣨰���seq����ȡ����10������
* �������洢���ȣ������������
* ��ֵ��pBuf��
**************************************/
uint8 flash_Tinfo_short_read(void *pBuf, uint8 seq)
{
  uint8 inMem[INFO_LENGTH]={0};
  osal_snv_read(0x82, INFO_LENGTH, inMem);
  
  uint8 temp[10]={0};
  
  
  uint8 i=0;
  for(i=0;i<10;i++)
  {
    if((seq+i)<INFO_LENGTH)
    {
      temp[i]=inMem[seq+i];
    }else
    {
      break;
    }
  }
  
  for(i=0;i<10;i++)
  {
    ((uint8 *)pBuf)[i]=temp[i];
  }
  return 0;
}






/**************************************
* uint8 flash_Rinfo_Length_init(void��
* ��flash�ڲ���ʼ���������ݵĳ��ȴ洢λ
**************************************/
uint8 flash_Rinfo_Length_init(uint8 seq)
{
    uint8 temp=0;
    //��ַ0x85�ǽ�����Ϣ�ĳ��ȵĴ洢����
    int8 ret8 = osal_snv_read(seq, 1, &temp);
    // ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
    if(NV_OPER_FAILED == ret8)
    {
        // �����ݽṹ���浽flash
        osal_snv_write(seq, 1, &temp); 
        osal_snv_read(seq, 1, &temp);
    }
    return SUCCESS;
}

/**************************************
* uint8 flash_Rinfo_init(uint8 seq)
* ��flash�ڲ���ʼ���������ݴ洢
**************************************/
uint8 flash_Rinfo_init(uint8 seq)
{
    uint16* temp;
    temp= (uint16 *)osal_mem_alloc(250);
    osal_memset(temp,0,250);
    //��ַ0x85�ǽ�����Ϣ�ĳ��ȵĴ洢����
    int8 ret8 = osal_snv_read(seq, INFO_LENGTH, temp);
    // ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
    if(NV_OPER_FAILED == ret8)
    {
        // �����ݽṹ���浽flash
        osal_snv_write(seq, INFO_LENGTH, temp); 
        osal_snv_read(seq, INFO_LENGTH, temp);
    }
    osal_mem_free(temp);
    return SUCCESS;
}



/**************************************
* uint8 flash_Rinfo_Length_set(uint8 length)
* ��flash�ڲ�д��������ݵĳ��ȴ洢λ
**************************************/
uint8 flash_Rinfo_Length_set(uint8 length)
{
	uint8 temp=0;
        temp=length;
        return osal_snv_write(0x85, 1, &temp);
}




/**************************************
* uint8 flash_Rinfo_Length_get(void)
* ��flash�ڲ���ȡ�������ݵĳ��ȴ洢λ
**************************************/
uint8 flash_Rinfo_Length_get(void)
{
        uint8 temp=1;
        osal_snv_read(0x85, 1, &temp);
        return temp;
}






/**************************************
* uint8 flash_Rinfo_short_write(void *pBuf, uint8 len)
* ��flash�ڲ�������������Ľ������ݵĳ���Ϊs
* ����s����д�볤��Ϊlen�����飬��ַ��pBuf
* �������洢���ȵ����ݲ�д
**************************************/
uint8 flash_Rinfo_short_write(void *pBuf, uint8 len)
{
        uint8 length=0;
        length=flash_Rinfo_Length_get();
        uint8 inMem[INFO_LENGTH]={0};
        
        osal_snv_read(0x84, INFO_LENGTH, inMem);
        uint8 i=0;
        for(i=0;i<len;i++)
        {
          if((length+i)<INFO_LENGTH)
          {
            inMem[length+i]=((uint8 *)pBuf)[i];
          }else
          {
            break;
          }
        }
        length=length+len;
        if(length>INFO_LENGTH)
        {
          length=INFO_LENGTH;
        }
	#if (defined HAL_LCD) && (HAL_LCD == TRUE)
        HalLcdWriteStringValue( "LVALUE = ", length, 10, HAL_LCD_LINE_6 );
	#endif
        flash_Rinfo_Length_set(length);
        return osal_snv_write(0x84, INFO_LENGTH, inMem);
}

/**************************************
* uint8 flash_Rinfo_short_read(void *pBuf, uint8 seq, uint8 pages)
* ��flash�ڲ�������������ĵ�pageҳ�ĵ�seq����ʼΪ��0λ��
* ��󣨰���seq����ȡ����9������
* �������洢���ȣ������������
* ��ֵ��pBuf��
**************************************/
uint8 flash_Rinfo_short_read(void *pBuf, uint8 seq, uint8 pages)
{
  //����һ������ΪINFO_LENGTH������
  uint16* inMem;
  inMem= (uint16 *)osal_mem_alloc(INFO_LENGTH);
  osal_memset(inMem,0,INFO_LENGTH);
  
  osal_snv_read(flash_RinfoPageAddress(pages), INFO_LENGTH, inMem);
  
  uint8 temp[9]={0};
  
  
  uint8 i=0;
  for(i=0;i<9;i++)
  {
    if((seq+i)<INFO_LENGTH)
    {
      temp[i]=inMem[seq+i];
    }else
    {
      break;
    }
  }
  
  for(i=0;i<9;i++)
  {
    ((uint8 *)pBuf)[i]=temp[i];
  }
  
  //�ͷ��ڴ�
  osal_mem_free(inMem);
  return 0;
}



/**************************************
* uint8 flash_Recinfo_Compare_Save(void *pBuf)
* ������5ҳflash������д�����ݣ��������ID���л��ߴ洢����
* �򲻴洢��һ�������IDȫΪ0�����������Դ洢
**************************************/
uint8 flash_Recinfo_Compare_Save(void *pBuf)
{
  uint8 uID[ID_LENGTH]={0};
  //��һ�������IDȫΪ0�������������Դ洢
  uint8 availID[ID_LENGTH]={0};
  int availableSEQ=-1;
  
  
  uint8 state=NOEXIST;
  
  for(int i=0;i<5;i++)
  {
    flash_Recinfo_getID(uID, flash_RinfoPageAddress(i));
    if(osal_memcmp(uID,pBuf,ID_LENGTH))
    {
      state=EXIST;
      continue;
    }else{
      if(osal_memcmp(uID,availID,ID_LENGTH))
      {
        availableSEQ=i;
        break;
      }
    }
  }
  
  if((state==NOEXIST)&&(availableSEQ!=-1))
  {
    flash_Rinfo_all_write(pBuf, flash_RinfoPageAddress(availableSEQ));
    flash_RINFO_addpages();
  }
  return 0;
}
/**************************************
* uint8 flash_Recinfo_getID(void *pBuf, uint8 add)
* ��ȡ�յ��Ĵ洢��Ϣseq�����ֵ�IDֵ
* 
**************************************/
uint8 flash_Recinfo_getID(void *pBuf, uint8 add)
{
  uint8 inMem[ID_LENGTH]={0};
  osal_snv_read(add, ID_LENGTH, inMem);
  
  for(int i=0;i<ID_LENGTH;i++)
  {
    ((uint8 *)pBuf)[i]=inMem[i];
  }
  return 0;
}

/**************************************
* uint8 flash_RinfoPageAddress(uint8 seq)
* ��ȡ�յ��Ĵ洢��Ϣ��seqҳ�ĵ�ַ
**************************************/
uint8 flash_RinfoPageAddress(uint8 seq)
{
  if((seq>=0)&&(seq<5))
  {
    return 0x84+2*seq;
  }
  return 0x84;
}

/**************************************
* uint8 flash_serialNumberInit(void);
* ���кŵĳ�ʼ��
**************************************/
uint8 flash_serialNumberInit()
{
    uint8 serial[SERIAL_LENGTH]={0};
    //��ַ0x8E�����к�
    int8 ret8 = osal_snv_read(SERIAL_ADDRESS, SERIAL_LENGTH, serial);
    // ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
    if(NV_OPER_FAILED == ret8)
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
  uint8 serial[SERIAL_LENGTH]={0};
  uint16 fulserial[SERIAL_LENGTH]={0};
  
  for(int i=0;i<SERIAL_LENGTH;i++)
  {
    fulserial[i]=osal_rand();
    serial[i]=LO_UINT16(fulserial[i]);
  }
  for(int i=0;i<SERIAL_LENGTH;i++)
  {
    ((uint8 *)pBuf)[i]=serial[i];
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


/**************************************
* uint8 flash_cashInit(void);
* ���ĳ�ʼ��
**************************************/
uint8 flash_cashInit()
{
    uint8 cash[CASH_LENGTH]={0};
    //��ַ0x8E�����к�
    int8 ret8 = osal_snv_read(CASH_ADDRESS, CASH_LENGTH, cash);
    // ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
    if(NV_OPER_FAILED == ret8)
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
    uint8 cash[CASH_LENGTH]={0};
    osal_snv_read(CASH_ADDRESS, CASH_LENGTH, cash);
    for(int i=0;i<CASH_LENGTH;i++)
    {
      ((uint8 *)pBuf)[i]=cash[i];
    }
    return SUCCESS;
}


/**************************************
* uint8 flash_RINFO_pagesInit(void);
* ��ʼ���洢ҳ��
**************************************/
uint8 flash_RINFO_pagesInit()
{
    uint8 pages=0;
    //��ַ0x8E�����к�
    int8 ret8 = osal_snv_read(INFO_PAGES_ADDR, INFO_PAGES_LEN, &pages);
    // ����ö��ڴ�δ��д������ݣ� ֱ�Ӷ����᷵�� NV_OPER_FAILED 
    if(NV_OPER_FAILED == ret8)
    {
        // �����ݽṹ���浽flash
        osal_snv_write(INFO_PAGES_ADDR, INFO_PAGES_LEN, &pages); 
        osal_snv_read(INFO_PAGES_ADDR, INFO_PAGES_LEN, &pages);
    }
    return SUCCESS;
}

/**************************************
* uint8 flash_RINFO_addpages(void);
*���Ӵ洢ҳ�������ӵ�MAXPAGES��ֹͣ
**************************************/
uint8 flash_RINFO_addpages()
{
    uint8 pages=0;
    osal_snv_read(INFO_PAGES_ADDR, INFO_PAGES_LEN, &pages);
    if((pages>=0)&&(pages<MAXPAGES))
    {
      pages=pages+1;
    }
    osal_snv_write(INFO_PAGES_ADDR, INFO_PAGES_LEN, &pages); 
    return SUCCESS;
}

/**************************************
* uint8 flash_RINFO_getpages(void);
* ��ȡ�洢ҳ��
**************************************/
uint8 flash_RINFO_getpages()
{
    uint8 pages=0;
    osal_snv_read(INFO_PAGES_ADDR, INFO_PAGES_LEN, &pages);
    return pages;
}



/**************************************
* uint8 flash_RINFO_setpages(uint8 pages);
* ���ô洢ҳ��
**************************************/
uint8 flash_RINFO_setpages(uint8 pages)
{
    osal_snv_write(INFO_PAGES_ADDR, INFO_PAGES_LEN, &pages); 
    return pages;
}


