#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*该程序的功能就是为BL2添加校验码。
 *【BL2 不能大于(14K ????4B) 字节，最后 4B用于存放较验码】
 */
int main (int argc, char *argv[])
{
    FILE *fp;
    unsigned char src;
    char *buf, *a;
    int buf_len;
    int nbytes, file_len;
    unsigned int checksum = 0;
    int i;

    if (argc != 4) {
        printf("Usage: mkbl2 <source file> <destination file> <size> \n");
        return -1;
    }

    buf_len = atoi(argv[3]);
    buf = (char *)malloc(buf_len);
    memset(buf, 0x00, buf_len);

    fp = fopen(argv[1], "rb");
    if( fp == NULL) {
        printf("source file open error\n");
        free(buf);
        return -1;
    }

    fseek(fp, 0L, SEEK_END);
    file_len = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    nbytes = fread(buf, 1, file_len, fp);

    if (nbytes != file_len) {
        printf("source file read error\n");
        free(buf);
        fclose(fp);
        return -1;
    }

    fclose(fp);

    for(i = 0; i < (14 * 1024) - 4; i++)
        checksum += (unsigned char)(buf[i]);

    *(unsigned int*)(buf + i) = checksum;

    fp = fopen(argv[2], "wb");
    if (fp == NULL) {
        printf("destination file open error\n");
        free(buf);
        return -1;
    }

    a = buf;
    nbytes = fwrite(a, 1, buf_len, fp);

    if (nbytes != buf_len) {
        printf("destination file write error\n");
        free(buf);
        fclose(fp);
        return -1;
    }

    free(buf);
    fclose(fp);
    return 0;
}
