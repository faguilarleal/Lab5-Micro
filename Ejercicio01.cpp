/** ---------------------------------------------------------
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3056 - Programacion de Microprocesadores
 * Auth: 	Kimberly Barrera
 * Date:	2021/08/25
 * Mod.:    2023/09/20
 *  * Modificado por : Francis Aguilar 22243
 * ---------------------------------------------------------
 * Ejercicio01.cpp
 * Laboratorio 05
 * Realizar: identificar de problemas en sincronización.
 * ---------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

//Defincion de variables: hilos, contador, variable mutex

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* doSomeThing(void *arg)
{
    unsigned long i = 0;
    counter += 1;								//incialización variable utilizada para retardo
    printf("\n Job %d started\n", counter);

    for(i=0; i<(0xFFFFF);i++);
    printf("\n Job %d finished\n", counter);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;
    if (pthread_mutex_init(&lock, NULL) != 0) 	//inicializacion de mutex no completada
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    while(i < 2)								//se crean solo 2 hilos
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL); 	//creacion de hilos sin paso de parametros
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));	//impresion de mensaje si el hilo no se crea correctamente
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);				//destruccion de mutex dinamica ya usada

    return 0;
}