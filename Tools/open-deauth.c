/* open-deauth.c - deauthorize the device while the SDK is in use. This
 * simulates what happens across a suspend/resume cycle where the device was in
 * use just before suspend. This test causes the SDK to spawn thousands of
 * threads and consume nearly all the machine's CPU for about 30 seconds.
 */

#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef unsigned char u8;

static void die(char *prefix) {
	perror(prefix);
	exit(1);
}

struct device {
	char name[256];
	char key[16];
};

#define NDEV 16

extern int QCWWANEnumerateDevices(u8 *size, struct device *devices);

static struct device *finddev(void) {
	int res;
	u8 size = NDEV;
	static struct device devices[NDEV];
	struct device *dev = &devices[0];

	res = QCWWANEnumerateDevices(&size, devices);
	if (res)
		die("QCWWANEnumerateDevices");
	if (size == 0)
		die("finddev: no devices");
	return dev;
}

extern int QCWWANConnect(const char *name, const char *key);

static void connect(const char *name, const char *key) {
	int res = QCWWANConnect(name, key);
	if (res)
		die("QCWWANConnect");
}

static void deauth(const char *dev) {
	char path[PATH_MAX];
	snprintf(path, sizeof(path), "/sys/bus/usb/devices/%s/authorized", dev);
	int f = open(path, O_WRONLY);
	if (f == -1)
		die("open");
	int bytes = write(f, "0", 1);
	if (bytes != 1)
		die("write");
	close(f);
}

extern int GetSerialNumbers(size_t esnsz, char *esn, size_t imeisz, char *imei,
                            size_t meidsz, char *meid);

static void getserials(void) {
	int res;
	char esn[1024];
	char imei[1024];
	char meid[1024];

	res = GetSerialNumbers(sizeof(esn), esn, sizeof(imei), imei,
	                       sizeof(meid), meid);
	if (res)
		die("GetSerialNumbers");
}

int main(int argc, char *argv[]) {
	struct device *dev;

	if (argc < 2) {
		printf("Usage: %s <usb device>\n", argv[0]);
		return 0;
	}

	dev = finddev();
	connect(dev->name, dev->key);
	deauth(argv[1]);
	getserials();
	printf("ok\n");
	return 0;
}
