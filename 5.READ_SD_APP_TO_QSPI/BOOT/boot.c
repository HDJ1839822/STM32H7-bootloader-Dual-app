#include "boot.h"

#include "bsp_qspi.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_sd.h" 
#include "bsp_sdram.h" 



/* QSPI ��ӳ��Ļ���ַ*/
#define     QSPI_BASE_ADDRESS  0x90000000UL

/* SDRAM ��ӳ��Ļ���ַ*/
#define     SDRAM_TARGET_ADDR  0xC1000000UL

/* SD����SDRAM���� �ԱȻ�����*/
#define     BLOCK_SIZE         1024   // 1KB

/* ��ȡ�ļ��� */
#define     APP_FILE_NAME      "app.bin"




 typedef  void (*pFunction)(void);
 pFunction JumpToApplication;
  

 void jump_app(void);
 int  qspi_init_and_enable_MemoryMapMode(void);
 void display_logo(void);
 void read_sd_data_to_QSPI(void);


void  jump_to_qspi_flash(void)
{
	
	read_sd_data_to_QSPI();
	
	
//	 bsp_sdram_init();
	
//   sd_application();
	
	
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




/* �Է���һ ���������qspiʱ�ӹ��ˣ��������qspiʱ�� */
void enable_qspi_clk(void)
{
  __HAL_RCC_QSPI_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
	
  __HAL_RCC_FMC_CLK_ENABLE(); /* �������ˣ����ʱ�ӱ��뿪 ûϸ�����ʱ����QSPI��ϵ  */
}






/* ȷ��һ���ɾ���bootloader ������Ҫ���ʼ���õ������������Լ��ж�  ֻ����QSPI����APP�оͲ���Ҫ��QSPI�� */
/* �ܿ�: �ڽ��ʼ����ʱ��ע�ⲻҪ��QSPI��ʱ��Ҳ���ʼ���� �е�������QSPIһ��ʱ�ӣ����ʼ��֮��Ͳ�������
   ������������������ʼ��֮�� �ٶ�����QSPI�Ƿ����� */
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
	
	
	 /* ���ʼ�� SD�� */
	 HAL_SD_MspDeInit(&hsd1);
		
		
	 /* ���ʼ�� SDRAM */
	 HAL_SDRAM_MspDeInit(&hsdram1);
		
	 
	 /*���ʼ��LED*/ 
	 HAL_GPIO_DeInit(LED_R_GPIO_Port,LED_R_Pin);
	 HAL_GPIO_DeInit(LED_B_GPIO_Port,LED_R_Pin);
		
	 /*���ʼ�� SD_CAP*/
	 HAL_GPIO_DeInit(SD_CAP_GPIO_Port,SD_CAP_Pin);
		
		
	 /*���ʼ��usart */
   HAL_UART_MspDeInit(&huart4);
	 
	
	/*��������ʱ��Ĭ��״̬�ָ�HSI*/
	 HAL_RCC_DeInit();
	 
	 /* Ϊ��ֹqspiʱ�� ����ʼ�� */
	 enable_qspi_clk();
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




 FILINFO fileInfo;

/*��SD���ݶ�ȡ��sdram
  ��SD���ݶ�ȡ��1k����,��sdram��������ÿ���ֽڽ���У��  ѭ����ȡ����У��
*/


int read_sd_data_to_sdram(void)
{
    
    FRESULT res;
    uint32_t bytesRead;
    uint8_t* sdram_ptr = (uint8_t*)SDRAM_TARGET_ADDR;  // ָ��SDRAM��ָ��
    uint8_t temp_buffer[BLOCK_SIZE];  // ��ʱ������

    // ��ȡ�ļ���Ϣ
    res = f_stat(APP_FILE_NAME, &fileInfo);
    if (res != FR_OK)
    {
        printf("  Error getting file info.\r\n"); /*�ļ�������*/
        return -1;
    }
    else
    {
        printf("  The size of the file  %s is %ld bytes.\r\n", APP_FILE_NAME,fileInfo.fsize); /*��ȡ�ļ���С*/
    }

    // ��ȡ�����ļ���SDRAM
    bytesRead = readFileContent(APP_FILE_NAME, sdram_ptr, fileInfo.fsize+1, 0);
		
    if (bytesRead != fileInfo.fsize)
    {
        printf("  Error reading the entire file.\r\n");
        return -1;
    }

    // ��1KB�Ŀ��С����У��
    for (uint32_t i = 0; i < fileInfo.fsize; i += BLOCK_SIZE)
    {
        // ���ļ��ж�ȡ1KB�Ŀ鵽��ʱ������
        bytesRead = readFileContent(APP_FILE_NAME, temp_buffer, BLOCK_SIZE, i);
        if (bytesRead != BLOCK_SIZE && i + bytesRead != fileInfo.fsize)
        {
            printf("  Error reading the file block to temp buffer.\r\n");
            return -1;
        }

        // �Ƚ�SDRAM�еĿ����ʱ�������е�����
        if (memcmp(sdram_ptr + i, temp_buffer, bytesRead) != 0)
        {
            printf("  Data mismatch detected at block starting from byte %d.\r\n", i);
            return -1;
        }
    }

    printf("  Data in SDRAM check the file content success.\r\n");
		return 0;
		
}



  #define BUFFER_SIZE 1024
  #define W25Q64JV_SECTOR_SIZE   0x1000

  /* ��sdram������д��qspi flash ��У�� */
  int write_sdram_data_to_qspi_flash(void)
  {

		
    uint8_t* sdram_data_ptr = (uint8_t*)SDRAM_TARGET_ADDR;
		uint8_t* qspi_data_ptr = (uint8_t*)QSPI_BASE_ADDRESS;
		
    uint32_t remaining_bytes = fileInfo.fsize;
    
	//	uint8_t read_buffer[BUFFER_SIZE];
  //	uint32_t bytes_to_compare;
  //  uint32_t offset = 0;
		
		
		
    QSPI_W25Qxx_Init();
		
		/* �жϹ̼������ݴ�С ȷ����Ҫ�����ĵ�ַ 0������ʼ */
		uint32_t start_sector = 0;  // ��������ʼ�մ�����0��ʼ
    uint32_t end_sector = (fileInfo.fsize + W25Q64JV_SECTOR_SIZE - 1) / W25Q64JV_SECTOR_SIZE - 1;  // �������������

    uint32_t sectors_need_Erase_num = end_sector - start_sector + 1;  // ������Ҫ��������������

    printf("  fileInfo.fsize=%ld\r\n", fileInfo.fsize);
    printf("  sectors_need_Erase_num = %04d\r\n", sectors_need_Erase_num);

	
		/* ����ʹ�õ������� ������С������4k������ */
   for (uint32_t i = 0; i < sectors_need_Erase_num; i++) {
		 
		   if(QSPI_W25Qxx_SectorErase((i * W25Q64JV_SECTOR_SIZE))==QSPI_W25Qxx_OK) { // ʹ��i��ȷ��Ҫ������������ַ
   
		   /*�����ɹ�*/
		    printf("  qspi erase %d sectors success!!!\r\n",i);
		}
		 else{
		  /*����ʧ��*/
			 printf("  qspi erase err!!!\r\n");
			 return -1;
			 
		 }
		 
   }
	 
	
		
		/* д������ */
		if(QSPI_W25Qxx_WriteBuffer(sdram_data_ptr, 0x0, fileInfo.fsize)!=QSPI_W25Qxx_OK)
		{
		 return -1;
		}
	
    
//    /* ���ڴ�ӳ��ģʽ�µ�����У�� */
//		while (remaining_bytes > 0) {
//    // ������һ��Ҫ�Ƚϵ��ֽ���
//    bytes_to_compare = (remaining_bytes > BUFFER_SIZE) ? BUFFER_SIZE : remaining_bytes;

//    // ��QSPI Flash�ж�ȡ����
//    QSPI_W25Q64JV_Read(read_buffer, offset, bytes_to_compare);

//    // ���ֽڱȽ�SDRAM�ͻ������е�����
//    for (uint32_t i = 0; i < bytes_to_compare; i++) {
//        if (read_buffer[i] != sdram_data_ptr[offset + i]) {
//					 /*��ӡУ�������Ϣ*/
//            printf("Mismatch at offset 0x%X: QSPI=0x%02X, SDRAM=0x%02X\r\n", 
//                   offset + i, read_buffer[i], sdram_data_ptr[offset + i]);
//            return -1;  // У��ʧ��
//        }
//    }

//    // ����ʣ���ֽ�����ƫ����
//    remaining_bytes -= bytes_to_compare;
//    offset += bytes_to_compare;
//   } 
//		/* ����ִ�е�������У��ɹ� */
//		printf("  qspi not memorymap checkout success!!!\r\n");
		

    /* �����ڴ�ӳ��ģʽ�ٽ���У�� */
		QSPI_W25Qxx_MemoryMappedMode();
		
		
		/* qspi�ڴ�ӳ��ģʽ����sdram������У�� */
		if(memcmp(sdram_data_ptr, qspi_data_ptr, remaining_bytes) == 0) {
			
		printf("  qspi  memorymap data check success!!!\r\n");
			
	 }
		else{
			printf("  qspi  memorymap data check err!!!\r\n");
		 return -1;
		}
		
		return 0;
	
}





  /*  ����SD��������ˢ�뵽QSPI ����ַ */
 void read_sd_data_to_QSPI(void)
 {
	   bsp_sd_init(); /* ����SD ��ʧ�ܻ�ִֹͣ�� */
	 
	   SDRAM_InitSequence();/*��ʼ��sdram*/
	 
     if(read_sd_data_to_sdram()==0) /* �Ƚ�sd��sdram����һ�� */
		 {
		  write_sdram_data_to_qspi_flash(); /* ��sdram������д��qspi �����ڴ�ӳ��ģʽ �Ƚ���sdram����һ�� */
		 }
   
 }

