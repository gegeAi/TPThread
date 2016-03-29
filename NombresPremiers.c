#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int * nombresPremiers(int n, int * taille);
int * factorisation(int n, int * taille);
void print_prime_factors(int n);

int main()
{
	print_prime_factors(4938);
	return 0;
}

int * nombresPremiers(int n, int * taille)
{
	int i;
	int * renvoi = (int *) malloc(sizeof(int)*n);
	int indice = 0; 
	for(i=2; i<=n; i++)
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

int * factorisation(int n, int * taille)
{
	int * renvoi = (int *) malloc(sizeof(int)*((int)(n/3)));
	int indice = 0;
	int taillePremier=0;
	int * tabPremier = nombresPremiers(n, &taillePremier);
	int i;
	for(i=0; i*i<taillePremier; i++)
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
	return renvoi;
}

void print_prime_factors(int n)
{
	int t=0;
	int * tab = factorisation(n, &t);
	int i;
	printf("%d : ", n);
	for(i=0; i<t; i++)
	{
		printf(" %d", tab[i]);
	}
}



