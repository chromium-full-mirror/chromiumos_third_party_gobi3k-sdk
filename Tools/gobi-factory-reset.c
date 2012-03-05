/* gobi-factory-reset.c - resets all Gobis to factory defaults */

#include <stdio.h>

#include <GobiConnectionMgmt/GobiConnectionMgmtAPI.h>

#define MAX_DEVICES   16

typedef struct device {
  char node[256];
  char key[16];
} device_t;

static int reset_device(device_t *dev, char *spc) {
  ULONG ret = QCWWANConnect(dev->node, dev->key);
  if (ret) {
    printf("Connect path '%s' key '%s': %lu\n", dev->node, dev->key, ret);
    return 1;
  }
  ret = ResetToFactoryDefaults(spc);
  if (ret) {
    printf("Reset path '%s' key '%s': %lu\n", dev->node, dev->key, ret);
    QCWWANDisconnect();
    return ret;
  }
  ret = QCWWANDisconnect();
  if (ret) {
    printf("Disconnect path '%s' key '%s': %lu\n", dev->node, dev->key, ret);
  }
  return ret;
}

int main(int argc, char *argv[]) {
  device_t devices[MAX_DEVICES];
  BYTE num_devices = MAX_DEVICES;
  ULONG ret;
  int i;

  if (argc != 2) {
    printf("Usage: %s <spc>\n", argv[0]);
    return 1;
  }

  ret = QCWWANEnumerateDevices(&num_devices, (BYTE*)devices);
  if (ret) {
    printf("EnumerateDevices: %lu\n", ret);
    return 2;
  }

  for (i = 0; i < num_devices; i++) {
    ret = ret || reset_device(&devices[i], argv[1]);
  }

  return ret ? 3 : 0;
}
