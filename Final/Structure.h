typedef struct Edge Edge;
typedef struct Vertex Vertex;

struct Edge
{
    Vertex *point1;
    char name[32];
    int weight;
    Vertex *point2; 
};

struct Vertex
{
    struct que *edge_list;
    char name[32];
    int degree;
};

struct Graph
{
    struct que *edges;
    struct que *vertices;
};

