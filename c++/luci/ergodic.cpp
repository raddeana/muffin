// s 为 section.
struct uci_option * o = uci_lookup_option(ctx, s, "index");
if ((NULL != o) && (UCI_TYPE_LIST == o->type)) //o存在 且 类型是 UCI_TYPE_LIST则可以继续.
{
    struct uci_element *e;

    uci_foreach_element(&o->v.list, e)
    {
        // 这里会循环遍历 list  
        // e->name 的值依次是 index.html, index.php, default.html  
    }
}
