// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/timekeeping.h>
#include <linux/slab.h>

#define DEV_NAME "virtchar7_time"
#define BUF_MAX 128

static dev_t devno;
static struct cdev vc_cdev;
static struct class *vc_class;

struct vc_file_ctx {
    char *buf;
    size_t len;
    loff_t pos;
};

static int vc_open(struct inode *inode, struct file *filp)
{
    struct vc_file_ctx *ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
    if (!ctx)
        return -ENOMEM;

    ctx->buf = kzalloc(BUF_MAX, GFP_KERNEL);
    if (!ctx->buf) {
        kfree(ctx);
        return -ENOMEM;
    }
    ctx->len = 0;
    ctx->pos = 0;
    filp->private_data = ctx;
    return 0;
}

static int vc_release(struct inode *inode, struct file *filp)
{
    struct vc_file_ctx *ctx = filp->private_data;
    if (ctx) {
        kfree(ctx->buf);
        kfree(ctx);
    }
    return 0;
}

static ssize_t vc_read(struct file *filp, char __user *ubuf, size_t count, loff_t *ppos)
{
    struct vc_file_ctx *ctx = filp->private_data;
    struct timespec64 ts;
    struct tm tm;
    int n;

    /* Якщо буфер порожній або ми на початку — сформувати новий час */
    if (ctx->pos == 0 || ctx->pos >= ctx->len) {
        ktime_get_real_ts64(&ts);              /* UTC */
        time64_to_tm(ts.tv_sec, 0, &tm);

        /* Формат: YYYY-MM-DDTHH:MM:SS.NNNNNNNNNZ\n */
        n = snprintf(ctx->buf, BUF_MAX,
                     "%04ld-%02d-%02dT%02d:%02d:%02d.%09ldZ\n",
                     (long)(tm.tm_year + 1900),
                     tm.tm_mon + 1,
                     tm.tm_mday,
                     tm.tm_hour,
                     tm.tm_min,
                     tm.tm_sec,
                     ts.tv_nsec);
        ctx->len = (n > 0) ? (size_t)n : 0;
        ctx->pos = 0;
    }

    /* Якщо користувач просить більше, ніж лишилось — обрізаємо */
    if (count > ctx->len - ctx->pos)
        count = ctx->len - ctx->pos;

    if (count == 0)
        return 0;

    if (copy_to_user(ubuf, ctx->buf + ctx->pos, count))
        return -EFAULT;

    ctx->pos += count;
    *ppos = ctx->pos;
    return count;
}

static const struct file_operations vc_fops = {
    .owner          = THIS_MODULE,
    .open           = vc_open,
    .release        = vc_release,
    .read           = vc_read,
};

static int __init vc_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&devno, 0, 1, DEV_NAME);
    if (ret)
        return ret;

    cdev_init(&vc_cdev, &vc_fops);
    vc_cdev.owner = THIS_MODULE;

    ret = cdev_add(&vc_cdev, devno, 1);
    if (ret)
        goto err_unreg;

    vc_class = class_create(DEV_NAME);
    if (IS_ERR(vc_class)) {
        ret = PTR_ERR(vc_class);
        goto err_cdev;
    }

    if (!device_create(vc_class, NULL, devno, NULL, DEV_NAME)) {
        ret = -ENOMEM;
        goto err_class;
    }

    pr_info(DEV_NAME ": loaded (major=%d minor=%d)\n", MAJOR(devno), MINOR(devno));
    return 0;

err_class:
    class_destroy(vc_class);
err_cdev:
    cdev_del(&vc_cdev);
err_unreg:
    unregister_chrdev_region(devno, 1);
    return ret;
}

static void __exit vc_exit(void)
{
    device_destroy(vc_class, devno);
    class_destroy(vc_class);
    cdev_del(&vc_cdev);
    unregister_chrdev_region(devno, 1);
    pr_info(DEV_NAME ": unloaded\n");
}

module_init(vc_init);
module_exit(vc_exit);

MODULE_AUTHOR("Oleksandra (variant 5.1)");
MODULE_DESCRIPTION("Virtual char device: read() returns current time (ISO-8601 UTC)");
MODULE_LICENSE("GPL");
