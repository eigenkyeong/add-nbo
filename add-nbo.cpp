#include <stdint.h>
#include <stdio.h>

uint32_t my_ntohl(uint32_t n) {
    uint32_t n1 = (n & 0xff000000) >> 24;
    uint32_t n2 = (n & 0x00ff0000) >> 8;
    uint32_t n3 = (n & 0x0000ff00) << 8;
    uint32_t n4 = (n & 0x000000ff) << 24;
    return n1 | n2 | n3 | n4;
}

int main(int argc, char *argv[])
{
    FILE *fd1 = NULL;
    FILE *fd2 = NULL;
    uint8_t buf1[5];
    uint8_t buf2[5];

    if (argc != 3) {
        printf("Wrong input\n");
        return 1;
    }

    fd1 = fopen(argv[1], "r");
    fd2 = fopen(argv[2], "r");
    if(!fd1 || !fd2){
        printf("Fail to open the input file\n");
        return 1;
    }
    fread(buf1, sizeof(uint8_t), 4, fd1);
    fread(buf2, sizeof(uint8_t), 4, fd2);

    uint32_t *p = reinterpret_cast<uint32_t*>(buf1);
    uint32_t n1 = my_ntohl(*p);

    uint32_t *q = reinterpret_cast<uint32_t*>(buf2);
    uint32_t n2 = my_ntohl(*q);

    int result = n1 + n2;

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", n1, n1, n2, n2, result, result);

    if (fd1) fclose(fd1);
    if (fd2) fclose(fd2);
}
