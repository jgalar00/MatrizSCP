#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 

int main(int argc, char** argv) {

	if(argc!=2) {
		printf("Uso: ./matrices_serie M (M=numero de filas y columnas de las matrices A y B)\n");
		return 1;
	}

	struct timeval start, end;

	srand (5);
	int M,i,j,a;
	char *v=NULL;
	M = strtol(argv[1], &v, 10);
	int **matriz_A;
	int **matriz_B;
	int **matriz_C;

	matriz_A = (int **)malloc(M*sizeof(int *));
	for (i=0;i<M;i++)
	matriz_A[i] = (int*) malloc (M*sizeof(int));

    matriz_B = (int **)malloc(M*sizeof(int *));
    for (i=0;i<M;i++)
    matriz_B[i] = (int*) malloc (M*sizeof(int));

    matriz_C = (int **)malloc(M*sizeof(int *));
    for (i=0;i<M;i++)
    matriz_C[i] = (int*) malloc (M*sizeof(int *));

	for(i=0;i<M;i++)
	{
		for(j=0;j<M;j++)
		{
			matriz_A[i][j] = rand()%101;
			matriz_B[i][j] = rand()%101;
		}
	}

	gettimeofday(&start, NULL);

	for (a = 0; a < M; a++) 
	{
    	for (i = 0; i < M; i++)
		{
        	int suma = 0;
        	for (j = 0; j < M; j++) 
			{
            	suma += matriz_A[i][j] * matriz_B[j][a];
        	}
        	matriz_C[i][a] = suma;
    	}
	}
 
    gettimeofday(&end, NULL);
 
    //long seconds = (end.tv_sec - start.tv_sec);
    //long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	float seconds = (end.tv_sec - start.tv_sec) + 1e-6*(end.tv_usec - start.tv_usec);
 
    printf("Tiempo ejecución: %0.8f segs\n", seconds);

	// Print matriz A
	// printf("Matriz A: \n");
	// for (i = 0; i < M; i++) 
	// {
    // 	for (j = 0; j < M; j++) 
	// 	{
    //     	printf("%d ", matriz_A[i][j]);
    // 	}
    // printf("\n");
	// }

	// Print matriz B
	// printf("Matriz B: \n");
	// for (i = 0; i < M; i++) 
	// {
    // 	for (j = 0; j < M; j++) 
	// 	{
    //     	printf("%d ", matriz_B[i][j]);
    // 	}
    // printf("\n");
	// }

	//Print matriz C (A*B)
	// printf("Matriz C (A*B): \n");
	// for (i = 0; i < M; i++) 
	// {
    // 	for (j = 0; j < M; j++) 
	// 	{
    //     	printf("%d ", matriz_C[i][j]);
    // 	}
    // printf("\n");
	// }

	free(matriz_A);
	free(matriz_B);
	free(matriz_C);

	return 0;
}
