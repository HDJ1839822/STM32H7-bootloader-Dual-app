
#include "string.h"
#include "stdio.h"
#include "boot_head.h"
#include "bsp_sd.h"


/* mkimageͷ�����ݽ��� */


/* 4�ֽڴ���ֽ���תС���ֽ��� */
uint32_t my_ntohl(uint32_t netlong) {
    return ((netlong & 0xFF000000) >> 24) |
           ((netlong & 0x00FF0000) >> 8) |
           ((netlong & 0x0000FF00) << 8) |
           ((netlong & 0x000000FF) << 24);
}



/*��ӡͷ����Ϣ*/
void printf_app_head(image_header_t *pimage_header_t){

	# if(0)   //���ڵ���
   printf("ih_magic in hexadecimal: 0x%x\r\n", my_ntohl(pimage_header_t->ih_magic));
	 printf("ih_hcrc in hexadecimal: 0x%x\r\n", my_ntohl(pimage_header_t->ih_hcrc));
	 printf("ih_time in hexadecimal: 0x%x\r\n", my_ntohl(pimage_header_t->ih_time));
	 printf("ih_size in hexadecimal: 0x%x\r\n", my_ntohl(pimage_header_t->ih_size));
	 printf("ih_load in hexadecimal: 0x%x\r\n", my_ntohl(pimage_header_t->ih_load));
	 printf("ih_ep in hexadecimal: 0x%x\r\n", my_ntohl(pimage_header_t->ih_ep));
	 printf("ih_dcrc in hexadecimal: 0x%x\r\n", my_ntohl(pimage_header_t->ih_dcrc));
	
	 printf("ih_os in hexadecimal: 0x%x\r\n",   pimage_header_t->ih_os);
	 printf("ih_arch in hexadecimal: 0x%x\r\n", pimage_header_t->ih_arch);
	 printf("ih_type in hexadecimal: 0x%x\r\n", pimage_header_t->ih_type);
	 printf("ih_comp in hexadecimal: 0x%x\r\n", pimage_header_t->ih_comp);
	 printf("| ih_name is: ");
   for (int i = 0; i < IH_NMLEN; i++) 
	 printf("%c", (unsigned char)pimage_header_t->ih_name[i]);  printf("\r\n");
	#else
	 printf("| ih_name   |");
   for (int i = 0; i < IH_NMLEN; i++) 
	 printf("%c", (unsigned char)pimage_header_t->ih_name[i]);  printf("\r\n");
	
	 printf("| ih_size   |  %u Byte    \r\n", my_ntohl(pimage_header_t->ih_size));
	 printf("| ih_load   |  0x%x       \r\n", my_ntohl(pimage_header_t->ih_load));
	 printf("| ih_ep     |  0x%x       \r\n", my_ntohl(pimage_header_t->ih_ep));
	 printf("| ih_hcrc   |  0x%x       \r\n", my_ntohl(pimage_header_t->ih_hcrc)); //ͷ��crc
	 printf("| ih_dcrc   |  0x%x       \r\n", my_ntohl(pimage_header_t->ih_dcrc)); //app crc32
	 printf("\r\n");
	#endif
 
}
	

//
uint32_t check_app_head(image_header_t *app_image_header_t, char *app_name) 
{
    int bytesRead = 0;  //��ȡ�ַ���

    bytesRead = readFileContent(app_name, app_image_header_t, sizeof(image_header_t), 0);

    if (bytesRead != sizeof(image_header_t)) {
			  printf(" boot ahead bytesRead err\r\n "); //��ȡ�ַ�������һ��
		    return -1;}
    else 
        printf_app_head(app_image_header_t); //��ӡmkimage ͷ����Ϣ
		   
		    return 0;	
 }

