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
	int indice = 1; 
	renvoi[0]=2;
	for(i=3; i<=n; i+=2)
	{
		int j;
		short premier=1;
		for(j=i-1; j>1; j--)
		{
			if(i%j==0)
			{
				premier=0;
			}
		}

		if(premier==1)
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
	for(i=0; i<taillePremier; i++)
	{
		if(n%tabPremier[i]==0)
		{
			renvoi[indice++]=tabPremier[i];
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
	printf("%d : ", n);
	for(i=0; i<t; i++)
	{
		printf(" %d", tab[i]);
	}
	free(tab);
}



