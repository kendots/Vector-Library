#ifndef VECTORS_H
#define VECTORS_H

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include"Kmath.h"

typedef struct
{
	int n;
	double * t;
}vector;

vector vnull={0,NULL};


void   VectInit (vector *);
void   VectFree (vector *);
vector Vect (int , ...);
void   VectGet (int , vector * );
void   VectPrint (vector v);
void   VectAdd (vector, vector, vector *);


void VectInit (vector * v)
{
	if (v->t)
	{
		puts("Error: The pointer was allocated!!");
		free(v->t);
	}

	v->t=calloc(v->n,sizeof(double));
}


void VectFree (vector * v)
{
	if (v->t)
	{
		free(v->t);
		v->t=NULL;
		v->n=0;
	}
}


vector Vect (int n, ...)
{
	va_list valist;
	int i;
	vector v={n,NULL};
	VectInit(&v);
	va_start(valist, n);
	for (i=0; i<n; i++)
		v.t[i]=(double) va_arg(valist, double);
	va_end(valist);
	return v;
}


void VectGet (int n, vector * v)
{
	int i;
	if (v->t==NULL)
	{
		v->n=n;
		v->t=calloc(v->n,sizeof(double));
	}

	for (i=0; i<n; i++)
		scanf("%lf",&v->t[i]);
}


vector VectZero(int n)
{
	int i;
	vector v={n,NULL};
	VectInit(&v);
	for (i=0; i<n; i++)
		v.t[i]=0;
}


void VectPrint (vector v)
{
	int i;
	for (i=0; i<v.n; i++)
		printf("%g \t",v.t[i]);
	puts("");
}


void VectAdd (vector v, vector w, vector * r)
{
	int i;
	if (r->t==NULL)
	{
		r->n=v.n;
		r->t=calloc(v.n,sizeof(double));
	}

	for (i=0; i<v.n; i++)
		r->t[i]=v.t[i]+w.t[i];
}


void VectCpy (vector v, vector r)
{
	int i;
	for (i=0; i<v.n; i++)
		v.t[i]=r.t[i];
}


void VectSub(Fun func, vector x, vector y)
{
	int i;
	for (i=0; i<x.n; i++)
		y.t[i]=func(x.t[i]);
}


vector VectRand(int n, int x)
{
	int i;
	vector v={n,NULL};
	for (i=0; i<v.n; i++)
		v.t[i]=rand()%x;
	return v;
}

double Dot (vector v, vector r)
{
	int i;
	double s=0;
	for (i=0; i<v.n; i++)
		s+=v.t[i]*r.t[i];
	return s;
}


void Cross (vector v, vector r, vector * s)
{
	int i;
	double * t=malloc(3*sizeof(double));
	t[0]=v.t[1]*r.t[2]-v.t[2]*r.t[1];
	t[1]=v.t[2]*r.t[0]-v.t[0]*r.t[2];
	t[2]=v.t[0]*r.t[1]-v.t[1]*r.t[0];
	for (i=0; i<=2; i++)
		s->t[i]=t[i];
	free(t);
}

//A^X=B
void CrossInv (vector A, vector B, vector * X)
{
	double x;
	vector temp={3,NULL};
	VectInit(&temp);
	x=Dot(A,A);
	int i;
	for (i=0; i<=2; i++)
		temp.t[i]=-A.t[i]/x;
	Cross(temp,B,X);
	free(temp.t);
}


vector Seq(double x, double it, double y)
{
	double i,z;
	int k;
	z=(y-x)/it;
	k=(int) z+1;
	vector v={k,NULL};
	VectInit(&v);
	k=0;
	for (i=x; i<=y; i+=it)
		v.t[k++]=i;
	return v;
}

vector linspace (double a, double b, int n)
{
	if (n<2) 
		return VectZero(1);
	int i,m=n-1;
	double h,x=a;
	vector v={n,NULL};
	VectInit(&v);
	
	h=(b-a)/m;
	for (i=0; i<n; i++)
	{
		x+=h;
		v.t[i]=x;
	}
	return v;
}


#endif 
