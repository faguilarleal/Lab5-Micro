/** ---------------------------------------------------------
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3056 - Programacion de Microprocesadores
 * Auth: 	Kimberly Barrera
 * Date:	2021/08/25
 * Mod.:    2023/09/20
 * Modificado por : Francis Aguilar 22243
 * ---------------------------------------------------------
 * Ejercicio02.cpp
 * Laboratorio 05
 * Realizar: sincronización trabajo con mutex
 * ---------------------------------------------------------*/
 
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define NTHREADS 10

//Defincion de variables: hilos, contador
pthread_t tid[NTHREADS];					
int counter;
pthread_mutex_t mtx; //mutex

void* function(void *arg)												//subrutina de inicio: imprime inicio y fin thread
{
    int i; 
	i = (long) i;
	unsigned long j = 0;	
    											//incialización variable utilizada para retardo
    pthread_mutex_lock(&mtx);
	counter += 1;

    printf("\n----    Job %d started    ----\n", counter);	
	printf("    Realizado por hilo No. %d\n",i);
	
    pthread_mutex_unlock(&mtx);

    for(j=0; j<(0xFFFFF);j++);	
    pthread_mutex_lock(&mtx);										//retardo
    printf("\n----   Job %d finished   ----\n", counter);				//indicador fin procesos de iésimo hilo
    
    pthread_mutex_unlock(&mtx);

    pthread_exit(0);
}

int main(void)
{
    long i = 0;		
    int err;									
    if (pthread_mutex_init(&mtx, NULL) != 0) 	//inicializacion de mutex no completada
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    while(i < NTHREADS)													//se crean  hilos
    {
        err = pthread_create(&(tid[i]), NULL, &function, (void *)i);	//creacion de hilos con paso de parametros
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));		//impresion de mensaje si el hilo no se crea correctamente
        i++;													
    }

	for (i=0;i<NTHREADS;i++)
	{ 
		pthread_join(tid[i],NULL);
	} 
	pthread_mutex_destroy(&mtx);				//destruccion de mutex dinamica ya usada

    return 0;
}