#include <asm/trace/fpu.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/preempt.h>
#include <linux/stddef.h>
#include <linux/time.h>

#include "linux/gfp_types.h"
#include "linux/kern_levels.h"
#include "linux/printk.h"
#include "linux/sched.h"
#include "linux/sched/task.h"
#include "linux/slab.h"
#include "linux/timekeeping.h"
#include "linux/types.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haoming Bai");
MODULE_DESCRIPTION(
    "The first task of NPU operating system course's third lab.");

void msleep(uint);

static int thread_fn(void *param) {
  typedef char *BKString;
  BKString path = "/test_file";
  size_t single_size = 1 << 20;
  size_t times = 4096;
  void *data = kmalloc(single_size, GFP_KERNEL);
  if (data == NULL) {
    printk(KERN_ERR "Memory alloc failed!");
    goto wait_stop;
  }
  for (size_t i = 0; i < single_size; i++) {
    BKString str = "Hamoming Bai\n";
    ((char *)data)[i] = str[i % 13];
  }

  typedef struct file file;
  file *test_file = filp_open(path, O_CREAT | O_RDWR, 0644);
  if (test_file == NULL) {
    printk(KERN_ERR "File open failed!");
    goto wait_stop;
  }

  kernel_fpu_begin();
  double res = 0;
  kernel_fpu_end();

  long long pos = 0;
  printk(KERN_INFO "Start kernel writing test!");
  for (size_t i = 0; i < times; i++) {
    double curr;
    typedef struct timespec64 timespec;
    timespec t_start, t_end;

    preempt_disable();
    ktime_get_ts64(&t_start);
    kernel_write(test_file, data, single_size, &pos);
    ktime_get_ts64(&t_end);
    preempt_enable();

    kernel_fpu_begin();
    double time_interval =
        (double)(t_end.tv_sec - t_start.tv_sec) +
        1e-9 * ((double)t_end.tv_nsec - (double)t_start.tv_nsec);
    curr = (double)single_size / time_interval;
    curr /= times;

    res += curr;
    kernel_fpu_end();
  }

  kernel_fpu_begin();
  printk(KERN_INFO
         "The writing performance of / filesystem is %ld bytes per sec",
         (long)(res));
  kernel_fpu_end();

  pos = 0;
  res = 0;
  printk(KERN_INFO "Start kernel reading test!");
  for (size_t i = 0; i < times; i++) {
    double curr;
    typedef struct timespec64 timespec;
    timespec t_start, t_end;

    preempt_disable();
    ktime_get_ts64(&t_start);
    kernel_read(test_file, data, single_size, &pos);
    ktime_get_ts64(&t_end);
    preempt_enable();

    kernel_fpu_begin();
    double time_interval =
        (double)(t_end.tv_sec - t_start.tv_sec) +
        1e-9 * ((double)t_end.tv_nsec - (double)t_start.tv_nsec);
    curr = (double)single_size / time_interval;
    curr /= times;

    res += curr;
    kernel_fpu_end();
  }

  kernel_fpu_begin();
  printk(KERN_INFO
         "The reading performance of / filesystem is %ld bytes per sec",
         (long)(res));
  kernel_fpu_end();

wait_stop:
  kfree(data);
  filp_close(test_file, NULL);
  while (!kthread_should_stop()) {
    msleep(1000);
  }
  return 0;
}

struct task_struct *th;

static int __init minit(void) {
  th = kthread_run(thread_fn, NULL, "l4t2");
  printk(KERN_INFO "Start Haoming Bai's l4t2 module!");
  return 0;
}

static void __exit mexit(void) {
  kthread_stop(th);
  printk(KERN_INFO "Stop Haoming Bai's l4t2 module!");
  printk(KERN_INFO "");
  return;
}

module_init(minit);
module_exit(mexit);
