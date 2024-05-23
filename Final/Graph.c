#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structure.h"
#include "que_linked_list.h"


// find Degree of a vertex based on the list of edges that are connected to it
void print_graph(struct Graph *graph_name)
{
    struct linked_list_node *temp_vert = graph_name->vertices->first_node;
    struct linked_list_node *temp_edge = graph_name->edges->first_node;
    
    while (temp_vert != NULL)
    {
        Vertex *vertex_node = temp_vert->data;
        printf("%s\n", vertex_node->name);
        temp_vert = temp_vert->ptr_next;
    }
    while (temp_edge != NULL)
    {
        Edge *edge_node = temp_edge->data;
        printf("%s\n", edge_node->name);
        temp_edge = temp_edge->ptr_next;
    }
    
}

void print_que(struct que *que_to_be_printed)
{
    printf("\n");
    int sum_of_path = 0;
    struct linked_list_node *temp_edge = que_to_be_printed->first_node;
    while (temp_edge != NULL)
    {
        Edge *edge_node = temp_edge->data;
        sum_of_path += edge_node->weight;
        printf("%s\n", edge_node->name);
        temp_edge = temp_edge->ptr_next;
    }
    printf("sum of path: %d\n\n", sum_of_path);
}

struct que * find_shortest_path(struct que *que_of_ques)
{
    struct que *returned_path = NULL;
    struct linked_list_node *temp_que_node = que_of_ques->first_node;
    int sum_of_path = 0;
    int smallest_sum_of_path = 999999999;
    while (temp_que_node != NULL)
    {
        struct que *temp_edge_que = temp_que_node->data;
        struct linked_list_node *temp_edge = temp_edge_que->first_node;
        while (temp_edge != NULL)
        {
            Edge *edge_node = temp_edge->data;
            sum_of_path += edge_node->weight;
            // printf("%s\n", edge_node->name);
            temp_edge = temp_edge->ptr_next;
        }
        if (sum_of_path < smallest_sum_of_path)
        {
            smallest_sum_of_path = sum_of_path;
            returned_path = temp_edge_que;
        }
        temp_que_node = temp_que_node->ptr_next;
        // printf("sum of path: %d\n", sum_of_path);

        sum_of_path = 0;
    }
    printf("smallest sum of path: %d\n", smallest_sum_of_path);
    return returned_path;
}

//add a vertex to the graph
Vertex * add_vertex(char *name)
{
    Vertex *vertex = NULL;
    vertex = malloc(sizeof(Vertex));
    strcpy(vertex->name, name);
    vertex->edge_list = NULL;
    vertex->degree = 0;
    return vertex;
}

int check_vertex_name(void *vertex_v, void *vertex_name)
{
    Vertex *vertex = (Vertex *)vertex_v;
    char *name = (char *)vertex_name;
    if (strcmp(vertex->name, name) == 0)
    {
        return 1;
    }
    return 0;
}

int check_edge_name(void *edge_v, void *edge_name)
{
    Edge *edge = (Edge *)edge_v;
    char *name = (char *)edge_name;
    if (strcmp(edge->name, name) == 0)
    {
        return 1;
    }
    return 0;
}

int check_edge_weights_binary(void *edge_1, void *edge_2)
{
    Edge *edge1= (Edge *)edge_1;
    Edge *edge2 = (Edge *)edge_2;
    if (edge1==NULL&&edge2==NULL)
    {
        return -1;
    }
    else if (edge1 == NULL)
    {
        return 0;
    }
    else if (edge2 == NULL)
    {
        return 1;
    }
    else if (edge1->weight <= edge2->weight)
    {
        return 1;
    }
    return 0;
}

//add an edge to the graph
Edge * add_edge(int edge_weight, char *name, Vertex *vertex1, Vertex *vertex2)
{
    if (vertex1 == NULL || vertex2 == NULL)
    {
        printf("vertices invalaid\n");
        return NULL;
    }

    Edge *edge_name = NULL;
    edge_name = malloc(sizeof(Edge));
    strcpy(edge_name->name, name);
    edge_name->weight = edge_weight;
    edge_name->point1 = vertex1;
    edge_name->point2 = vertex2;
    vertex1->edge_list = add_to_que(vertex1->edge_list, edge_name);
    vertex2->edge_list = add_to_que(vertex2->edge_list, edge_name);
    vertex1->degree += 1;
    vertex2->degree += 1;
    return edge_name;
}

