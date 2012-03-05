/* sdk-stress.c - repeatedly disconnect uncleanly from the SDK
 * This test exposes a bug in the Qualcomm kernel driver - it is unable to
 * cleanly handle disconnects that are caused by abnormal process termination.
 * Basically, the desired behavior is:
 *   Process 1 calls QCWWANConnect() successfully
 *   Process 1 terminated abnormally
 *   Process 2 calls QCWWANConnect() successfully
 * Currently, Process 2's call will fail with error code 10.
 * This problem prevents us from restarting cromo if it crashes, since the
 * restarted instance won't be able to connect to the device.
 *
 * Copyright (c) 2010 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef unsigned char u8;
typedef unsigned long u64;

struct device {
	char name[256];
	char key[16];
};

#define NDEV 16

extern u64 QCWWANEnumerateDevices(u8 *size, struct device *devices);
extern u64 QCWWANConnect(char *name, char *key);

static void test(struct device *dev) {
	u64 res = QCWWANConnect(dev->name, dev->key);
	printf("%d: connect: %lu\n", getpid(), res);
	if (res)
		exit(1);
	sleep(2);
	exit(0);
}

int main(void) {
	u8 size = NDEV;
	struct device devices[NDEV];
	int res;
	int status;
	unsigned int i;

	res = QCWWANEnumerateDevices(&size, devices);
	if (res)
		return -1;
	for (i = 0; i < size; i++) {
		printf("%d device: %s %s\n", getpid(), devices[i].name,
		       devices[i].key);
	}

	while (1) {
		printf("%d attempt\n", getpid());
		res = fork();
		if (res < 0)
			return -2;
		if (!res)
			test(&devices[0]);
		sleep(1);
		kill(res, SIGKILL);
		res = wait(&status);
		printf("%d wait %d %d\n", getpid(), res, status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			printf("%d failed\n", res);
	}

	return 0;
}
