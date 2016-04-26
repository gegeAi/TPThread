#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>

#include "NombresPremiersConcurrent.h"

uint64_t * nombresPremiers(uint64_t n, int * taille);
Liste * factorisation(uint64_t n);
void print_prime_factors(uint64_t n);
void * run(void * param);

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexScanf=PTHREAD_MUTEX_INITIALIZER;
static FILE * f = NULL;

int main()
{
	int i=0;
	if((f=fopen("input.txt","r")) != NULL)
	{
		pthread_t t1=0;
		pthread_t t2=0;
		pthread_create(&t1, NULL, run, NULL);
		//pthread_create(&t2, NULL, run, NULL);
		
		pthread_join(t1, NULL);	
		//pthread_join(t2, NULL);

		fclose(f);
	}

	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutexScanf);
	
	return 0;
}

uint64_t * nombresPremiers(uint64_t n, int * taille)
{
	uint64_t i;
	uint64_t * renvoi = (uint64_t *) malloc(sizeof(uint64_t)*n/3);
	int indice = 2; 
	int saut = 2;
	renvoi[0]=2;
	renvoi[1]=3;
	for(i=5; i<=n; i+=saut, saut=6-saut)
	{
		uint64_t j;
		for(j=(uint64_t)(sqrt(i-1)+1); j>1 && i%j!=0; j--);

		if(j==1)
		{
			renvoi[indice++] = i;
		}
	}
	*taille=indice;
	return renvoi;
}


Liste * factorisation(uint64_t n)
{
	Liste * renvoi = (Liste *) malloc(sizeof(Liste));
	Liste * finListe = renvoi;
	int nbDepart = n;
	int taillePremier=0;
	uint64_t * tabPremier = nombresPremiers(n, &taillePremier);
	int i;
	uint64_t produit = 1;
	for(i=0; i<taillePremier && produit < nbDepart; i++)
	{
		if(n%tabPremier[i]==0)
		{
			Liste * suivant = (Liste *) malloc(sizeof(Liste));
			suivant->suivant = NULL;
			finListe->n = tabPremier[i];
			finListe->suivant = suivant;
			finListe = suivant;
			n/=tabPremier[i];
			produit *= tabPremier[i--];
		}
	}
	if(n!= 1)
	{
		free(renvoi);
		renvoi = NULL;
	}
	free(tabPremier);
	return renvoi;
}


void print_prime_factors(uint64_t n)
{
	Liste * tab = factorisation(n);
	int i;
	pthread_mutex_lock(&mutex);
	printf("%ld : ", n);
	if(tab == NULL)
	{
		printf("%ld %d", n, 1);
	}
	else
	{
		do
		{
			printf("%ld ", tab->n);
			Liste * tps = tab->suivant;
			free(tab);
			tab = tps;
		}while(tab->suivant != NULL);
	}
	printf("\n");
	pthread_mutex_unlock(&mutex);
	free(tab);
}

void * run(void * param)
{
	uint64_t n;
	
	pthread_mutex_lock(&mutexScanf);
	while(fscanf(f, "%ld",&n) != EOF)
	{
		pthread_mutex_unlock(&mutexScanf);
		
		print_prime_factors(n);

		pthread_mutex_lock(&mutexScanf);
	}
	pthread_mutex_unlock(&mutexScanf);

	pthread_exit(NULL);
}



