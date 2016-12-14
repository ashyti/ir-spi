#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define LIRC_SET_SEND_CARRIER		1074030867
#define LIRC_SET_SEND_DUTY_CYCLE	1074030869

#define DSIZE	67

/*
unsigned int b[DSIZE] = { 0xab, 0xab, 16, 40, 16, 40, 16, 40,
			16, 15, 16, 15, 16, 14, 16, 15,
			16, 15, 16, 40, 16, 40, 16, 40,
			16, 15, 16, 15, 16, 15, 16, 15,
			16, 15, 16, 40, 16, 40, 16, 40,
			16, 15, 15, 15, 16, 15, 16, 15,
			16, 15, 16, 15, 16, 15, 16, 15,
			16, 40, 16, 40, 16, 40, 16, 40,
			16, 40, 16
};
*/

unsigned int b[DSIZE] = { 171, 171, 22, 64, 22, 64, 22, 64,
			22, 21, 22, 21, 22, 20, 22, 21,
			22, 21, 22, 64, 22, 64, 22, 64,
			22, 21, 22, 21, 22, 21, 22, 21,
			22, 21, 22, 64, 22, 64, 22, 64,
			22, 21, 21, 21, 22, 21, 22, 21,
			22, 21, 22, 21, 22, 21, 22, 21,
			22, 64, 22, 64, 22, 64, 22, 64,
			22, 64, 22
};

int main(void)
{
	int fd, ret;
	ssize_t n;
	uint32_t val;

	fd = open("/dev/lirc0", O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "unable to open the device\n");
		return -1;
	}

	/***** send test *****/
	val = 608000;
	ret = ioctl(fd, LIRC_SET_SEND_CARRIER, &val);
	if (ret < 0) {
		fprintf(stderr, "LIRC_SET_SEND_CARRIER failed\n");
		return -1;
	}

	val = 60;
	ret = ioctl(fd, LIRC_SET_SEND_DUTY_CYCLE, &val);
	if (ret < 0) {
		fprintf(stderr, "LIRC_SET_SEND_CARRIER failed\n");
		return -1;
	}

	n = write(fd, b, DSIZE * sizeof(unsigned int));
	if (n < 0) {
		fprintf(stderr, "unable to write to the device\n");
		ret = -1;
	} else if (n != DSIZE) {
		fprintf(stderr, "failed to write everything, wrote %ld instead\n", n);
		ret = -1;
	} else {
		fprintf(stdout, "wrote all the %ld data\n", n);
	}

	close(fd);
	return ret;
}
