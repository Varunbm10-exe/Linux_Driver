#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4 GNU/Linux");
MODULE_DESCRIPTION("A simple GPIO driver for setting an LED and reading a button");

static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "my_gpio_driver"
#define DRIVER_CLASS "MyModuleClass"

static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
    int to_copy, not_copied, delta;
    char tmp[3] = " \n";

    to_copy = min(count, sizeof(tmp));
    printk("Value of button: %d\n", gpio_get_value(529));
    tmp[0] = gpio_get_value(529) + '0';

    not_copied = copy_to_user(user_buffer, &tmp, to_copy);
    delta = to_copy - not_copied;
    return delta;
}

static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
    int to_copy, not_copied, delta;
    char value;

    to_copy = min(count, sizeof(value));
    not_copied = copy_from_user(&value, user_buffer, to_copy);

    switch(value) {
        case '0':
            gpio_set_value(516, 0);
            break;
        case '1':
            gpio_set_value(516, 1);
            break;
        default:
            printk("Invalid Input!\n");
            break;
    }

    delta = to_copy - not_copied;
    return delta;
}

static int driver_open(struct inode *device_file, struct file *instance) {
    printk("dev_nr - open was called!\n");
    return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
    printk("dev_nr - close was called!\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .read = driver_read,
    .write = driver_write
};

static int __init ModuleInit(void) {
    printk("Hello, Kernel!\n");

    if (alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
        printk("Device Nr. could not be allocated!\n");
        return -1;
    }
    printk("read_write - Device Nr. Major: %d, Minor: %d was registered!\n", MAJOR(my_device_nr), MINOR(my_device_nr));

    if ((my_class = class_create(DRIVER_CLASS)) == NULL) {
        printk("Device class cannot be created!\n");
        goto ClassError;
    }

    if (device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
        printk("Cannot create device file!\n");
        goto DeviceFileError;
    }

    cdev_init(&my_device, &fops);

    if (cdev_add(&my_device, my_device_nr, 1) == -1) {
        printk("Registering device to kernel failed!\n");
        goto AddError;
    }

    if (gpio_request(516, "rpi-gpio-4")) {
        printk("Cannot allocate GPIO 4\n");
        goto AddError;
    }

    if (gpio_direction_output(516, 0)) {
        printk("Cannot set GPIO 4 to output!\n");
        goto Gpio4Error;
    }

    if (gpio_request(529, "rpi-gpio-17")) {
        printk("Cannot allocate GPIO 17\n");
        goto Gpio4Error;
    }

    if (gpio_direction_input(529)) {
        printk("Cannot set GPIO 17 to input!\n");
        goto Gpio17Error;
    }

    return 0;

Gpio17Error:
    gpio_free(529);
Gpio4Error:
    gpio_free(516);
AddError:
    device_destroy(my_class, my_device_nr);
DeviceFileError:
    class_destroy(my_class);
ClassError:
    unregister_chrdev_region(my_device_nr, 1);
    return -1;
}

static void __exit ModuleExit(void) {
    gpio_set_value(516, 0);
    gpio_free(529);
    gpio_free(516);
    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev_region(my_device_nr, 1);
    printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

