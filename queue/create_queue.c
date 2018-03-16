#/* create_queue.c-Creates a queue, traverses and erases the queue.
*/  

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kfifo.h>
#include<linux/slab.h>
#include<linux/moduleparam.h>
#include<linux/random.h>

MODULE_LICENSE("GPL");


static int dstruct_size=1; 

module_param(dstruct_size,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(dstruct_size, "List size");



static int __init create_queue_init(void) {

	struct kfifo my_queue;
	int ret,i,j;
        unsigned int var;
	ret=kfifo_alloc(&my_queue,1024,GFP_KERNEL);
	if(ret)
	   return ret;
        
        //Enqueueing
        for(i=0;i<dstruct_size;i++){
            get_random_bytes(&var,sizeof(var));
            var=var%10000;
            ret=kfifo_in(&my_queue,&var,sizeof(var));
        }
       
        //Traversal
        for(j=0;j<dstruct_size;j++){
            ret=kfifo_out(&my_queue,&var,sizeof(var));
            printk(KERN_INFO "Element is %d\n",var);
        }
         
        //Dequeue
        kfifo_reset(&my_queue);
        
        //Cleanup
        kfifo_free(&my_queue);
        return 0; 
}

static void __exit create_queue_exit(void) {
}

module_init(create_queue_init);
module_exit(create_queue_exit);
