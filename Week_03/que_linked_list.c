#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_validation.h"

//sturcture for linked list nodes
struct linked_list_node
{
    // ptr to prev
    struct linked_list_node *ptr_prev;
    // data;
    int num;
    // ptr to next
    struct linked_list_node *ptr_next;
};

//structure of a queue
struct que
{
    //ptr to the first node
    struct linked_list_node *first_node;
    //how many nodes there are
    int length;
    //ptr to  the last node
    struct linked_list_node *last_node;
};

//Looks at value stored in the first node of the queue
int peek_first_node(struct que que_num)
{
    // printf("First nodes Value: %d\n", que_num.first_node->num);
    return que_num.first_node->num;
}

//Looks at value stored in the Last node of the queue
int peek_last_node(struct que que_num)
{
    // printf("Last nodes Value: %d\n", que_num.last_node->num);
    return que_num.last_node->num;
}

//adds node to back of queue
void add_to_que(struct que *que_num, int data_to_be_stored)
{
    struct linked_list_node *node = {0};
    node = malloc(sizeof(struct linked_list_node));
    node->num = data_to_be_stored;
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

}

//returns the value that is stored in the first node of the queue and removes that node from queue
int pop_first_node(struct que *que_num)
{
    if (que_num->first_node == NULL)
    {
        printf("no data in que\n");
        return 0;
    }
    else
    {
        struct linked_list_node *temp_node = que_num->first_node;
        int temp_node_value = que_num->first_node->num;
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
int pop_last_node(struct que *que_num)
{
    if (que_num->last_node == NULL)
    {
        printf("no data in que\n");
        return 0;
    }
    else
    {
        struct linked_list_node *temp_node = que_num->last_node;
        int temp_node_value = que_num->last_node->num;
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


int main()
{
    struct que que_1 = {0};
    que_1.first_node = NULL;
    que_1.length = 0;
    que_1.last_node = NULL;
    int user_data = 1;
    int i = 0;
    char want_go[10] = {0};
    int debug = 0;

    while (user_data != 0)
    {
        printf("Give me an int to store. (0 ends program)\n");
        readline_int("%d", &user_data);
        add_to_que(&que_1, user_data);
    }

    if (debug == 1)
    {
        printf("pop first node test: %d\n", pop_first_node(&que_1));
        printf("pop last node test: %d\n", pop_last_node(&que_1));
        for (size_t i = 0; i < 3; i++)
        {
            printf("Test of peek front: %d\n", peek_first_node(que_1));
            printf("Test of peek end: %d\n", peek_last_node(que_1));
        }
        for (size_t i = 0; i <= 5; i++)
        {
            printf("pop last node test: %d\n", pop_last_node(&que_1));
        }
    }
}
