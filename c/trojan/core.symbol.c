#include <linux/kernel.h>  
#include <linux/module.h>  
#include <linux/init.h>  
#include <linux/sched.h>  
#include <asm/unistd.h>  
MODULE_LICENSE("GPL");  
MODULE_AUTHOR("xunil@bmy");  
MODULE_DESCRIPTION("Different from others, this module automatically locate the entry of  
sys_call_table !");  
unsigned long *sys_call_table=NULL;  
asmlinkage int (*orig_mkdir)(const char *,int);  
struct _idt  
{  
unsigned short offset_low,segment_sel;  
unsigned char reserved,flags;  
unsigned short offset_high;  
};  
unsigned long *getscTable(){  
        unsigned char idtr[6],*shell,*sort;  
        struct _idt *idt;  
        unsigned long system_call,sct;  
        unsigned short offset_low,offset_high;  
        char *p;  
        int i;  
  
  
        __asm__("sidt %0" : "=m" (idtr));  
  
        idt=(struct _idt*)(*(unsigned long*)&idtr[2]+8*0x80);  
        offset_low = idt->offset_low;  
        offset_high = idt->offset_high;  
        system_call=(offset_high<<16)|offset_low;  
  
        shell=(char *)system_call;  
        sort="/xff/x14/x85";  
  
        for(i=0;i<(100-2);i++)  
                if(shell[i]==sort[0]&&shell[i+1]==sort[1]&&shell[i+2]==sort[2])  
                        break;  
        p=&shell[i];  
        p+=3;  
        sct=*(unsigned long*)p;  
        return (unsigned long*)(sct);  
}  
asmlinkage int hacked_mkdir(const char * pathname, int mode){  
        printk("PID %d called sys_mkdir !/n",current->pid);  
        return orig_mkdir(pathname,mode);  
}  
static int __init find_init(void){  
        sys_call_table = getscTable();  
        orig_mkdir=(int(*)(const char*,int))sys_call_table[__NR_mkdir];  
        sys_call_table[__NR_mkdir]=(unsigned long)hacked_mkdir;  
        return 0;  
}  
static void __exit find_cleanup(void){  
        sys_call_table[__NR_mkdir]=(unsigned long)orig_mkdir;  
}  

module_init(find_init);  
module_exit(find_cleanup);  