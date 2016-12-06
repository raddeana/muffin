#include <linux/sched.h>  
#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/init.h>  
#include <linux/fs.h>  
#include <linux/file.h>  

MODULE_AUTHOR("xunil@BMY");  
MODULE_DESCRIPTION("By utilizing the VFS filesystem, this module can capturesystem calls.");  
MODULE_LICENSE("GPL");

char *root_fs = "/";
typedef int (*readdir_t)(struct file *, void *, filldir_t); 

readdir_t orig_root_readdir = NULL;  

int myreaddir(struct file *fp, void *buf, filldir_t filldir)  
{  
        int r;  
        printk("<1>You got me partner!/n");  
        r=orig_root_readdir(fp,buf,filldir);  
        return r;  
}

int patch_vfs(const char *p, readdir_t *orig_readdir, readdir_t new_readdir)  
{  
        struct file *filep;  
        filep = filp_open(p,O_RDONLY,0);  
        
        if(IS_ERR(filep)) {
            return -1; 
        } 
        
        if(orig_readdir) {
            *orig_readdir = filep->f_op->readdir;  
        }

        filep->f_op->readdir=new_readdir;  
        filp_close(filep, 0);  
        
        return 0;  
}

int unpatch_vfs(const char *p, readdir_t orig_readdir) 
{  
        struct file *filep;  
        filep=filp_open(p,O_RDONLY,0);  
        if(IS_ERR(filep))  
                return -1;  
        filep->f_op->readdir=orig_readdir;  
        filp_close(filep,0);  
        return 0;  
}

static int patch_init(void)  
{  
        patch_vfs(root_fs, &orig_root_readdir, myreaddir);  
        printk("<1>VFS is patched!/n");  
        return 0;  
}

static void patch_cleanup(void) 
{  
    unpatch_vfs(root_fs, orig_root_readdir);  
    printk("<1>VFS is unpatched!/n");  
}  

module_init(patch_init);  
module_exit(patch_cleanup);  