#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

uint64_t * nombresPremiers(uint64_t n, int * taille);
uint64_t * factorisation(uint64_t n, int * taille);
void print_prime_factors(uint64_t n);

int main()
{
	FILE * f;
	if((f=fopen("numbers.txt","r")) != NULL)
	{
		uint64_t n;
		while(fscanf(f, "%lld",&n) != EOF)
		{
			print_prime_factors(n);
			printf("\n");
		}
		fclose(f);
	}
	
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

void print_prime_factors(uint64_t n)
{
	int t=0;
	uint64_t * tab = factorisation(n, &t);
	int i;
	printf("%lld : ", n);
	for(i=0; i<t; i++)
	{
		printf(" %lld", tab[i]);
	}
	free(tab);
}

