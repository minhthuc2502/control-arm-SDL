/**
 * @file    ttyarmdriver.c
 * @author  PHAM Minh Thuc
 * @date    7 April 2020
 * @version 0.1
 * @brief 	a simple tty driver allows to replace the bras robotique ALD5 in the period of confinement.  
*/

#include <linux/console.h>
#include <linux/module.h>
#include <linux/tty.h>

MODULE_LICENSE("GPL");              ///< The license type -- this affects runtime behavior
MODULE_AUTHOR("PHAM Minh Thuc");      ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("Simple driver replace arm ALD5");  ///< The description -- see modinfo
MODULE_VERSION("0.1");              ///< The version of the module
static char message[256] = {0};  /// Memory for the string that is passed from userspace
static short size_of_message;    ///< Used to remember the size of the string stored
static const struct tty_port_operations ttyarm_port_ops;
static struct tty_driver *ttyarm_driver;
static struct tty_port ttyarm_port;

static int ttyarm_open(struct tty_struct *tty, struct file *filp)
{
    printk(KERN_INFO "ttyarm: device has been opened\n");
	return tty_port_open(&ttyarm_port, tty, filp);
}

static void ttyarm_close(struct tty_struct *tty, struct file *filp)
{
    printk(KERN_INFO "ttyarm: device has been closed\n");
	tty_port_close(&ttyarm_port, tty, filp);
}

static int ttyarm_write(struct tty_struct *tty, const unsigned char *buf, int count)
{
    sprintf(message, "%s(%i letters",buf,count);
    size_of_message = strlen(message);
    printk(KERN_INFO "ttyarm: Recieved %i letters from the user: %s\n",count,message);
	return count;
}

static int ttyarm_write_room(struct tty_struct *tty)
{
	return 65536;
}

static const struct tty_operations ttyarm_ops = {
	.open = ttyarm_open,
	.close = ttyarm_close,
	.write = ttyarm_write,
	.write_room = ttyarm_write_room,
};

static struct tty_driver *ttyarm_device(struct console *c, int *index)
{
	*index = 0;
	return ttyarm_driver;
}

static struct console ttyarm_console = {
	.name = "ttyarm",
	.device = ttyarm_device,
};

static int __init ttyarm_init(void)
{
	printk(KERN_INFO "ttyarm: Inittialize driver ttyarm sucessfully\n");
	struct tty_driver *driver;
	int ret;

	driver = tty_alloc_driver(1,
		TTY_DRIVER_RESET_TERMIOS |
		TTY_DRIVER_REAL_RAW |
		TTY_DRIVER_UNNUMBERED_NODE);
	if (IS_ERR(driver))
		return PTR_ERR(driver);

	tty_port_init(&ttyarm_port);
	ttyarm_port.ops = &ttyarm_port_ops;

	driver->driver_name = "ttyarm0";
	driver->name = "ttyarm0";
	driver->type = TTY_DRIVER_TYPE_CONSOLE;
	driver->init_termios = tty_std_termios;
	driver->init_termios.c_oflag = OPOST | OCRNL | ONOCR | ONLRET;
	tty_set_operations(driver, &ttyarm_ops);
	tty_port_link_device(&ttyarm_port, driver, 0);

	ret = tty_register_driver(driver);
	if (ret < 0) {
		put_tty_driver(driver);
		tty_port_destroy(&ttyarm_port);
		return ret;
	}

	ttyarm_driver = driver;
	register_console(&ttyarm_console);

	return 0;
}

static void __exit ttyarm_exit(void)
{
	printk(KERN_INFO "ttyarm: Exit driver ttyarm sucessfully\n");
	unregister_console(&ttyarm_console);
	tty_unregister_driver(ttyarm_driver);
	put_tty_driver(ttyarm_driver);
	tty_port_destroy(&ttyarm_port);
}

module_init(ttyarm_init);
module_exit(ttyarm_exit);
