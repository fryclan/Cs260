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
    add_to_que(vertex1->edge_list, edge_name);
    add_to_que(vertex2->edge_list, edge_name);
    vertex1->degree += 1;
    vertex2->degree += 1;
    return edge_name;
}

//Function for finding the shortest path from one vertex to another
void shortest_path(char *vertex_name1, char *vertex_name2)
{
    
}

void Minimum_Spanning_Tree()
{

}

void main()
{
    struct Graph graph1 = { 0 };
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
    add_to_que(graph1.edges, add_edge(2, "G-F", 
        search_for_node(graph1.vertices->first_node,"G",check_vertex_name), 
        search_for_node(graph1.vertices->first_node,"F",check_vertex_name)));
    
    print_graph(&graph1);
}
