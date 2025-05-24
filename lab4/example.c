#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haoming Bai");
MODULE_DESCRIPTION(
    "The first task of NPU operating system course's third lab.");

static int __init minit(void) {
  return 0;
}

static void __exit mexit(void) {
  return;
}

module_init(minit);
module_exit(mexit);
