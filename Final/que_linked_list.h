//sturcture for linked list nodes
struct linked_list_node
{
    // ptr to prev
    struct linked_list_node *ptr_prev;
    // data;
    void *data;
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

void * peek_first_node(struct que *que_num);

void * peek_last_node(struct que *que_num);

struct que * add_to_que(struct que *que_num, void *data_to_be_stored);

void * pop_first_node(struct que *que_num);

void * pop_last_node(struct que *que_num);

void * search_for_node(struct linked_list_node *node, void * data_to_be_found,int (*compare_function)(void *data_ptr, void *data_to_be_compared));


