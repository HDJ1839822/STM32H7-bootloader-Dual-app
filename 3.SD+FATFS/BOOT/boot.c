#include "boot.h"

#include "bsp_qspi.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_sd.h" 




/* QSPI ��ӳ��Ļ���ַ*/
#define QSPI_BASE_ADDRESS  0X90000000UL
 
 typedef  void (*pFunction)(void);
 pFunction JumpToApplication;
 
 
 
 

 void jump_app(void);
 int  qspi_init_and_enable_MemoryMapMode(void);
 void display_logo(void);



void  jump_to_qspi_flash(void)
{
	
   sd_application();
	
	
//	 /* �����ڴ�ӳ�� success*/
//	 if(qspi_init_and_enable_MemoryMapMode() == 0)
//	 {
//	  display_logo(); 
//		
//	  jump_app();
//	
//	 }
//	 else  /* ��⵽QSPIδ������ʼ��|δ�����ڴ�ӳ��ģʽ */
//	 {
//		 while(1)
//		 {
//		  LEDR_TOGGLE();
//			delay_ms(500);
//		 }
//	 }
}




/* return 0: success     return -1: err */
int qspi_init_and_enable_MemoryMapMode(void)
{
   volatile uint8_t id[2];
    
    if(QSPI_W25Qxx_Init()==QSPI_W25Qxx_OK){   /* qspi init */
			  printf(" QSPI Init success \r\n");
			
			  if(QSPI_W25Qxx_MemoryMappedMode()==QSPI_W25Qxx_OK){  /* start MemoryMappedMode */
				printf(" QSPI Start Memory Map success \r\n\r\n\r\n");	
				return 0;	
				}else{
				
				  printf(" QSPI Start Memory Map err \r\n ");
				  return -1;
				}					
	  }
		else{
			 printf(" QSPI Init err \r\n ");
			 return -1;
		 }
}


/* ȷ��һ���ɾ���bootloader ������Ҫ���ʼ���õ������������Լ��ж�  ֻ����QSPI����APP�оͲ���Ҫ��QSPI�� */
void DeInit_all_bsp_and_IRQ(void)
{ 
   SCB_DisableICache();		// �ر�ICache
	 SCB_DisableDCache();		// �ر�Dcache
 	
	 SysTick->CTRL = 0;		// �ر�SysTick
	 SysTick->LOAD = 0;		// ��������ֵ
	 SysTick->VAL = 0;		// �������ֵ
	
	
	 /* �ر������жϣ���������жϹ����־ */
    for (int i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ICPR[i] = 0xFFFFFFFF;
    } 
	 
	 /*���ʼ��LED*/ 
	 HAL_GPIO_DeInit(LED_R_GPIO_Port,LED_R_Pin);
	 HAL_GPIO_DeInit(LED_B_GPIO_Port,LED_R_Pin);
	 
	 /*���ʼ��usart */
   HAL_UART_MspDeInit(&huart4);
	 
	 /*��������ʱ��Ĭ��״̬�ָ�HSI*/
	 HAL_RCC_DeInit();
}





 void jump_app(void)
 {
	/* ���ʼ�������������ж� */
	DeInit_all_bsp_and_IRQ();
	 
	/* ȷ��CPU����Ӧ�κ��жϣ����������Ƿ�ʹ�ܡ�   ע����app����Ҫ�ֶ������ж� __enable_irq(); */
	__disable_irq();
	 

	JumpToApplication = (pFunction) (*(__IO uint32_t*) (QSPI_BASE_ADDRESS + 4));	// ������ʼ��ַ
	__set_MSP(*(__IO uint32_t*) QSPI_BASE_ADDRESS);	// ��������ջָ��

   
	JumpToApplication();			// ִ����ת
 }
 
 
 
 
 /*     logo ������վ��http://patorjk.com/software/taag/       */
 
 void display_logo(void)
{
	                                                                                                                                                                   
  printf("'  BBBBBBBBBBBBBBBBB        OOOOOOOOO          OOOOOOOOO     TTTTTTTTTTTTTTTTTTTTTTT\r\n");
  printf("'  B::::::::::::::::B     OO:::::::::OO      OO:::::::::OO   T:::::::::::::::::::::T\r\n");
  printf("'  B::::::BBBBBB:::::B  OO:::::::::::::OO  OO:::::::::::::OO T:::::::::::::::::::::T\r\n");
  printf("'  BB:::::B     B:::::BO:::::::OOO:::::::OO:::::::OOO:::::::OT:::::TT:::::::TT:::::T\r\n");
  printf("'    B::::B     B:::::BO::::::O   O::::::OO::::::O   O::::::OTTTTTT  T:::::T  TTTTTT\r\n");
  printf("'    B::::B     B:::::BO:::::O     O:::::OO:::::O     O:::::O        T:::::T        \r\n");
  printf("'    B::::BBBBBB:::::B O:::::O     O:::::OO:::::O     O:::::O        T:::::T        \r\n");
  printf("'    B:::::::::::::BB  O:::::O     O:::::OO:::::O     O:::::O        T:::::T        \r\n");
  printf("'    B::::BBBBBB:::::B O:::::O     O:::::OO:::::O     O:::::O        T:::::T        \r\n");
  printf("'    B::::B     B:::::BO:::::O     O:::::OO:::::O     O:::::O        T:::::T        \r\n");
  printf("'    B::::B     B:::::BO:::::O     O:::::OO:::::O     O:::::O        T:::::T        \r\n");
  printf("'    B::::B     B:::::BO::::::O   O::::::OO::::::O   O::::::O        T:::::T        \r\n");
  printf("'  BB:::::BBBBBB::::::BO:::::::OOO:::::::OO:::::::OOO:::::::O      TT:::::::TT      \r\n");
  printf("'  B:::::::::::::::::B  OO:::::::::::::OO  OO:::::::::::::OO       T:::::::::T      \r\n");
  printf("'  B::::::::::::::::B     OO:::::::::OO      OO:::::::::OO         T:::::::::T      \r\n");
  printf("'                                                                                   \r\n");
	printf("'                                                                                   \r\n");
	printf("'  www.newbie.pics                                                                  \r\n");
	printf("'                                                                                   \r\n");
	printf("'                                                                                   \r\n");
	printf("'                                                                                   \r\n");
	printf("'                                                                                   \r\n");

}

