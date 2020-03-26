#include <iostream>
#include <stdio.h>
using namespace std;

struct student
{
	int cod;
	char *nume;
	float medie;
};

struct nodLS //liste secundare
{
	student inf;
	nodLS *next;
};

struct hashT
{
	nodLS **vect;
	int size;
};

int functieHash(int cheie, hashT tabela)
{
	return cheie % tabela.size;
}

int inserare(hashT tabela, student s)
{
	int pozitie;
	if(tabela.vect!=NULL)
	{
		pozitie = functieHash(s.cod, tabela);
		nodLS *nou = (nodLS*)malloc(sizeof(nodLS));
		nou->inf.cod = s.cod;
		nou->inf.nume = (char*)malloc((strlen(s.nume)+1)*sizeof(char));
		strcpy(nou->inf.nume, s.nume);
		nou->inf.medie = s.medie;
		nou->next = NULL;
		if(tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else
		{
			nodLS* temp = tabela.vect[pozitie];
			while(temp->next)
				temp = temp->next;
			temp->next = nou;

		}
	}
	return pozitie;
}

void traversare(hashT tabela)
{
	if (tabela.vect!=NULL)
	{
		for(int i=0;i<tabela.size;i++)
			if(tabela.vect[i]!=NULL)
			{
				printf("\nPozitie = %d", i);
				nodLS *temp = tabela.vect[i];
				while(temp)
				{
					printf("\nCod=%d, Nume=%s, Medie=%5.2f", temp->inf.cod, temp->inf.nume, temp->inf.medie);
					temp = temp->next;
				}
			}
	}
}

void main()
{
	hashT tabela;
	tabela.size = 101;
	tabela.vect = (nodLS**)malloc(tabela.size*sizeof(nodLS*));
	for(int i=0;i<tabela.size;i++)
		tabela.vect[i] = NULL;

	int n;
	student s;
	printf("Nr. studenti=");
	scanf("%d", &n);
	char buffer[20];

	for(int i=0;i<n;i++)
	{
		printf("\nCod=");
		scanf("%d", &s.cod);
		printf("\nNume=");
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer)+1)*sizeof(char));
		strcpy(s.nume, buffer);
		printf("\nMedie=");
		scanf("%f", &s.medie);

		inserare(tabela, s);
	}
	traversare(tabela);
}
