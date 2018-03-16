/* create_map.c-Creates a map, insert,traverse and delete
*/  

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/idr.h>
#include<linux/slab.h>
#include<linux/moduleparam.h>
#include<linux/random.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mohammed Salman");

static int dstruct_size=1; 

module_param(dstruct_size,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(dstruct_size, "List size");



static int __init create_map_init(void) {

	struct idr my_map;
	int id,i,j;
        unsigned int var, *check;
        int nums[dstruct_size],random_values[dstruct_size];
	idr_init(&my_map);
        
        for(i=0;i<dstruct_size;i++){
            get_random_bytes(&var,sizeof(var));
            var=var%10000;
            random_values[i]=var;
        }   

        //Inserting elements into map
        for(i=0;i<dstruct_size;i++){
            idr_preload(GFP_KERNEL);
            id=idr_alloc(&my_map, &(random_values[i]),10,550,GFP_KERNEL);
            idr_preload_end();

            if(id==-ENOSPC)
                printk(KERN_INFO "No id available in the requested range\n");
            else if(id==-ENOMEM)
                printk(KERN_INFO "No memory available\n");
            else 
                nums[i]=id;   
        }

        //Traversal
        for(j=0;j<dstruct_size;j++){
           check=idr_find(&my_map,nums[j]);
           if(!check)
                printk(KERN_INFO "Element not found\n");
           else { 
                printk(KERN_INFO "ID is %d and element is %d\n",nums[j],*check);
                idr_remove(&my_map,nums[j]);
           }
        }
        
        //Cleanup
        idr_destroy(&my_map);
        return 0; 
}

static void __exit create_map_exit(void) {
}

module_init(create_map_init);
module_exit(create_map_exit);