Edge * compare_edge_weights(Edge *edge1, Edge *edge2)
{
    if (edge1 == NULL)
    {
        return edge2;
    }
    else if (edge2 == NULL)
    {
        return edge1;
    }
    else if (edge1->weight <= edge2->weight)
    {
        return edge1;
    }
    return edge2;  
}
//find lowest edge weight out of specific vertex
Edge * find_lowest_edge_weight(Vertex *temp_vert)
{
    Edge *temp_edge = NULL;
    struct linked_list_node *temp_edge_node = temp_vert->edge_list->first_node;
    while (temp_edge_node != NULL)
    {
        Edge *edge_node = temp_edge_node->data;
        temp_edge = compare_edge_weights(temp_edge, edge_node);
        temp_edge_node = temp_edge_node->ptr_next;
    }
    return temp_edge;
}

Edge * find_lowest_edge_weight_edge_list(struct que *edges_fed_in)
{
    Edge *temp_edge = NULL;
    struct linked_list_node *temp_edge_node = edges_fed_in->first_node;
    while (temp_edge_node != NULL)
    {
        Edge *edge_node = temp_edge_node->data;
        temp_edge = compare_edge_weights(temp_edge, edge_node);
        temp_edge_node = temp_edge_node->ptr_next;
    }
    return temp_edge;
}

struct que * Move_from_que_to_que(struct que *que_to_move_from, struct que *que_to_move_to)
{
    struct linked_list_node *temp_node = que_to_move_from->first_node;

    while (temp_node !=NULL)
    {
        que_to_move_to = add_to_que(que_to_move_to, temp_node->data);
        temp_node = temp_node->ptr_next;
        pop_first_node(que_to_move_from);
    }
    return que_to_move_to;
}

//search a que to see if node data is already in que
int search_que_data(struct que *que_to_be_searched, Edge *data_to_be_checked)
{
    int flag_point_1_found = 0;
    int flag_point_2_found = 0;

    if (que_to_be_searched == NULL)
    {
        return 1;
    }
    
    struct linked_list_node *node_to_be_searched = que_to_be_searched->first_node;
    while (node_to_be_searched != NULL)
    {
        Edge *temp_edge_from_edge_que = node_to_be_searched->data;
        if (data_to_be_checked == temp_edge_from_edge_que)
        {
            return 0;
        }
        else if (data_to_be_checked->point1 == temp_edge_from_edge_que->point1 || 
            data_to_be_checked->point1 == temp_edge_from_edge_que->point2)
        {
            flag_point_1_found = 1;
        }
        if (data_to_be_checked->point2 == temp_edge_from_edge_que->point1 || 
            data_to_be_checked->point2 == temp_edge_from_edge_que->point2)
        {
            flag_point_2_found = 1;
        }

        if (flag_point_1_found && flag_point_2_found)
        {
            return 0;
        }
        
        
        node_to_be_searched = node_to_be_searched->ptr_next;
    }
    return 1;
}

struct que * paths_from_a_to_z(struct Graph *graph, struct que *edge_que_passed_in, struct que *A_Z_path_ques, char *starting_point, char *ending_point)
{
    static int nested_levels = 0;
    struct linked_list_node *node_vert = graph->vertices->first_node;
    struct linked_list_node *node_edge = graph->edges->first_node;
    Vertex *ending_vert = search_for_node(node_vert, ending_point,check_vertex_name);
    Vertex *starting_vert = search_for_node(node_vert, starting_point,check_vertex_name);
    nested_levels++;
    // printf("starting_vert name: %s, %d\n", starting_vert->name, nested_levels);

    if (nested_levels >= 50)
    {
        nested_levels--;
        return NULL;
    }

    Vertex *temp_vert = NULL;
    struct que *edge_que = edge_que_passed_in;
    struct linked_list_node *temp_edge_node = starting_vert->edge_list->first_node;
    struct que *path_que = A_Z_path_ques;

