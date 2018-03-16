/* create_list.c-Creates a list, traverses and erases the memory allocated in one function.
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

//Reading command line argument dstruct_size
module_param(dstruct_size,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(dstruct_size, "List size");

//Struct to hold the node in linked list
struct k_list {
	struct list_head test_list;
	unsigned int temp;
};


static int __init create_list_init(void) 
{

	struct k_list *listarr[dstruct_size],*entry;
	struct list_head test_head;
	int i=0;
	unsigned int var;

	INIT_LIST_HEAD(&test_head);

	//Creating the list
        while(i<dstruct_size) {
       		listarr[i]=kmalloc(sizeof(struct k_list *),GFP_KERNEL);
       		get_random_bytes(&var,sizeof(var));
       	        var=var%10000;	
                listarr[i]->temp=var;
       		list_add(&listarr[i]->test_list,&test_head);      
       		i++;
	}

        //Traversing through the list
	list_for_each_entry(entry,&test_head,test_list){
		printk(KERN_INFO "Element is : %d\n", entry->temp);
	}
        
        //Cleanup
        i=0;
       	while(i<dstruct_size) {
		list_del(&listarr[i]->test_list);
                kfree(listarr[i]);
                i++;
        }
 return 0;        
}

static void __exit create_list_exit(void) {
}

module_init(create_list_init);
module_exit(create_list_exit);
