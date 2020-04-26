/*
Reference taken from GEEKS FOR GEEKS

Implementation of Krushkal Algorithm in C++

A MST has (V – 1) edges where V is the number of vertices in the given graph. 
The time complexity for Kruskal’s algorithm is O(e log e), where e is the number of edges on graph.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

    struct Edge

    {
        int src, dest, weight;
    };
    struct Graph
    {
            int V, E;
            struct Edge* edge;
    };
    struct Graph* createGraph(int V, int E)
    {
        struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
        graph->V = V;
        graph->E = E;
        graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge)); 
        return graph;
    }

    struct subset

    {
            int parent;
            int rank;
    };

     

    int find(struct subset subsets[], int i)

    {

        if (subsets[i].parent != i)

            subsets[i].parent = find(subsets, subsets[i].parent);

     

        return subsets[i].parent;

    }

    void Union(struct subset subsets[], int x, int y)

    {

        int xroot = find(subsets, x);

        int yroot = find(subsets, y);


        if (subsets[xroot].rank < subsets[yroot].rank)

            subsets[xroot].parent = yroot;

        else if (subsets[xroot].rank > subsets[yroot].rank)

            subsets[yroot].parent = xroot;


        else

        {

            subsets[yroot].parent = xroot;

            subsets[xroot].rank++;

        }

    }

    int myComp(const void* a, const void* b)

    {

        struct Edge* a1 = (struct Edge*) a;

        struct Edge* b1 = (struct Edge*) b;

        return a1->weight > b1->weight;

    }

    void KruskalMST(struct Graph* graph)

    {

        int V = graph->V;

        struct Edge result[V]; // Tnis will store the resultant MST

        int e = 0; // An index variable, used for result[]

        int i = 0; // An index variable, used for sorted edges


        qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);


        struct subset *subsets = (struct subset*) malloc(V * sizeof(struct subset));


        for (int v = 0; v < V; ++v)

        {

            subsets[v].parent = v;

            subsets[v].rank = 0;

        }

        while (e < V - 1)

        {

            struct Edge next_edge = graph->edge[i++];

     

            int x = find(subsets, next_edge.src);

            int y = find(subsets, next_edge.dest);

     

            if (x != y)

            {

                result[e++] = next_edge;

                Union(subsets, x, y);

            }


        }

    
        cout<<"\nThe MST is :\n";

        for (i = 0; i < e; ++i)

            printf("%d -- %d == %d\n", result[i].src, result[i].dest,

                    result[i].weight);

        return;

    }

     

    // Driver program to test above functions

    int main()

    {

	int V ,E; 
	cout<<"\nEnter no. of vertices ";
    cin>>V;
    cout<<"\nEnter no. of edges ";
    cin>>E; 
	struct Graph* graph = createGraph(V, E);


	int n,s,d,w;
    cout<<"\nEnter node numebr ";
    cin>>n;
    for(int i=0 ; i<n;i++)
    {
        cout<<"\nEnter src ";
        cin>>s;
        cout<<"\nEnter dest ";
        cin>>d;
        cout<<"\nEnter weight ";
        cin>>w;
        graph->edge[i].src = s; 
	    graph->edge[i].dest = d; 
	    graph->edge[i].weight = w;

    }
     
     

        KruskalMST(graph);

     

        return 0;

    }    

/*

------------------------------------------------------OUTPUT------------------------------------------------------------

Enter no. of vertices 6

Enter no. of edges 6

Enter node numebr 5

Enter src 0

Enter dest 1

Enter weight 6

Enter src 1

Enter dest 2

Enter weight 2

Enter src 1

Enter dest 4

Enter weight 7

Enter src 2

Enter dest 3

Enter weight 12

Enter src 2

Enter dest 5

Enter weight 10

The MST is :

2 -- 3 == 4
0 -- 3 == 5
0 -- 1 == 10
*/
