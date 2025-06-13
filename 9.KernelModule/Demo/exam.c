#include <linux/module.h>


static int __init chdev_init(void)
{
    pr_info("DevLinux: hello world kernel module!\n");
    return 0;
}

static void __exit chdev_exit(void)
{
    pr_info("DevLinux: Goodbye\n");
}

module_init(chdev_init);
module_exit(chdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DevLinux");
MODULE_DESCRIPTION("Interger GPIO Driver for Raspberry Pi Zero W (BCM2708)");
