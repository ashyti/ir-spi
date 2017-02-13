/*
 * ir-spi testing program
 * Copyright (C) 2017  Andi Shyti <andi.shyti@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

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
