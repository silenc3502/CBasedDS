#include <stdio.h>
#include <stdlib.h>

typedef struct graph_record
{
	int v;
	int e;
	int **m;
}
graph_type;

typedef graph_type *	p_graph;

int **init_matrix(int nrow, int ncol, int value)
{
	int i, j;
	int **m;

	m = malloc(nrow * sizeof(int *));

	for (i = 0; i < nrow; i++)
	{
		m[i] = malloc(ncol * sizeof(int));

		for (j = 0; j < ncol; j++)
		{
			m[i][j] = value;
		}
	}

	return m;
}

void free_matrix(int **m, int nrow)
{
	int i;

	for (i = 0; i < nrow; i++)
	{
		free(m[i]);
	}

	free(m);
}

p_graph init_graph(int v)
{
	p_graph g = (p_graph)malloc(sizeof(graph_type));

	g->v = v;
	g->e = 0;
	g->m = init_matrix(v, v, 0);

	return g;
}

void insert_edge(p_graph g, int v1, int v2)
{
	if (g->m[v1][v2] == 0)
	{
		g->e++;
		g->m[v1][v2] = 1;
		// g->m[v2][v1] = 1;
	}
}

void print_matrix(p_graph graph)
{
	int i, j, len = graph->v;

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len; j++)
		{
			printf("%2d", graph->m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// 0   1   2   3   4   5   6
// A   B   C   D   E   F   G
int main(void)
{
	p_graph graph = init_graph(7);

	insert_edge(graph, 0, 3);
	insert_edge(graph, 0, 2);
	insert_edge(graph, 2, 3);
	insert_edge(graph, 2, 5);
	insert_edge(graph, 3, 5);
	insert_edge(graph, 3, 1);
	insert_edge(graph, 3, 4);
	insert_edge(graph, 1, 5);
	insert_edge(graph, 4, 6);

	print_matrix(graph);

	// free_graph(graph);

	return 0;
}