    temp_vert = starting_vert;
    temp_edge_node = temp_vert->edge_list->first_node;
    
    while (temp_edge_node != NULL)
    {
        Edge *temp_edge = temp_edge_node->data;
        if (search_que_data(edge_que, temp_edge) == 1)
        {
            edge_que = add_to_que(edge_que, temp_edge);
            if (temp_edge->point1 == ending_vert || temp_edge->point2 == ending_vert)
            {
                struct que *edge_que_copy = NULL;
                struct linked_list_node *temp_node = edge_que->first_node;
                while (temp_node != NULL)
                {
                    Edge *temp_storage = temp_node->data;
                    edge_que_copy = add_to_que(edge_que_copy, temp_storage);
                    temp_node = temp_node->ptr_next;
                }
                
                path_que = add_to_que(path_que, edge_que_copy);
                if (nested_levels > 1)
                {
                    pop_last_node(edge_que);
                }
                
            }
            else
            {
                if(check_vertex_name(temp_edge->point1, starting_vert->name) == 1)
                {
                    temp_vert = temp_edge->point2;
                }
                else if(check_vertex_name(temp_edge->point2, starting_vert->name) == 1)
                {
                    temp_vert = temp_edge->point1;
                }
                // printf("before recursion goes down\n");
                // print_que(edge_que);
                edge_que = paths_from_a_to_z(graph, edge_que, path_que, temp_vert->name, ending_point);
                // printf("after edge_que is stored and returns from recursion\n");
            }
        }
        temp_edge_node = temp_edge_node->ptr_next;
    }
    pop_last_node(edge_que);
    nested_levels--;
    return edge_que;
}

struct Graph Minimum_Spanning_Tree(struct Graph *graph_fed_in)
{
//need to make 4 ques: que 1 list of vertices in graph and not in tree, que 2 list of vertices added to minimum spanning tree, que 3 temp list of
//connected vertices not in tree, que 4 list of edges in graph sorteded by weight
//step one connect 2 vertices from graph with lowest edge value from list (should be first one) add vertices to que 2 remove vertices from que 1 
//step 2 cheak next lowest weighted edge's points for one in tree and one not in tree or neither in tree if neither in tree add points to que 3
//repeat step 2 till all vertices are in tree
    struct que *verts_not_in_spaning_tree = graph_fed_in->vertices;
    struct que *edges_not_sorted = graph_fed_in->edges;
    struct que *verts_in_spanning_tree = NULL;
    struct que *verts_connected_not_in_tree = NULL;
    struct que *sorted_edges = NULL;
    struct que *edges_in_spanning_tree = NULL;
    struct que *edges_connected_not_in_tree = NULL;
    struct Graph graph_to_return = { 0 };
    printf("is it breaking here\n");
    // print_que(edges_not_sorted);
    struct linked_list_node *temp_edge = NULL;
    temp_edge = edges_not_sorted->first_node;

