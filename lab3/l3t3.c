#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#include "linux/kern_levels.h"
#include "linux/printk.h"
#include "linux/stddef.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haoming Bai");
MODULE_DESCRIPTION(
    "The third task of NPU operating system course's third lab.");

static struct proc_dir_entry *dir;

static int __init minit(void) {
  dir = proc_mkdir("arch", NULL);
  __auto_type curr = dir;
  if (curr == NULL) {
    printk(KERN_ERR "Create dir \"arch\" failed!");
  }
  curr = proc_mkdir("is", curr);
  if (curr == NULL) {
    printk(KERN_ERR "Create dir \"is\" failed!");
  }
  curr = proc_mkdir("the", curr);
  if (curr == NULL) {
    printk(KERN_ERR "Create dir \"the\" failed!");
  }
  curr = proc_mkdir("best", curr);
  if (curr == NULL) {
    printk(KERN_ERR "Create dir \"best\" failed!");
  }
  return 0;
}

static void __exit mexit(void) {
  proc_remove(dir);
  printk(KERN_INFO "Remove /arch/is/the/best !");
  return;
}

module_init(minit);
module_exit(mexit);
