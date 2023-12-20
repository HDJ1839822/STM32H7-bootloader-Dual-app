#ifndef __BOOT_H
#define __BOOT_H

#include "stdint.h"

typedef uint32_t  __be32;

typedef struct {
	uint8_t jump_time;          /* ��ת����ʱ�� */
	uint8_t which_app_running;  /* ѡ��app����  APP1/APP2*/
	uint8_t sys_parameter_flag; /* ��һ��ʹ��QSPI����־λ */
	uint8_t debug_flag;         /* ��ӡ���Կ�����־λ  1�������� 0�رյ���*/
}BOOT_SYS_config; /* ϵͳ���ò��� */



typedef struct{
uint32_t app1_size;
uint32_t app2_size;
}APP_SIZE; /* app��С(�ֽ�) */



#define IH_NMLEN	32	/* Image Name Length		*/
typedef struct image_header {
	__be32		ih_magic;	/* Image Header Magic Number	*/
	__be32		ih_hcrc;	/* Image Header CRC Checksum	*/
	__be32		ih_time;	/* Image Creation Timestamp	*/
	__be32		ih_size;	/* Image Data Size		*/
	__be32		ih_load;	/* Data	 Load  Address		*/
	__be32		ih_ep;		/* Entry Point Address		*/
	__be32		ih_dcrc;	/* Image Data CRC Checksum	*/
	uint8_t		ih_os;		/* Operating System		*/
	uint8_t		ih_arch;	/* CPU architecture		*/
	uint8_t		ih_type;	/* Image Type			*/
	uint8_t		ih_comp;	/* Compression Type		*/
	uint8_t		ih_name[IH_NMLEN];	/* Image Name		*/
} image_header_t,*pimage_header_t;



void  jump_to_qspi_flash(void);



#endif
