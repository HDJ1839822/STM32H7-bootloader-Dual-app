#include "bootloader.h"
#include "stdint.h"
#include "bsp_qspi.h"

/*
QSPI FALSH 

����
APP:            0X0000 0000 ---> 0X003F EFFF      size : 0X3F F000    4M-4K
PARAMENT:       0X003F F000 ---> 0X003F FFFF      SIZE : 0X1000       4K

������
BACK APP1:      0X0040 0000 ---> 0X007F EFFF      size : 0X3F F000    4M-4K
BACK PARAMENT:  0X007F F000 ---> 0X007F FFFF      SIZE : 0X1000       4K

1.����Ϊ��״̬  ��������뱸�����Ƿ���CRC   ����CRC��ȡSD�����ݣ�δ��⵽SD�������shellģʽ�ȴ�rz
   �����������Ƿ��а汾��Ҫ���£�
2.��Ҫ����
3.�������


*/
   psqspi_flash pqspi_flash = &qspi_w26q64;
	 
	 
	 

 /* ��ȡϵͳ���������� */
int get_qspi_falsh_sys_parameny(uint32_t address){
	
	





}




int read_qspi_falsh_data(){
	  
   



}










uint32_t bootloade( ){
	
     //��ʼ��QSPI     
	   pqspi_flash->qspi_w25qxx_init(); 
	
	   //����AES
	
	   //���QSPI����
	   read_qspi_falsh_data();
	   
	   
	   

	



 return 0;

}


