#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/stddef.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haoming Bai");
MODULE_DESCRIPTION(
    "The second task of NPU operating system course's second lab.");

struct task_struct *thread;

void msleep(unsigned int msecs);

int thread_fn(void *) {
  struct file *file = NULL;
  while (!kthread_should_stop()) {
    msleep(1000);
    file = filp_open("/proc/loadavg", O_RDONLY, 0);
    if (IS_ERR(file)) {
      continue;
    }
    char buf[10];
    char out[100] = "The loadavg within 1 min is: ";
    kernel_read(file, buf, 4, NULL);
    buf[4] = 0;
    filp_close(file, 0);
    strncat(out, buf, 4);
    printk(KERN_INFO "%s", out);
  }
  return 0;
}

static int __init init_func(void) {
  printk(KERN_INFO "l2t2 loaded\n");
  thread = kthread_run(thread_fn, NULL, "l2t2");
  return 0;
}

static void __exit exit_func(void) {
  kthread_stop(thread);
  printk(KERN_INFO "l2t2 unloaded\n");
}

module_init(init_func);
module_exit(exit_func);
