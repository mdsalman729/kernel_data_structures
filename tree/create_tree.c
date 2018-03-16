/* create_tree.c-Creates a tree, insert,traverse and delete
*/  

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/rbtree.h>
#include<linux/slab.h>
#include<linux/moduleparam.h>
#include<linux/random.h>

MODULE_LICENSE("GPL");

static int dstruct_size;

module_param(dstruct_size,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(dstruct_size, "List size");

struct tree_entry {
      struct rb_node rbnode;
      int data;
};


static int rb_insert(struct rb_root *root,struct tree_entry *entry,struct tree_entry **dupentry)
{

        struct rb_node **link=&root->rb_node,*parent=NULL;
        struct tree_entry *myentry;
        while (*link) {
              parent=*link;
              myentry=rb_entry(parent,struct tree_entry,rbnode);
              if (myentry->data > entry->data)
                 link=&(*link)->rb_left;
              else if (myentry->data < entry->data )
                 link=&(*link)->rb_right;
              else {
                 *dupentry=myentry;
                 return -EEXIST;
              }
        }
        rb_link_node(&entry->rbnode,parent,link);
        rb_insert_color(&entry->rbnode,root);
        return 0;
}

static struct tree_entry * rb_search(struct rb_root *root,int key) 
{
    struct rb_node *node=root->rb_node;
    struct tree_entry *entry;
    while (node) {
           entry=rb_entry(node,struct tree_entry,rbnode);
           if (entry->data > key) 
               node=node->rb_left;
           else if (entry->data < key)
               node=node->rb_right;
           else
               return entry;
    }
    return NULL;
}
      
         

static int __init create_tree_init(void) 
{

	struct rb_root my_tree_root=RB_ROOT;
        struct tree_entry* my_tree[dstruct_size];
        struct tree_entry **dupentry;
        int random_nums[dstruct_size];
        int i=0;
        unsigned int var;
	
        //Insert
        while(i<dstruct_size) {
       		my_tree[i]=kmalloc(sizeof(struct tree_entry *),GFP_KERNEL);
       		get_random_bytes(&var,sizeof(var));
       	        var=var%10000;
                random_nums[i]=var;	
                my_tree[i]->data=var;
       		rb_insert(&my_tree_root,my_tree[i],dupentry);      
       		i++;
	}
        
        //Traverse
        for (i=0;i<dstruct_size;i++) {
            struct tree_entry *val;
            val=rb_search(&my_tree_root,random_nums[i]);
            if (val) {
                printk(KERN_INFO "Element is %d\n",val->data);
                rb_erase(&val->rbnode,&my_tree_root);
            }
            else
                printk(KERN_INFO "Element not found\n");
        }

        //Delete
        for(i=0;i<dstruct_size;i++)
               kfree(my_tree[i]);
       

        return 0;        
}

static void __exit create_tree_exit(void) {}

module_init(create_tree_init);
module_exit(create_tree_exit);
