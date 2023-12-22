
#include "command.h"
#include "uart.h"
#include "stdio.h"


#define CRC32_POLYNOMIAL 0xEDB88320u
//���������                   �����׵�ַ     ���ݴ�С
static uint32_t calculate_crc32(const void *data, size_t size) {
    const uint8_t *byteData = (const uint8_t *)data;
    uint32_t crc = 0xFFFFFFFFu;

    for (size_t i = 0; i < size; ++i) {
        crc ^= byteData[i];
        for (int j = 0; j < 8; ++j) {
            crc = (crc >> 1) ^ ((crc & 1) ? CRC32_POLYNOMIAL : 0);
        }
    }

    return ~crc;
}




static int crc32(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: crc32 <start_address> <size_in_bytes>\r\n");
        return 1;  // ���ش�����
    }

    // �������в����л�ȡ��ʼ��ַ�ʹ�С
    uint32_t dataStartAddress;
    size_t dataSizeInBytes;

    if (sscanf(argv[1], "%x", &dataStartAddress) != 1) {
        fprintf(stderr, "Invalid start address\r\n");
        return 1;
    }

    if (sscanf(argv[2], "%zu", &dataSizeInBytes) != 1) {
        fprintf(stderr, "Invalid size\r\n");
        return 1;
    }

    // ���� CRC32
    uint32_t crcResult = calculate_crc32((const void *)dataStartAddress, dataSizeInBytes);

    // �������õ��� CRC32 ֵ
    printf("CRC32: 0x%x\r\n", crcResult);

    return 0;  // ���سɹ���
}




struct command crc32_cmd = {
	"crc32",
		
	"view crc32\r\n",
	
	"Usage: \r\n"
  "       crc32  <ram_base_addr>  <size>\r\n",
	crc32,
};















