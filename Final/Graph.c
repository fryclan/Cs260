#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structure.h"


// find Degree of a vertex based on the list of edges that are connected to it
int FindDegree(Vertex *vertex_name)
{
    
}

//add a vertex to the graph
void add_vertex(Vertex *vertex_name)
{
    vertex_name = malloc(sizeof(Vertex));
    vertex_name->name[32] = ("%s", vertex_name);
}

//add an edge to the graph
void add_edge(Edge *edge_name,int edge_weight, Vertex *vertex1, Vertex *vertex2)
{
    edge_name = malloc(sizeof(Edge));
    edge_name->weight = edge_weight;
    edge_name->point1 = vertex1;
    edge_name->point2 = vertex2;  
}

//Function for finding the shortest path from one vertex to another
void shortest_path(Vertex *vertex1, Vertex *vertex2)
{
    //find the smallest weight in the first vertexes edge list and
}

void Minimum_Spanning_Tree()
{

}

