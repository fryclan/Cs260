typedef struct Edge Edge;
typedef struct Vertex Vertex;

struct Edge
{
    Vertex *point1;
    int weight;
    Vertex *point2; 
};

struct Vertex
{
    Edge *edge_list;
    char name[32];
    int degree;
};


