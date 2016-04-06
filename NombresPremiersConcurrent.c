#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>

uint64_t * nombresPremiers(uint64_t n, int * taille);
uint64_t * factorisation(uint64_t n, int * taille);
void print_prime_factors(uint64_t n);
void * run(void * param);

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexScanf=PTHREAD_MUTEX_INITIALIZER;
static FILE * f = NULL;

int main()
{
	int i=0;
	if((f=fopen("numbers.txt","r")) != NULL)
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
	uint64_t * renvoi = (uint64_t *) malloc(sizeof(uint64_t)*n);
	int indice = 2; 
	int saut = 2;
	renvoi[0]=2;
	renvoi[1]=3;
	for(i=5; i<=n; i+=saut, saut=6-saut)
	{
		uint64_t j;
		for(j=(uint64_t)(sqrt(i-1)+1); j>1 && i%j!=0; j--);

		if(j=1)
		{
			renvoi[indice++] = i;
		}
	}
	*taille=indice;
	return renvoi;
}


uint64_t * factorisation(uint64_t n, int * taille)
{
	uint64_t * renvoi = (uint64_t *) malloc(sizeof(uint64_t)*((uint64_t)sqrt(n)+1));
	int indice = 0;
	int taillePremier=0;
	uint64_t * tabPremier = nombresPremiers(sqrt(n)+2, &taillePremier);
	int i;
	uint64_t produit = 1;
	for(i=0; i<taillePremier && produit < n; i++)
	{
		if(n%tabPremier[i]==0)
		{
			renvoi[indice++]=tabPremier[i];
			produit *= tabPremier[i];
			n/=tabPremier[i];
			i--;
		}
	}
	if(indice==0 || n!= 1)
	{
		renvoi[indice++]=n;
	}
	*taille=indice;
	free(tabPremier);
	return renvoi;
}


void print_prime_factors(uint64_t nombre)
{
	int t=0;
	uint64_t * tab = factorisation(nombre, &t);
	int i;
	pthread_mutex_lock(&mutex);
	printf("%lld : ", nombre);
	for(i=0; i<t; i++)
	{
		printf(" %lld", tab[i]);
	}
	printf("\n");
	pthread_mutex_unlock(&mutex);
	free(tab);
}

void * run(void * param)
{
	uint64_t n;
	
	pthread_mutex_lock(&mutexScanf);
	while(fscanf(f, "%lld",&n) != EOF)
	{
		pthread_mutex_unlock(&mutexScanf);
		
		print_prime_factors(n);

		pthread_mutex_lock(&mutexScanf);
	}
	pthread_mutex_unlock(&mutexScanf);

	pthread_exit(NULL);
}



