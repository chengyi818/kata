#include <sys/types.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define MYCDEV_CLEAN 0x6b30
#define MYCDEV_GETVALUE 0x80046b31
#define MYCDEV_SETVALUE 0x80046b32
#define UNUSED(x) (void)(x)

int main(int argc, const char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);
    int fd;
    int n;
    int len;
    char rec[1024] = "";
    char buf[1024] = "hello cdev";

    // open
    fd = open("/dev/mycdev0", O_RDWR);
    if(fd < 0) {
        perror("Fail to open\n");
        return -1;
    }
    printf("open successful, fd = %d\n", fd);

    // ioctl
    ioctl(fd, MYCDEV_CLEAN);
    ioctl(fd, MYCDEV_GETVALUE, &len);
    ioctl(fd, MYCDEV_SETVALUE, 8);
    printf("cdev.len = %d\n", len);

    // write
    n = write(fd, buf, strlen(buf));
    if(n < 0) {perror("Fail to write\n");
        return -1;
    }
    printf("write %d bytes!\n", n);

    lseek(fd, 0, SEEK_SET);
    // close and reopen
    /* close(fd); */
    /* fd = open("/dev/mycdev0", O_RDWR); */
    /* if(fd < 0) { */
    /*     perror("Fail to open\n"); */
    /*     return -1; */
    /* } */
    /* printf("open successful, fd = %d\n", fd); */

    // read
    n = read(fd, rec, 0x51);
    if(n < 0 ) {
        perror("Fail to read\n");
        return -1;
    }
    printf("read %d bytes!\n", n);
    printf("rec = %s\n", rec);

    return 0;
}
