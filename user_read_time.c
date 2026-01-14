#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEV_PATH "/dev/virtchar7_time"

int main(void)
{
    int fd = open(DEV_PATH, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buf[128] = {0};
    ssize_t n = read(fd, buf, sizeof(buf)-1);
    if (n < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    buf[n] = '\0';
    printf("Kernel time: %s", buf);

    /* Друге читання покаже новий час (перечитування файлу) */
    lseek(fd, 0, SEEK_SET);
    n = read(fd, buf, sizeof(buf)-1);
    if (n >= 0) {
        buf[n] = '\0';
        printf("Kernel time again: %s", buf);
    }

    close(fd);
    return 0;
}