    while (temp_edge !=NULL)
    {
        sorted_edges = add_to_que_sorted(sorted_edges, temp_edge->data, check_edge_weights_binary);
        temp_edge = temp_edge->ptr_next;
    }
    print_que(sorted_edges);
    // printf("how about here\n");
    struct linked_list_node *temp_node = sorted_edges->first_node;
    // printf("is it in the while loop?\n");
    int counter = 0;
    while (temp_node != NULL)
    {
        // counter = counter + 1;
        // printf("loop count %d\n", counter);
        struct Edge *edge_to_connect = temp_node->data;
        // printf("or mayble it is the edge structure?\n");
        if (verts_in_spanning_tree == NULL)
        {
            // printf("was it the first if\n");
            verts_in_spanning_tree = add_to_que(verts_in_spanning_tree, edge_to_connect->point1);
            verts_in_spanning_tree = add_to_que(verts_in_spanning_tree, edge_to_connect->point2);
            edges_in_spanning_tree = add_to_que(edges_in_spanning_tree, edge_to_connect);
            // printf("well it wasnt the first if statment\n");
        }
        //cheak for vert 1 in tree
        else if (search_for_node(verts_in_spanning_tree->first_node, edge_to_connect->point1, check_vertex_name) != NULL)
        {
            // printf("how about the vert 1 cheak\n");
            if (search_for_node(verts_in_spanning_tree->first_node, edge_to_connect->point2, check_vertex_name) == NULL)
            {
                if (verts_connected_not_in_tree != NULL)
                {
                    if (search_for_node(verts_connected_not_in_tree->first_node, edge_to_connect->point2, check_vertex_name) != NULL)
                    {
                        // printf("is it the move function?\n");
                        verts_in_spanning_tree = Move_from_que_to_que(verts_connected_not_in_tree, verts_in_spanning_tree);
                        edges_in_spanning_tree = Move_from_que_to_que(edges_connected_not_in_tree, edges_in_spanning_tree);
                        // printf("so it wasnt the move from que to que\n");
                    }
                    else
                    {
                        // printf("was it the else statment?\n");
                        verts_in_spanning_tree = add_to_que(verts_in_spanning_tree,edge_to_connect->point2);
                        edges_in_spanning_tree = add_to_que(edges_in_spanning_tree, edge_to_connect);
                    }
                }
                else
                {
                    verts_in_spanning_tree = add_to_que(verts_in_spanning_tree,edge_to_connect->point2);
                    edges_in_spanning_tree = add_to_que(edges_in_spanning_tree, edge_to_connect);
                }
            }
            else
            {
                /* code */
            }
            
            // printf("how about the vert 1 cheak\n");
        }
        //cheak for vert 2 in tree
        else if ((verts_in_spanning_tree->first_node, edge_to_connect->point2, check_vertex_name) != NULL)
        {
            // printf("gotcha its this one\n");
            if (search_for_node(verts_in_spanning_tree->first_node, edge_to_connect->point1, check_vertex_name) == NULL)
            {
                // printf("was it the first if check in the else if?\n");
                if (verts_connected_not_in_tree != NULL)
                {
                    if (search_for_node(verts_connected_not_in_tree->first_node, edge_to_connect->point1, check_vertex_name) != NULL)
                    {
                        // printf("is it the move function?\n");
                        verts_in_spanning_tree = Move_from_que_to_que(verts_connected_not_in_tree, verts_in_spanning_tree);
                        edges_in_spanning_tree = Move_from_que_to_que(edges_connected_not_in_tree, edges_in_spanning_tree);
                        // printf("so it wasnt the move from que to que\n");
                    }
                    else
                    {
                        // printf("was it the else statment?\n");
                        verts_in_spanning_tree = add_to_que(verts_in_spanning_tree,edge_to_connect->point1);
                        edges_in_spanning_tree = add_to_que(edges_in_spanning_tree, edge_to_connect);
                    }
                }
                else
                {
                    verts_in_spanning_tree = add_to_que(verts_in_spanning_tree,edge_to_connect->point1);
                    edges_in_spanning_tree = add_to_que(edges_in_spanning_tree, edge_to_connect);
                }
            }
            // printf("how about the vert 2 cheak\n");
        }
        //cheak for neither in tree
        else if (search_for_node(verts_in_spanning_tree->first_node, edge_to_connect->point1, check_vertex_name) == NULL && search_for_node(verts_in_spanning_tree->first_node, edge_to_connect->point2, check_vertex_name) == NULL)
        {
            // printf("is it the neither\n");
            if (verts_connected_not_in_tree == NULL)
            {
                verts_connected_not_in_tree = add_to_que(verts_connected_not_in_tree, edge_to_connect->point1);
                verts_connected_not_in_tree = add_to_que(verts_connected_not_in_tree, edge_to_connect->point2);
                edges_connected_not_in_tree = add_to_que(edges_connected_not_in_tree, edge_to_connect);
            }
            else if (search_for_node(verts_connected_not_in_tree->first_node, edge_to_connect->point1, check_vertex_name) != NULL)
            {
                if (search_for_node(verts_connected_not_in_tree->first_node, edge_to_connect->point2, check_vertex_name) == NULL)
                {
                    verts_connected_not_in_tree = add_to_que(verts_connected_not_in_tree, edge_to_connect->point2);
                    edges_connected_not_in_tree = add_to_que(edges_connected_not_in_tree, edge_to_connect);
                } 
            }
            else if (search_for_node(verts_connected_not_in_tree->first_node, edge_to_connect->point2, check_vertex_name) != NULL)
            {
                if (search_for_node(verts_connected_not_in_tree->first_node, edge_to_connect->point1, check_vertex_name) == NULL)
                {
                    verts_connected_not_in_tree = add_to_que(verts_connected_not_in_tree, edge_to_connect->point1);
                    edges_connected_not_in_tree = add_to_que(edges_connected_not_in_tree, edge_to_connect);
                } 
            }
            // printf("how about the vert neither cheak\n");
        }
        temp_node = temp_node->ptr_next;
        // printf("end of loop\n");
    }
    // printf("well it wasn't the while loop stuff???\n");
    graph_to_return.edges = edges_in_spanning_tree;
    graph_to_return.vertices = verts_in_spanning_tree;
    return graph_to_return;
}

