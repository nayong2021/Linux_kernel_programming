/*
 * list.c - Linux kernel list API
 *
 * TODO 1/0: Fill in name / email
 * Author: YongSung Na <nayong2017@ajou.ac.kr>
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

#define PROCFS_MAX_SIZE		1024

#define procfs_dir_name		"list"
#define procfs_file_read	"preview"
#define procfs_file_write	"management"

struct proc_dir_entry *proc_list;
struct proc_dir_entry *proc_list_read;
struct proc_dir_entry *proc_list_write;

/* TODO 2/0: define your list! */

struct str_node{
	struct list_head list;
	char* str;
};

LIST_HEAD(head);

static int list_proc_show(struct seq_file *m, void *v)
{
	/* TODO 3/0: print your list. One element / line. */
	
	struct str_node* pos;

	list_for_each_entry(pos, &head, list)
		seq_puts(m, pos->str);

	return 0;
}

static struct str_node* str_node_alloc(char *str)
{
	struct str_node* temp;
	temp = kmalloc(sizeof(struct str_node), GFP_KERNEL);
	if(temp == NULL)
		return NULL;

	temp->str = kmalloc(strlen(str) + 1, GFP_KERNEL);
	if(temp->str == NULL)
		return NULL;

	strcpy(temp->str, str);

	return temp;
}

static void str_node_addf(char *str)
{
	struct str_node* temp;
	temp = str_node_alloc(str);
	if(temp == NULL)
		return;
	list_add(&temp->list, &head);
}

static void str_node_adde(char *str)
{
	struct str_node* temp;
	temp = str_node_alloc(str);
	if(temp == NULL)
		return;
	list_add_tail(&temp->list, &head);
}

static void str_node_delf(char *str)
{
	struct list_head *pos, *next;
	struct str_node *temp;

	list_for_each_safe(pos, next, &head) {
		temp = list_entry(pos, struct str_node, list);
		if (strcmp(temp->str, str) == 0) {
			list_del(pos);
			kfree(temp);
			return;
		}
	}
}

static void str_node_dela(char *str)
{
	struct list_head *pos, *next;
	struct str_node *temp;

	list_for_each_safe(pos, next, &head) {
		temp = list_entry(pos, struct str_node, list);
		if (strcmp(temp->str, str) == 0) {
			list_del(pos);
			kfree(temp);
		}
	}
}


static int list_read_open(struct inode *inode, struct  file *file)
{
	return single_open(file, list_proc_show, NULL);
}

static int list_write_open(struct inode *inode, struct  file *file)
{
	return single_open(file, list_proc_show, NULL);
}

static ssize_t list_write(struct file *file, const char __user *buffer,
			  size_t count, loff_t *offs)
{
	char local_buffer[PROCFS_MAX_SIZE];
	unsigned long local_buffer_size = 0;

	local_buffer_size = count;
	if (local_buffer_size > PROCFS_MAX_SIZE)
		local_buffer_size = PROCFS_MAX_SIZE;

	memset(local_buffer, 0, PROCFS_MAX_SIZE);
	if (copy_from_user(local_buffer, buffer, local_buffer_size))
		return -EFAULT;

	/* local_buffer contains your command written in /proc/list/management
	 * TODO 4/0: parse the command and add/delete elements.
	 */
	if(strncmp(local_buffer, "addf", 4) == 0)
		str_node_addf(local_buffer + 5);
	else if(strncmp(local_buffer, "adde", 4) == 0)
		str_node_adde(local_buffer + 5);
	else if(strncmp(local_buffer, "delf", 4) == 0)
		str_node_delf(local_buffer + 5);
	else if(strncmp(local_buffer, "dela", 4) == 0)
		str_node_dela(local_buffer + 5);

	return local_buffer_size;
}

static const struct proc_ops r_pos = {
	//.owner		= THIS_MODULE,
	.proc_open		= list_read_open,
	.proc_read		= seq_read,
	.proc_release		= single_release,
};

static const struct proc_ops w_pos = {
	//.owner		= THIS_MODULE,
	.proc_open		= list_write_open,
	.proc_write		= list_write,
	.proc_release		= single_release,
};

static int list_init(void)
{
	proc_list = proc_mkdir(procfs_dir_name, NULL);
	if (!proc_list)
		return -ENOMEM;

	proc_list_read = proc_create(procfs_file_read, 0000, proc_list,
				     &r_pos);
	if (!proc_list_read)
		goto proc_list_cleanup;

	proc_list_write = proc_create(procfs_file_write, 0000, proc_list,
				      &w_pos);
	if (!proc_list_write)
		goto proc_list_read_cleanup;

	return 0;

proc_list_read_cleanup:
	proc_remove(proc_list_read);
proc_list_cleanup:
	proc_remove(proc_list);
	return -ENOMEM;
}

static void list_exit(void)
{
	proc_remove(proc_list);
}

module_init(list_init);
module_exit(list_exit);

MODULE_DESCRIPTION("Linux kernel list API");
/* TODO 5/0: Fill in your name / email address */
MODULE_AUTHOR("YongSung Na <nayong2017@ajou.ac.kr>");
MODULE_LICENSE("GPL v2");
