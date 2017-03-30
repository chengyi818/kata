/*
 * File Name: mycdev.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.com
 * Created Time: Wed 29 Mar 2017 07:34:08 PM CST
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/ioctl.h>

#define MYCDEV_TYPE 'k'
#define MYCDEV_CLEAN _IO(MYCDEV_TYPE, 0x30)
#define MYCDEV_GETVALUE _IOR(MYCDEV_TYPE, 0x31, int)
#define MYCDEV_SETVALUE _IOW(MYCDEV_TYPE, 0x32, int)

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
    if(*ppos == mycd->len)
        return 0;

    // if size bigger than buffer_left, then read buffer_left
    if(size > mycd->len - *ppos)
        n = mycd->len - *ppos;
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

long mycdev_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    int ret = 0;
    struct mycdev *mycd = file->private_data;

    switch (cmd) {
    case MYCDEV_CLEAN:
        printk("CMD: CLEAN\n");
        memset(mycd->buffer, 0, sizeof(mycd->buffer));
        break;
    case MYCDEV_SETVALUE:
        printk("CMD: SETVALUE\n");
        mycd->len = arg;
        break;
    case MYCDEV_GETVALUE:
        printk("CMD: GETVALUE\n");
        ret = put_user(mycd->len, (int *)arg);
        break;
    default:
        return -EFAULT;
    }

    return ret;
}

// device operation function interface
static const struct file_operations mycdev_operations = {
    .owner = THIS_MODULE,
    .open = mycdev_open,
    .read = mycdev_read,
    .write = mycdev_write,
    .unlocked_ioctl = mycdev_unlocked_ioctl,
};

// module init
int __init mycdev_init(void) {
    int i = 0;
    int n = 0;
    int ret;
    struct device *device;

    gcd = kzalloc(ndevices * sizeof(struct mycdev), GFP_KERNEL);
    if(!gcd) {
        return -ENOMEM;
    }

    // device num: MAJOR(12bit) | MINOR(20bit)
    dev_num = MKDEV(MAJOR_NUM, 0);

    // register static device
    ret = register_chrdev_region(dev_num, ndevices, "mycdev");
    if(ret < 0) {
        // register static device fail, register dynamic device
        ret = alloc_chrdev_region(&dev_num, 0, ndevices, "mycdev");
        if(ret < 0) {
            printk("Fail to register_chrdev_region\n");
            goto err_register_chrdev_region;
        }
    }

    // create device class
    cls = class_create(THIS_MODULE, "mycdev");
    if(IS_ERR(cls)) {
        ret = PTR_ERR(cls);
        goto err_class_create;
    }
    printk("ndevices: %d\n", ndevices);

    for(n = 0; n < ndevices; n++) {
        // init char device
        cdev_init(&gcd[n].cdev, &mycdev_operations);

        // add device to OS
        ret = cdev_add(&gcd[n].cdev, dev_num+n, 1);
        if(ret < 0) {
            goto err_cdev_add;
        }

        // output device info to userspace(/sys/class/$(class_name)/$(device_name))
        device = device_create(cls, NULL, dev_num+n, NULL, "mycdev%d", n);
        if(IS_ERR(device)) {
            ret = PTR_ERR(device);
            printk("Fail to device_create\n");
            goto err_device_create;
        }
    }

printk("Register dev_fito to system, ok!\n");
    return 0;

err_device_create:
    // remove outputed device info
    for(i = 0; i < n; i++) {
        device_destroy(cls, dev_num+i);
    }

err_cdev_add:
    // remove cdev added
    for (i = 0; i < n; ++i) {
        cdev_del(&gcd[i].cdev);
    }

err_class_create:
    unregister_chrdev_region(dev_num, ndevices);

err_register_chrdev_region:
    return ret;
}

void __exit mycdev_exit(void) {
    int i;

    // destroy device info in sysfs
    for (i = 0; i < ndevices; ++i) {
        device_destroy(cls, dev_num+i);
    }

    // destroy device class
    class_destroy(cls);

    // delete char device from OS
    for (i = 0; i < ndevices; ++i) {
        cdev_del(&gcd[i].cdev);
    }

    // free alloced device num
    unregister_chrdev_region(dev_num, ndevices);

    kfree(gcd);
    printk("remove mycdev from system, ok!\n");
    return;
}

module_init(mycdev_init);
module_exit(mycdev_exit);
MODULE_LICENSE("GPL");
