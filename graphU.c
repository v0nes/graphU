#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main(void)
{
    int n = 0, n1 = 0, n2 = 0;
    int i, j;
    char buffer = ' ';
    int* x_graph_1 = (int*)malloc(2 * sizeof(int));
    int* y_graph_1 = (int*)malloc(2 * sizeof(int));
    int* x_graph_2 = (int*)malloc(2 * sizeof(int));
    int* y_graph_2 = (int*)malloc(2 * sizeof(int));
    bool crossing_flag = false;

    FILE* graph_file;
    if ((graph_file = fopen("graph_file.txt", "w")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    fprintf(graph_file, "first graph:\n");
    while (buffer != '>')
    {   
        x_graph_1 = (int*)realloc(x_graph_1, ((n1 + 1) * sizeof(int)));
        y_graph_1 = (int*)realloc(y_graph_1, ((n1 + 1) * sizeof(int)));
        scanf("%d%d", (x_graph_1 + n1), (y_graph_1 + n1 ));
        buffer = getchar();
        if (*(x_graph_1 + n1) == -33686019 || *(x_graph_1 + n1) == -842150451)
        {
            *(x_graph_1 + n1) = -1;
        }
        if (*(y_graph_1 + n1) == -33686019 || *(y_graph_1 + n1) == -842150451)
        {
            *(y_graph_1 + n1) = -1;
        }
        fprintf(graph_file, "%d--%d;\n", *(x_graph_1 + n1), *(y_graph_1 + n1));
        n1++;
    }
    buffer = ' ';
    fprintf(graph_file, "second graph:\n");
    while (buffer != '>')
    {
        x_graph_2 = (int*)realloc(x_graph_2, ((n2 + 1) * sizeof(int)));
        y_graph_2 = (int*)realloc(y_graph_2, ((n2 + 1) * sizeof(int)));
        scanf("%d%d", (x_graph_2 + n2), (y_graph_2 + n2));
        buffer = getchar();
        if (*(x_graph_2 + n2) == -33686019 || *(x_graph_2 + n2) == -842150451)
        {
            *(x_graph_2 + n2) = -1;
        }
        if (*(y_graph_2 + n2) == -33686019 || *(y_graph_2 + n2) == -842150451)
        {
            *(y_graph_2 + n2) = -1;
        }
        fprintf(graph_file, "%d--%d;\n", *(x_graph_2 + n2), *(y_graph_2 + n2));
        n2++;
    }
    FILE* dot_file;
    if ((dot_file = fopen("dot_file.txt", "w")) == NULL)
    {
    	printf("Cannot open file.\n");
    	exit(1);
    }
    fprintf(dot_file, "graph G{\n");
    fprintf(graph_file, "union graph:\n");
    for (i = 0; i < n1; i = i++)
    {
        if (*(x_graph_1 + i) != -1)
        {
            if (*(y_graph_1 + i) != -1)
            {
               fprintf(dot_file, "%d -- %d;\n", *(x_graph_1 + i), *(y_graph_1 + i));
               fprintf(graph_file, "%d -- %d;\n", *(x_graph_1 + i), *(y_graph_1 + i));
            }
            else
            {
                fprintf(dot_file, "%d;\n", *(x_graph_1 + i));
                fprintf(graph_file, "%d;\n", *(x_graph_1 + i));
            }
        }
        for (j = 0; j < n2; j = j++)
        {
            if (((*(x_graph_1 + i) == *(x_graph_2 + j)) && (*(y_graph_1 + i) == *(y_graph_2 + j))) || ((*(x_graph_1 + i) == *(y_graph_2 + j)) && (*(y_graph_1 + i) == *(x_graph_2 + j))))
            {
                *(x_graph_2 + j) = -1;
                *(y_graph_2 + j) = -1;
                if (crossing_flag)
                {
                    if (*(x_graph_1 + i) != -1)
                    {
                        if (*(y_graph_1 + i) != -1)
                        {
                            fprintf(dot_file, "%d -- %d;\n", *(x_graph_1 + i), *(y_graph_1 + j));
                            fprintf(graph_file, "%d -- %d;\n", *(x_graph_1 + i), *(y_graph_1 + j));
                        }
                        else
                        {
                            fprintf(dot_file, "%d;\n", *(x_graph_1 + i));
                            fprintf(graph_file, "%d;\n", *(x_graph_1 + i));
                        }
                    }
                }
                crossing_flag = true;
            }
        }
        crossing_flag = false;
    }
    for (j = 0; j < n2; j++)
    {
        if (*(x_graph_2 + j) != -1)
        {
            if (*(y_graph_2 + j) != -1)
            {
                fprintf(dot_file, "%d -- %d;\n", *(x_graph_2 + j), *(y_graph_2 + j));
                fprintf(graph_file, "%d -- %d;\n", *(x_graph_2 + j), *(y_graph_2 + j));
            }
            else
            {
                fprintf(dot_file, "%d;\n", *(x_graph_2 + j));
                fprintf(graph_file, "%d;\n", *(x_graph_2 + j));
            }
        }
    }
    fprintf(dot_file, "}");
    fclose(dot_file);
    fclose(graph_file);
    system("dot C:\\Users\\duhin\\source\\repos\\graphU\\dot_file.txt -Tbmp -o graph.PNG");
    system("rundll32  \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen C:\\Users\\duhin\\source\\repos\\graphU\\graph.PNG");
}
