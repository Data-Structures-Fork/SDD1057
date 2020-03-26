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
	nodLS *next, *prev;
};

struct nodLP //lista principala
{
	nodLS *inf;
	nodLP *next;
};

nodLS* inserareLS(nodLS *cap, student s)
{
	nodLS *nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume)+1)*sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	nou->next = NULL;
	nou->prev = NULL;
	if(cap==NULL)
		cap = nou;
	else
	{
		nodLS *temp = cap;
		while(temp->next)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
	}
	return cap;
}

void inserareLP(nodLP**capLP, nodLS *capLS)
{
	nodLP *nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next = NULL;
	if(*capLP==NULL)
		*capLP = nou;
	else
	{
		nodLP* temp = *capLP;
		while(temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void traversareLS(nodLS *cap)
{
	nodLS* temp = cap;
	while(temp)
	{
		printf("\nCod=%d, Nume=%s, Medie=%5.2f", temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void traversareLP(nodLP* cap)
{
	nodLP*temp = cap;
	while(temp)
	{
		printf("\nSublista: ");
		traversareLS(temp->inf);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS *cap)
{
	nodLS* temp = cap;
	while(temp)
	{
		nodLS *temp2 = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP *cap)
{
	nodLP*temp = cap;
	while(temp)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		temp = temp2;
	}
}

void main()
{
	int n;
	student s;
	printf("Nr. studenti=");
	scanf("%d", &n);

	char buffer[20];

	nodLP *capLP =NULL;
	nodLS *capLSpar = NULL, *capLSimpar = NULL;

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

		if(s.cod % 2 == 0)
			capLSpar = inserareLS(capLSpar, s);
		else
			capLSimpar = inserareLS(capLSimpar, s);
	}
	inserareLP(&capLP, capLSpar);
	inserareLP(&capLP, capLSimpar);

	traversareLP(capLP);
	dezalocareLP(capLP);
}