void main()
{
    struct Graph graph1 = { 0 };
    struct que *path_que_ptr = NULL;
    struct que que_of_ques = { 0 };
    struct Graph minimum_spanning_tree = { 0 };
    graph1.vertices = add_to_que(graph1.vertices, add_vertex("A"));
    add_to_que(graph1.vertices, add_vertex("B"));
    add_to_que(graph1.vertices, add_vertex("C"));
    add_to_que(graph1.vertices, add_vertex("D"));
    add_to_que(graph1.vertices, add_vertex("E"));
    add_to_que(graph1.vertices, add_vertex("F"));
    add_to_que(graph1.vertices, add_vertex("G"));
    graph1.edges = add_to_que(graph1.edges, add_edge(1, "A-B", 
        search_for_node(graph1.vertices->first_node,"A",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"B",check_vertex_name)));
    add_to_que(graph1.edges, add_edge(2, "A-D", 
        search_for_node(graph1.vertices->first_node,"A",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"D",check_vertex_name)));
    add_to_que(graph1.edges, add_edge(3, "A-E", 
        search_for_node(graph1.vertices->first_node,"A",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"E",check_vertex_name)));
    add_to_que(graph1.edges, add_edge(2, "B-D", 
        search_for_node(graph1.vertices->first_node,"B",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"D",check_vertex_name)));
    add_to_que(graph1.edges, add_edge(3, "B-C", 
        search_for_node(graph1.vertices->first_node,"B",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"C",check_vertex_name)));
    add_to_que(graph1.edges, add_edge(12, "C-D", 
        search_for_node(graph1.vertices->first_node,"C",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"D",check_vertex_name)));
    add_to_que(graph1.edges, add_edge(6, "D-E", 
        search_for_node(graph1.vertices->first_node,"D",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"E",check_vertex_name)));
    add_to_que(graph1.edges, add_edge(4, "E-F", 
        search_for_node(graph1.vertices->first_node,"E",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"F",check_vertex_name)));
    add_to_que(graph1.edges, add_edge(5, "E-G", 
        search_for_node(graph1.vertices->first_node,"E",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"G",check_vertex_name)));
    add_to_que(graph1.edges, add_edge(2, "F-G", 
        search_for_node(graph1.vertices->first_node,"F",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"G",check_vertex_name)));

    //prints Full Gragh Structure
    print_graph(&graph1);
    printf("\n");
    //prints Full Graph Structure

    //shortest path print
    paths_from_a_to_z(&graph1,path_que_ptr,&que_of_ques,"C","G");
    path_que_ptr = find_shortest_path(&que_of_ques);
    print_que(path_que_ptr);
    //sortest path print finished
    // printf("where did it break\n");
    //minimum spanning tree print stuff
    minimum_spanning_tree = Minimum_Spanning_Tree(&graph1);
    // printf("did it assign the returned function\n");
    print_graph(&minimum_spanning_tree);
    //minimum spanning tree print stuff


    // printf("\nstart of test\n");
    // struct que *test_for_move = NULL;
    // print_que(graph1.edges);
    // printf("it is printing the graph edges correctly\n");
    // test_for_move = Move_from_que_to_que(graph1.edges, test_for_move);
    // printf("it moved correctly\n");
    // print_que(test_for_move);
    
}
