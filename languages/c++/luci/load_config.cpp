#include <unistd.h>  
#include <stdio.h>  
#include <string.h>  
#include <uci.h>  
  
  
static struct uci_context * ctx = NULL; //定义一个UCI上下文的静态变量
/********************************************* 
 *   载入配置文件,并遍历Section. 
 */
bool load_config()  
{  
    struct uci_package * pkg = NULL;  
    struct uci_element *e;  
  
  
    ctx = uci_alloc_context(); // 申请一个UCI上下文.  
    if (UCI_OK != uci_load(ctx, UCI_CONFIG_FILE, &pkg))  
        goto cleanup; //如果打开UCI文件失败,则跳到末尾 清理 UCI 上下文.  
  
  
    /* 遍历UCI的每一个节 */  
    uci_foreach_element(&pkg->sections, e)  
    {  
        struct uci_section *s = uci_to_section(e);  
        // 将一个 element 转换为 section类型, 如果节点有名字,则 s->anonymous 为 false.  
        // 此时通过 s->e->name 来获取.  
        // 此时 您可以通过 uci_lookup_option()来获取 当前节下的一个值.  
        if (NULL != (value = uci_lookup_option_string(ctx, s, "ipaddr")))  
        {  
            ip = strdup(value) //如果您想持有该变量值，一定要拷贝一份。当 pkg销毁后value的内存会被释放。  
        }  
        // 如果您不确定是 string类型 可以先使用 uci_lookup_option() 函数得到Option 然后再判断.  
        // Option 的类型有 UCI_TYPE_STRING 和 UCI_TYPE_LIST 两种.  
  
  
    }  
    uci_unload(ctx, pkg); // 释放 pkg   
cleanup:  
    uci_free_context(ctx);  
    ctx = NULL;  
}
