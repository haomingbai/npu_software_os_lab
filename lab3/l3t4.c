#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>

#include "linux/dynamic_debug.h"
#include "linux/moduleparam.h"
#include "linux/printk.h"
#include "linux/sched.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haoming Bai");
MODULE_DESCRIPTION(
    "The forth task of NPU operating system course's third lab.");

unsigned int msleep(unsigned int msecs);

static int paramA, paramB, paramC;

module_param(paramA, int, 0664);
MODULE_PARM_DESC(paramA, "The paramater A of the l3t4");
module_param(paramB, int, 0664);
MODULE_PARM_DESC(paramB, "The paramater A of the l3t4");
module_param(paramC, int, 0664);
MODULE_PARM_DESC(paramC, "The paramater A of the l3t4");

static int thread_fn(void *param) {
  int currA = paramA, currB = paramB, currC = paramC;
  while (!kthread_should_stop()) {
    if (paramA != currA) {
      currA = paramA;
      printk(KERN_INFO "The A param has been changed to %d", currA);
    }
    if (paramB != currB) {
      currB = paramB;
      printk(KERN_INFO "The B param has been changed to %d", currB);
    }
    if (paramC != currC) {
      currC = paramC;
      printk(KERN_INFO "The C param has been changed to %d", currC);
    }
    msleep(1000);
  }
  return 0;
}

struct task_struct *th;

static int __init minit(void) {
  th = kthread_run(thread_fn, NULL, "watch thread");
  return 0;
}

static void __exit mexit(void) {
  kthread_stop(th);
  return;
}

module_init(minit);
module_exit(mexit);
