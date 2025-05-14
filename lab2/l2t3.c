#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/mm_types.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/stddef.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haoming Bai");
MODULE_DESCRIPTION(
    "The third task of NPU operating system course's second lab.");

struct task_struct *thread;

void msleep(unsigned int msecs);

int thread_fn(void *param) {
  while (!kthread_should_stop()) {
    msleep(1000);
    struct task_struct *p;
    for_each_process(p) {
      if (p->__state == 0) {
        printk(KERN_INFO "1)name: %s 2)pid: %d 3)state %u", p->comm, p->pid,
               p->__state);
      }
    }
  }
  return 0;
}

static int __init init_func(void) {
  printk(KERN_INFO "l2t3 loaded\n");
  thread = kthread_run(thread_fn, NULL, "l2t3");
  return 0;
}

static void __exit exit_func(void) {
  kthread_stop(thread);
  printk(KERN_INFO "l2t3 unloaded\n");
}

module_init(init_func);
module_exit(exit_func);
