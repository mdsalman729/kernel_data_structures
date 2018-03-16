/* create_list_separate.c-Creates a list, traverses and erases the memory allocated in separate functions.
*/  



#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>
#include<linux/moduleparam.h>
#include<linux/random.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mohammed Salman");

static int dstruct_size;

module_param(dstruct_size,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(dstruct_size, "List size");


//Struct to hold each node of the list
struct k_list {
	struct list_head test_list;
	unsigned int temp;
};

//Function to create the list.Assumption is the that the entire list is created in one call. 
static int create_list(struct k_list* node[], struct list_head* test_head)
{
           int i;
           unsigned int var;
           if(test_head==NULL || node==NULL )
              return -1;
           else {
               for (i=0;i<dstruct_size;i++) {
                    node[i]=kmalloc(sizeof(struct k_list *),GFP_KERNEL);
                    get_random_bytes(&var,sizeof(var));
                    var=var%10000;
                    node[i]->temp=var;
                    list_add(&node[i]->test_list,test_head);
               }
           }
           return 0;
}

// Function to traverse through the list 
static int traverse(struct list_head *test_head)
{
       struct k_list *entry;
       if(test_head==NULL)
           return -1;
       else {
          list_for_each_entry(entry,test_head,test_list){
               printk(KERN_INFO "Element is %d\n",entry->temp);
          }
      }
       return 0; 
}


//Function to cleanup the memory allocated
static int list_erase(struct k_list* listarr[]) 
{
     int i;
     for(i=0;i<dstruct_size;i++) {
          list_del(&listarr[i]->test_list);
          kfree(listarr[i]);
     }
     return 0;

}                

//Function which is called when the module in instantiated
static int __init create_list_separate_init(void) {

	struct k_list *listarr[dstruct_size];
	struct list_head test_head;

	INIT_LIST_HEAD(&test_head);

        create_list(listarr,&test_head);

        traverse(&test_head);
        
        list_erase(listarr);

 return 0;        
}

static void __exit create_list_separate_exit(void) {
}

module_init(create_list_separate_init);
module_exit(create_list_separate_exit);
