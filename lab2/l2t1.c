#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/stddef.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haoming Bai");
MODULE_DESCRIPTION(
    "The first task of NPU operating system course's second lab.");

struct task_struct *thread;

void msleep(unsigned int msecs);

static int thread_fn(void *parm) {
  for (; !kthread_should_stop();) {
    msleep(1000);
    printk(KERN_INFO "The thread has runned for another second");
  }
  return 0;
}

static int __init init_func(void) {
  printk(KERN_INFO "The first module of lab2 is loaded\n");
  thread = kthread_run(thread_fn, NULL, "l2t1");
  return 0;
}

static void __exit exit_func(void) {
  kthread_stop(thread);
  printk(KERN_INFO "The first module of lab2 is unloaded\n");
}

module_init(init_func);
module_exit(exit_func);
