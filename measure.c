#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"

long long get_nanosecond()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

int main()
{
    char buf[1];
    char write_buf[] = "testing writing";
    int offset = 92; /* TODO: try test something bigger than the limit */

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    for (int i = 0; i <= offset; i++) {
        long long start, ktime, utime;
        lseek(fd, i, SEEK_SET);
        start = get_nanosecond();
        read(fd, buf, 1);
        utime = get_nanosecond - start;
        ktime = write(fd, write_buf, 0);

        printf("%d %lld %lld %lld\n", i, ktime, utime, utime - ktime);
    }

    close(fd);
    return 0;
}
