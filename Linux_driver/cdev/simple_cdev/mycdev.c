/*
 * File Name: mycdev.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.com
 * Created Time: Wed 29 Mar 2017 07:34:08 PM CST
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#define MYCDEV_TYPE 'k'
#define MYCDEV_CLEAN _IO(MYCDEV_TYPE, 0x30)
#define MYCDEV_GETVALUE _IOR(MYCDEV_TYPE, 0x31)
#define MYCDEV_SETVALUE _IOW(MYCDEV_TYPE, 0x32)

// set device major number
#define MAJOR_NUM 250

// my own char device
struct mycdev {
    int len;
    unsigned char buffer[50];
    struct cdev cdev;
};

// minor device number
static dev_t dev_num = {0};

// global gcd
struct mycdev *gcd;

// device class
struct class *cls;

// param from userspace
// which to determine how many device to register
static int ndevices = 1;
module_param(ndevices, int, 0644);
MODULE_PARM_DESC(ndevices, "The number of devices for register.\n");

// open device
static int mycdev_open(struct inode *inode, struct file *file) {
    struct mycdev *cd;
    printk("mycdev_open success!\n");

    // save pointer of struct mycdev to private_data of sturct file
    cd = container_of(inode->i_cdev, struct mycdev, cdev);
    file->private_data = cd;

    return 0;
}

// read device
static ssize_t mycdev_read(struct file *file, char __user *ubuf, size_t size, loff_t *ppos) {
    int n;
    int ret;
    char *kbuf;
    struct mycdev *mycd = file->private_data;

    printk("read *ppos: %lld\n", *ppos);

    // check ppos
    if(*ppos == mycd->length)
        return 0;

    // if size bigger than buffer_left, then read buffer_left
    if(size > mycd->len - *ppos)
        n = my->len - *ppos;
    else
        n = size;

    printk("read size: n = %d\n", n);
    // get data read position
    kbuf = mycd->buffer + *ppos;

    // copy data to userspace
    ret = copy_to_user(ubuf, kbuf, n);
    if(ret != 0)
        return -EFAULT;

    // update ppos
    *ppos += n;

    printk("mycdev_read success!\n");

    return n;
}

// write device
static ssize_t mycdev_write(struct file *file, const char __user *ubuf, size_t size, loff_t *ppos) {
    int n;
    int ret;
    char *kbuf;
    struct mycdev *mycd = file->private_data;

    printk("write *ppos: %lld\n", *ppos);

    // reach the end of buffer
    if(*ppos == sizeof(mycd->buffer))
        return -1;

    // if size bigger than buffer_left, then write as many as possible
    if(size > sizeof(mycd->buffer) - *ppos)
        n = sizeof(mycd->buffer) - *ppos;
    else
        n = size;

    // get data write position
    kbuf = mycd->buffer + *ppos;

    // copy data from userspace
    ret = copy_from_user(kbuf, ubuf, n);
    if(ret != 0)
        return -EFAULT;

    // update ppos
    *ppos += n;

    // update mycdev.len
    mycd->len += n;

    printk("mycdev_write success!\n");
    return n;
}
