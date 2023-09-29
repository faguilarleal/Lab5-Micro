/** ---------------------------------------------------------
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3056 - Programacion de Microprocesadores
 * Auth:  Francis Aguilar 22243
 * Date:	2021/09/28
 * ---------------------------------------------------------
 * Ejercicio4.cpp
 * Laboratorio 05
 * Realizar: calcular el producto punto de dos vectores A y B, de 1000 elementos c/uno
 * ---------------------------------------------------------*/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <random>

//Defincion de variables: hilos, contador, variable mutex

#define nthreads 1000

pthread_t tid[nthreads];
pthread_mutex_t lock;
float Resultado = 0.0; 

float* v1= new float[nthreads]; 
float* v2= new float[nthreads]; 

void* productoPunto(void *arg){
    long threadID = (long) arg;
    int fin = (threadID == nthreads - 1)? nthreads: threadID + 1;

    float temp = 0.0;
    for (int i = threadID; i< fin; i++){
        pthread_mutex_lock(&lock);
        temp += v1[i]*v2[i]; // acumulador de la respuesta
        pthread_mutex_unlock(&lock);
    }
    pthread_mutex_lock(&lock);
    Resultado += temp;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void){

    int err;	
    const int tamanio= 1000;

    std::random_device rd;
    std::mt19937 mt(rd()); // Mersenne Twister 19937 como motor de generación

    // Definir un rango para los números aleatorios
    int min = 1;
    int max = 100;

    // Crear una distribución uniforme
    std::uniform_int_distribution<int> dist(min, max);


    for (int i=0 ; i< nthreads; ++i){
        v1[i]=dist(mt);
        v2[i]=dist(mt);
    }

// creacion erronea del mutex
    if (pthread_mutex_init(&lock, NULL) != 0) 	
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    //creacion de hilos
    for (intptr_t i = 0; i<nthreads; i++){
        if (pthread_create(&(tid[i]), NULL, &productoPunto, (void *)i) !=0){
             printf("\ncan't create thread ");	
        }
    }

    
    for (int i = 0; i<nthreads; i++){
        pthread_join(tid[i],NULL);
    }
    
    printf("Resultado del producto punto: %f\n", Resultado);
	
    pthread_mutex_destroy(&lock); 


    return 0; 
}
 