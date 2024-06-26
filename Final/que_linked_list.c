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
        // printf("nothing in here mate.\n");
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

// void * search_for_node_to_delete(struct linked_list_node *node, void * data_to_be_found,int (*compare_function)(void *data_ptr, void *data_to_be_compared))
// {
//     if (node == NULL)
//     {
//         printf("nothing in here mate.\n");
//         return NULL;
//     }
//     else if (compare_function(node->data, data_to_be_found) == 1)
//     {
//         struct linked_list_node *temp_node1 = node->ptr_prev;
//         struct linked_list_node *temp_node2 = node->ptr_next;
//         if (node->ptr_next==NULL&&node->ptr_prev==NULL)
//         {
//             temp_node1 = node;
//             node = NULL;
//             return temp_node1->data;
//         }
        
//         else if (node->ptr_next==NULL)
//         {
//             temp_node1->ptr_next = node->ptr_next;
//             return node->data;
//         }
//         else if(node->ptr_prev==NULL)
//         {
//             temp_node2->ptr_prev = node->ptr_prev;
//             return node->data;
//         }
        
//         temp_node2->ptr_prev = node->ptr_prev;
//         temp_node1->ptr_next = node->ptr_next;
//         return node->data;
//     }
//     else
//     {
//         return search_for_node(node->ptr_next, data_to_be_found, compare_function);
//     }
// }

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

struct que * add_to_que_sorted(struct que *que_num, void *data_to_be_stored, int (*compare_function)(void *data_ptr, void *data_to_be_compared))
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
    struct linked_list_node *temp_node = que_num->first_node;
    while (temp_node != NULL)
    {
        int compare_result = 0;
        compare_result = compare_function(node->data, temp_node->data);
        if(compare_result == 1)
        {
            node->ptr_prev = temp_node->ptr_prev;
            node->ptr_next = temp_node;
            temp_node->ptr_prev = node;
            temp_node = node->ptr_prev;
            if(temp_node != NULL)
            {
                temp_node->ptr_next = node;
            }
            else
            {
                que_num->first_node = node;
            }
            return que_num;
        }
        else if(compare_result == 0)
        {
            temp_node = temp_node->ptr_next;
        }
    }
    
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
