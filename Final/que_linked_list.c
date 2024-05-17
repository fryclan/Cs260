#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_validation.h"
#include "que_linked_list.h"


//Looks at value stored in the first node of the queue
void * peek_first_node(struct que *que_num)
{
    // printf("First nodes Value: %d\n", que_num.first_node->num);
    return que_num->first_node->data;
}

//Looks at value stored in the Last node of the queue
void * peek_last_node(struct que *que_num)
{
    // printf("Last nodes Value: %d\n", que_num.last_node->num);
    return que_num->last_node->data;
}

void * search_for_node(struct linked_list_node *node, void * data_to_be_found,int (*compare_function)(void *data_ptr, void *data_to_be_compared))
{
    if (node == NULL)
    {
        printf("nothing in here mate.\n");
        return NULL;
    }
    else if (compare_function(node->data, data_to_be_found) == 1)
    {
        return node->data;
    }
    else
    {
        return search_for_node(node->ptr_next, data_to_be_found, compare_function);
    }
}

//adds node to back of queue
struct que * add_to_que(struct que *que_num, void *data_to_be_stored)
{
    
    struct linked_list_node *node = {0};
    node = malloc(sizeof(struct linked_list_node));
    if (que_num == NULL)
    {
        que_num = malloc(sizeof(struct que));
        que_num->first_node = NULL;
        que_num->last_node = NULL;
        que_num->length = 0;
    }
    
    node->data = data_to_be_stored;
    node->ptr_prev = que_num->last_node;
    node->ptr_next = NULL;
    if (que_num->length == 0)
    {
        que_num->first_node = node;
    }
    else
    {
        que_num->last_node->ptr_next = node;
    }

    que_num->last_node = node;
    que_num->length = (que_num->length+1);

    
    return que_num;
}

//returns the value that is stored in the first node of the queue and removes that node from queue
void * pop_first_node(struct que *que_num)
{
    if (que_num->first_node == NULL)
    {
        printf("no data in que\n");
        return 0;
    }
    else
    {
        struct linked_list_node *temp_node = que_num->first_node;
        void * temp_node_value = que_num->last_node->data;
        temp_node_value = que_num->first_node->data;
        que_num->first_node = que_num->first_node->ptr_next;
        if (que_num->first_node != NULL)
        {
            que_num->first_node->ptr_prev = NULL;
        }
        que_num->length = (que_num->length-1);
        free(temp_node);
        
        return temp_node_value;
    }
    
}

//returns the value that is stored in the last node of the queue and removes that node from queue
void * pop_last_node(struct que *que_num)
{
    if (que_num == NULL)
    {
        // printf("no data in que\n");
        return 0;   
    }
    
    if (que_num->last_node == NULL)
    {
        // printf("no data in que\n");
        return 0;
    }
    else
    {
        struct linked_list_node *temp_node = que_num->last_node;
        void *temp_node_value = que_num->last_node->data;
        que_num->last_node = que_num->last_node->ptr_prev;
        if (que_num->last_node != NULL)
        {
            que_num->last_node->ptr_next = NULL;
        }
        que_num->length = (que_num->length-1);
        free(temp_node);
        return temp_node_value;
    }
    
}
