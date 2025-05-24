#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include "linux/kern_levels.h"
#include "linux/printk.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haoming Bai");
MODULE_DESCRIPTION(
    "The second task of NPU operating system course's third lab.");

static struct file_system_type hmfs_fs_type = {
  .owner = THIS_MODULE,
  .name = "hmfs",
};

static int __init minit(void) {
  int reg_res = register_filesystem(&hmfs_fs_type);
  if (reg_res == 0) {
    printk(KERN_INFO "Register hmfs succeeded!");
  } else {
    printk(KERN_INFO "Register hmfs failed!");
  }
  return 0;
}

static void __exit mexit(void) {
  unregister_filesystem(&hmfs_fs_type);
  return;
}

module_init(minit);
module_exit(mexit);
