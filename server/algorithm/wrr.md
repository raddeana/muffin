#### Linux内核IPVS使用的WRR算法
```c
static struct ip_vs_scheduler ip_vs_wrr_scheduler = {
    .name =         "wrr",
    .refcnt =       ATOMIC_INIT(0),
    .module =       THIS_MODULE,
    .n_list =       LIST_HEAD_INIT(ip_vs_wrr_scheduler.n_list),
    .init_service =     ip_vs_wrr_init_svc,
    .done_service =     ip_vs_wrr_done_svc,
    .add_dest =     ip_vs_wrr_dest_changed,
    .del_dest =     ip_vs_wrr_dest_changed,
    .upd_dest =     ip_vs_wrr_dest_changed,
    .schedule =     ip_vs_wrr_schedule,
};
```

```c
// Supposing that there is a server set S = {S0, S1, …, Sn-1};
// W(Si) indicates the weight of Si;
// i indicates the server selected last time, and i is initialized with -1;
// cw is the current weight in scheduling, and cw is initialized with zero; 
// max(S) is the maximum weight of all the servers in S;
// gcd(S) is the greatest common divisor of all server weights in S;

while (true) {
    i = (i + 1) mod n;
    
    if (i == 0) {
        cw = cw - gcd(S); 
        if (cw <= 0) {
            cw = max(S);
            if (cw == 0)
            return NULL;
        }
    } 
    
    if (W(Si) >= cw) 
        return Si;
}
```

```c
#include <stdio.h>
#include <stdlib.h>

struct entry {
        int weight;
};

struct entry *g_entry = NULL;
int max_weight = 0;
int curr_weight = 0;
int divisor = 0;
int iter = -1;


int gcd(int a, int b) {  
        if (a == 0) {
                return b;
        }
        return gcd(b%a, a);  
} 

struct entry *next(int size) {

        struct entry *ent;
        while (1) {
                iter = (iter + 1) % size;
                if (iter == 0) {
                        curr_weight = curr_weight - divisor; 
                        if (curr_weight <= 0) {
                                curr_weight = max_weight;
                        }
                } 
                ent = &g_entry[iter];
                if (ent->weight >= curr_weight) {
                        return ent;
                }
        }
}

int main (int argc, char **argv) {
        int size = atoi(argv[1]);
        int i = 0;
        int total = 0;

        g_entry = (struct entry *)calloc(size, sizeof(struct entry));
        for (i = 0; i < size; i++) {
                struct entry *ent = &g_entry[i];
                ent->weight = atoi(argv[i+2]);
                total += ent->weight;
                if (ent->weight > max_weight) {
                        max_weight = ent->weight;
                }
                divisor = gcd(divisor, ent->weight);
        }

        for (i = 0; i < total; i++) {
                struct entry *ent = next(size);
                printf("[LAST]: %d\n", ent->weight);
        }

}
```

#### Nginx使用的WRR算法
```c
#include <stdio.h>
#include <stdlib.h>

struct entry {
  int weight;
  int curr_weight;
};

struct entry *curr_entry = NULL;
struct entry *g_entry = NULL;

struct entry *next (struct entry *entrys, int size) {
  struct entry *ent;
  
  int i = 0, 
      total = 0;
  
  for (i = 0; i < size; i++) {
    ent = &entrys[i];
    ent->curr_weight += ent->weight;
    total += ent->weight;
    if (curr_entry == NULL || ent->curr_weight > curr_entry->curr_weight) {
      curr_entry = ent;
    }
  }

  curr_entry->curr_weight -= total;

  for (i = 0; i < size; i++) {
          ent = &entrys[i];
  }

  return curr_entry;
}

int main (int argc, char **argv) {
        int size = atoi(argv[1]);
        int i = 0;
        int total = 0;

        g_entry = (struct entry *)calloc(size, sizeof(struct entry));
        for (i = 0; i < size; i++) {
                struct entry *ent = &g_entry[i];
                ent->weight = atoi(argv[i+2]);
                total += ent->weight;
        }


        for (i = 0; i < total; i++) {
                struct entry *ent = next(g_entry, size);
                printf("[LAST]: %d\n", ent->weight);
        }

}
```

#### CFS/FQ/PQ调度与WRR负载均衡
```c
#include <stdio.h>
#include <stdlib.h>

struct entry {
  int weight;
  int curr_cfs;
};

struct entry *curr_entry = NULL;
struct entry *g_entry = NULL;


struct entry *next_cfs (struct entry *entrys, int size) {
  struct entry *ent;
  int i = 0, total = 0;
  for (i = 0; i < size; i++) {
    ent = &entrys[i];

    // 选择最小的curr_cfs
    if (curr_entry == NULL || ent->curr_cfs < curr_entry->curr_cfs) {
      curr_entry = ent;
    }
  }
  
  // 满足“单位1”中有weight个元素，算法的结果才是正确的
  curr_entry->curr_cfs += 100000000/(curr_entry->weight);
  return curr_entry;
}


int main (int argc, char **argv) {
  int size = atoi(argv[1]);
  int i = 0;
  int total = 0;

  g_entry = (struct entry *)calloc(size, sizeof(struct entry));
  
  for (i = 0; i < size; i++) {
    struct entry *ent = &g_entry[i];
    ent->weight = atoi(argv[i+2]);
    ent->curr_cfs = 100000000/ent->weight;
    total += ent->weight;
  }


  for (i = 0; i < total; i++) {
    struct entry *ent = next_cfs(g_entry, size);
    printf("[LAST_CFS]: %d\n", ent->weight);
  }
}
```
