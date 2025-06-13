#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DRIVER_AUTHOR "VinhPhat VPlabcom@gmail.com"
#define DRIVER_DESC   "A simple Linux Led driver"
#define DRIVER_VERSION "1.0"

#define NPAGE 1

struct m_chdev{
    uint32_t size;
    char *kmalloc_ptr;
    dev_t dev_num;
    struct class *m_class;
    struct cdev m_cdev;
}m_dev;

static int     dev_open(struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};

static int dev_open(struct inode *inodep, struct file *filep){
    // pr_info("system call open");
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep){
    // pr_info("system call close");
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
    size_t to_read;
    // pr_info("system call read");

    if (*offset >= m_dev.size)
        return 0;

    to_read = (len > m_dev.size - *offset) ? (m_dev.size - *offset) : len;

    if (copy_to_user(buffer, m_dev.kmalloc_ptr + *offset, to_read) != 0) {
        pr_info("Failed to copy data to user\n");
        return -EFAULT;
    }

    *offset += to_read;
    return to_read;
    return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
    size_t to_write;
    // pr_info("system call write");

    to_write = (len + *offset > NPAGE * PAGE_SIZE) ? (NPAGE * PAGE_SIZE - *offset) : len;

    if (copy_from_user(m_dev.kmalloc_ptr + *offset , buffer, to_write) != 0) {
        pr_info("Failed to copy data from user\n");
        return -EFAULT;
    }

    pr_info("Data from user: %s", m_dev.kmalloc_ptr);

    if (strncmp(m_dev.kmalloc_ptr, "on", 2) == 0) {
        pr_info("turn on led\n");
    } else if (strncmp(m_dev.kmalloc_ptr, "off", 3) == 0) {
        pr_info("turn off led\n");
    }

    *offset += to_write;
    m_dev.size = *offset;

    return to_write;
    return 0;
}


static int __init chdev_init(void)
{
    if(alloc_chrdev_region(&m_dev.dev_num, 0, 1, "dev_num") < 0){
        pr_info("fail to alloc chrdev region");
        return  -1;
    }

    pr_info("DevLinux: hello world kernel module!\n");
    printk(KERN_INFO "LedDriver: major number = %d, minor number = %d\n", MAJOR(m_dev.dev_num), MINOR(m_dev.dev_num));

    if ((m_dev.m_class = class_create(THIS_MODULE, "m_class")) == NULL) {
        unregister_chrdev_region(m_dev.dev_num, 1);
        class_destroy(m_dev.m_class);
        pr_err("Failed to create class\n");
        return PTR_ERR(m_dev.m_class);
    }

    if (device_create(m_dev.m_class, NULL, m_dev.dev_num, NULL, "m_device") == NULL) {
        cdev_del(&m_dev.m_cdev);
        class_destroy(m_dev.m_class);
        unregister_chrdev_region(m_dev.dev_num, 1);
        pr_info("Failed to create device\n");
        return -1;
    }

    cdev_init(&m_dev.m_cdev, &fops);

    if (cdev_add(&m_dev.m_cdev, m_dev.dev_num, 1) < 0) {
        class_destroy(m_dev.m_class);
        unregister_chrdev_region(m_dev.dev_num, 1);
        pr_err("Failed to add cdev\n");
        return -1;
    }

    m_dev.kmalloc_ptr = kmalloc(NPAGE * PAGE_SIZE, GFP_KERNEL);
    if(!m_dev.kmalloc_ptr){
        pr_err("cannot allocate memmory\n");
        device_destroy(m_dev.m_class, m_dev.dev_num);
    }
    return 0;
}

static void __exit chdev_exit(void)
{
    cdev_del(&m_dev.m_cdev);
    device_destroy(m_dev.m_class, m_dev.dev_num);
    class_destroy(m_dev.m_class);
    unregister_chrdev_region(m_dev.dev_num, 1);
    pr_info("DevLinux: Goodbye\n");
}

module_init(chdev_init);
module_exit(chdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
