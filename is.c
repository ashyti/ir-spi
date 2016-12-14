#include <fcntl.h>
#include <linux/lirc.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

unsigned int b[67] = { 171, 171, 22, 64, 22, 64, 22, 64,
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

	n = write(fd, b, sizeof(b));
	if (n < 0) {
		fprintf(stderr, "unable to write to the device\n");
		ret = -1;
	} else if (n != sizeof(b)) {
		fprintf(stderr, "failed to write everything, wrote %ld instead\n", n);
		ret = -1;
	} else {
		fprintf(stdout, "wrote all the %ld data\n", n);
	}

	close(fd);
	return ret;
}
