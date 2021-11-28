#define _CRT_SECURE_NO_WARNINGS
#define HEADER ("Лабораторная работа №5\nВыполнил: Пантюшов Е.И.\n")
#include <queue>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
using namespace std;
struct node
{
	int vertex;
	struct node* next;
};

struct Graph
{
	int numVertices;
	struct node** adjList;
};

struct node* createNode(int v)
{
	struct node* newNode = (node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int vertices)
{
	struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;
	graph->adjList = (node**)malloc(vertices * sizeof(struct node*));
	for (int i = 0; i < vertices; i++)
		graph->adjList[i] = NULL;
	return graph;
}
struct queue1
{
	int element;
	struct queue1* next;
};
struct q
{
	struct queue1* peredn, * zadn;
};
struct q* sozd()
{
	struct q* a = (q*)malloc(sizeof(q));
	a->peredn = 0;
	a->zadn = 0;
	return (a);
}
void push(struct q* a, int x)
{
	struct queue1* nov = (queue1*)malloc(sizeof(queue1));
	nov->element = x;
	nov->next = 0;
	if (a->peredn == 0)
		a->peredn = nov;
	else {
		if (a->zadn == 0) {
			a->zadn = nov;
			a->peredn->next = nov;
		}
		else
		{
			a->zadn->next = nov;
			a->zadn = nov;
		}
	}
}

void pop(struct q* a, int x)
{
	if (a->peredn)
	{
		struct queue1* temp = (queue1*)malloc(sizeof(queue1));
		temp = a->peredn;
		a->peredn = temp->next;
		free(temp);
	}
}
void addEdge(struct Graph* graph, int i, int j)
{
	struct node* newNode = createNode(j);
	if (graph->adjList[i] == NULL)
	{
		graph->adjList[i] = newNode;
		newNode = NULL;
	}
	struct node* temp = graph->adjList[i];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;

	newNode = createNode(i);
	if (graph->adjList[j] == NULL)
	{
		graph->adjList[j] = newNode;
		newNode = NULL;
	}
	temp = graph->adjList[j];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}

void printGraph(struct Graph* graph)
{
	for (int i = 0; i < graph->numVertices; i++)
	{
		struct node* temp = graph->adjList[i];
		printf("%d-я вершина: ", i);
		while (temp)
		{
			printf("%d ", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}
}

void bfs(int** G, int* NUM, int v, int n)
{
	clock_t t1, t2;
	float res;
	t1 = clock();
	queue <int> q;
	q.push(v);
	NUM[v] = 1;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		printf(" %d ", v);
		for (int i = 0; i < n; i++)
		{
			if ((G[v][i] == 1) && (NUM[i] == 0))
			{
				q.push(i);
				NUM[i] = 1;
			}
		}
	}
	t2 = clock();
	res = t2 - t1;
	printf("\nВремя работы алгоритма через библиотеку: %f\n", res / 1000);
}

void bfs_list(struct Graph* graph, int* NUM, int v, int n)
{
	queue <int> q;
	q.push(v);
	NUM[v] = 1;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		printf("%d ", v);
		struct node* list = graph->adjList[v];
		while (list)
		{
			if (NUM[list->vertex] == 0)
			{
				q.push(list->vertex);
				NUM[list->vertex] = 1;
			}
			list = list->next;
		}
	}
}

void bfs_sv(int** G, int* NUM, int v, int n)
{
	clock_t t1, t2;
	float res;
	t1 = clock();
	struct q* a = sozd();
	push(a, v);
	NUM[v] = 1;
	while (a->peredn)
	{
		v = a->peredn->element;
		pop(a, v);
		printf(" %d ", v);
		for (int i = 0; i < n; i++)
		{
			if ((G[v][i] == 1) && (NUM[i] == 0))
			{
				push(a, i);
				NUM[i] = 1;
			}
		}
	}
	t2 = clock();
	res= res = t2 - t1;
	printf("\nВремя работы алгоритма через очередь,реализованную самостоятельо %f\n", res / 1000);
}
void task_1_1(int** G, int n)
{
	printf("\nЗадание 1.\n\nПункт 1.\nМатрица смежности:\n");
	for (int i = 0; i < n; i++)
	{
		G[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
		{
			G[i][j] = rand() % 2;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				G[i][j] = 0;
			}
			else
			{
				G[i][j] = G[j][i];
			}
			printf(" %d ", G[i][j]);
		}
		printf("\n");
	}
}

void task_1_2(int** G, int n)
{
	int* NUM = (int*)malloc(n * sizeof(int));
	int v;
	for (int i = 0; i < n; i++)
	{
		NUM[i] = false;
	}
	printf("\nПункт 2.\nВведите точку входа: ");
	scanf("%d", &v);
	printf("Результат работы алгоритма обхода в ширину(матрица): ");
	bfs(G, NUM, v, n);
	free(NUM);
}

void task_1_3(struct Graph* graph, int n, int** G)
{
	struct node** node = graph->adjList;
	int v;
	int* NUM = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((G[i][j] == 1) && (i < j))
			{
				addEdge(graph, i, j);
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		NUM[i] = false;
	}
	printf("\n\nПункт 3.\nСписок смежности: \n");
	printGraph(graph);
	printf("Введите точку входа: ");
	scanf("%d", &v);
	printf("Результат работы алгоритма обхода в ширину(список): ");
	bfs_list(graph, NUM, v, n);
	printf("\n\n");
	free(NUM);
}
void task_2_1(struct Graph* graph, int n, int** G)
{
	int* NUM = (int*)malloc(n * sizeof(int));
	int v;
	for (int i = 0; i < n; i++)
	{
		NUM[i] = false;
	}
	printf("Введите точку входа: ");
	scanf("%d", &v);
	printf("Результат работы алгоритма обхода в ширину через очередь(): ");
	bfs_sv(G, NUM, v, n);
	printf("\n\n");
	free(NUM);
}


int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	printf(HEADER);
	printf("Введите размерность матрицы: ");
	int n;
	scanf("%d", &n);
	int** G = (int**)malloc(n * sizeof(int*));
	struct Graph* graph = createGraph(n);
	task_1_1(G, n);
	task_1_2(G, n);
	task_1_3(graph, n, G);
	task_2_1(graph, n, G);
	free(G);
	system("PAUSE");
	return 0;
}