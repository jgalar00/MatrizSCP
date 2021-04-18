#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/time.h>  
#include <math.h>

int main(int argc, char** argv) {

	if(argc!=2) 
  {
		printf("Uso: ./run.sh \"matrices_MPI2 M\" (M= numero de filas y columnas de las matrices A y B)\n");
		return 1;
	}

  int world_rank, world_size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  //struct timeval start, end;

	srand (5);
	int M,i,j,k,a,filas_proc,tam,z;
	char *v=NULL;
	M = strtol(argv[1], &v, 10);


  if (M<world_size ) 
  {
    fprintf(stderr, "El numero de procesadores tiene que ser < M%s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  } 
  else if ((M%world_size) != 0)
  {
    fprintf(stderr, "El numero de procesadores tiene que ser divisor de M%s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  filas_proc = M/world_size;
  tam = filas_proc*M;

	int *matriz_A;
	int *matriz_B;
	int *matriz_C;
  int *traspuesta_B;
  int *vector_A;
  int *vector_B;
  int *vector_C;

  matriz_A = (int *)malloc(M*M*sizeof(int));
  matriz_B = (int *)malloc(M*M*sizeof(int));
  traspuesta_B = (int *)malloc(M*M*sizeof(int));
  matriz_C = (int *)malloc(M*M*sizeof(int));

  vector_A = (int *)malloc(tam*sizeof(int));
  vector_B = (int *)malloc(tam*sizeof(int));
  vector_C = (int *)malloc(tam*sizeof(int));

  if (world_rank == 0) 
  {
    for(i=0;i<M;i++)
	  {
		  for(j=0;j<M;j++)
		  {
			matriz_A[M*i+j] = rand()%101;
			matriz_B[M*i+j] = rand()%101;
      traspuesta_B[M*j+i] = matriz_B[M*i+j];
		  }
	  }


    //gettimeofday(&start, NULL);
    

  }

  for(i=0;i<tam;i++)
  {
    vector_C[i] = 0;
  }

  double inicio, final, tiempo_transcurrido;
  inicio = MPI_Wtime();

  MPI_Scatter(matriz_A,tam,MPI_INT,vector_A,tam,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Scatter(traspuesta_B,tam,MPI_INT,vector_B,tam,MPI_INT,0,MPI_COMM_WORLD);

  for(k=0; k<world_size; k++)
  {

    for (j=0;j<filas_proc;j++)
    {
      for(z=0;z<filas_proc;z++)
      {
        for(i=0; i<M; i++)
        {
          vector_C[(((world_rank*filas_proc)+(k*filas_proc))%M)+(j*M)+z] += vector_A[i+(j*M)]*vector_B[i+(z*M)];
        }
      }
    }

    int send_rank = (int)(fabs(world_rank+(world_size-1)))%world_size;
    int recv_rank = (int)(fabs(world_rank+1))%world_size;
    
    MPI_Send(vector_B, tam, MPI_INT, send_rank, 0, MPI_COMM_WORLD);
    MPI_Recv(vector_B, tam, MPI_INT, recv_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
  }

  MPI_Gather(vector_C,tam,MPI_INT,matriz_C,tam,MPI_INT,0,MPI_COMM_WORLD);

  final = MPI_Wtime();
  tiempo_transcurrido = final-inicio;

  //Print matriz C
  if(world_rank == 0) 
  {

    //gettimeofday(&end, NULL);
 
    //long seconds = (end.tv_sec - start.tv_sec);
    //long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    printf("Tiempo ejecución: %f segs\n", tiempo_transcurrido);

	  // printf("Matriz C (A*B): \n");
    // fflush(stdin);
	  // for (i = 0; i < M; i++) 
	  // {
    //   for (j = 0; j < M; j++) 
		//   {
    //     printf("%d ", matriz_C[M*i+j]);
    //     fflush(stdin);
    //   }
    //   printf("\n");
    //   fflush(stdin);
	  // }
  }

  MPI_Finalize();

  free(matriz_A);
  free(matriz_B);
	free(matriz_C);
  free(traspuesta_B);
  free(vector_A);
	free(vector_B);
  free(vector_C);

}