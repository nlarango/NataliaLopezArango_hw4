#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
   //PARTE 1
	//AQUI PONGO TODAS LAS VARIABLES
	int i;
	int j;
	int a;
	//AQUI PONGO TODAS LAS CONSTANTES
	int t=100000.0; 
	int nx=129.0;
	float velpropagacion=250.0;
	double longitudcuerda= 0.64;
	double dx=0.005;
	double dt=(0.1*dx)/velpropagacion;
	double r=velpropagacion*dt/dx;
	int iteraciones=(1/dt)+1;
	//PERIODO ESTIMADO
	int periodo=(2*longitudcuerda)/velpropagacion;
	//AQUI PONGO LOS VECTORES USADOS
	double*x=malloc(nx*sizeof(double));
	double*y=malloc(nx*sizeof(double));
	double*y2=malloc(nx*sizeof(double));
	double*pres=malloc(nx*sizeof(double));
	double*fut=malloc(nx*sizeof(double));
	double*fut2=malloc(nx*sizeof(double));
	double*fut3=malloc(nx*sizeof(double));
	double*pas=malloc(nx*sizeof(double));
	//AQUI VA LA MATRIZ DONDE VAN LAS SOLUCIONES
	double ** matriz=malloc(iteraciones*sizeof(double*));
	//LAS MATRIZ DE SOLUCIONES
	for (i=0; i<iteraciones; i++)
	{
	matriz[i]=malloc(nx*sizeof(double));
	}
	//MATRIZ SOLUCION EN CEROS
	for(i=0; i<nx; i++)
	{
		for(j=0;j<iteraciones;j++)
		{
		matriz[j][i]=0.0;
		}
	}
	//AQUI LEO EL ARCHIVO DE CONDICIONES INICIALES
	FILE*datos=fopen("cond_ini_cuerda.dat","r");
	for (i=0;i<nx; i++)
	{
	fscanf(datos,"%lf %lf\n", &x[i],&y[i]);
	//printf("%lf\n" , x[i]);
	}
	//fclose(datos);
	FILE*datos2=fopen("datos.txt","w");
	//LAS CONDICIONES INICIALES
	for(a=0; a<nx; a++)
	{
	fscanf(datos,"%lf %lf\n", &x[a],&y[a]);
	}
// Vector de X
for(i=0;i<nx-1;i++)
{x[i] = i*dx;}
// Onda para t=0
for(i=1;i<nx-1;i++)
{matriz[0][i]=y[i]+(r*r/2.0)*(y[i+1]-2.0*y[i]+y[i-1]);}
 matriz[0][i]=y[0]+(r*r/2.0)*(y[1]-2.0*y[0]+y[nx-1]);
 matriz[0][nx-1]=y[nx-1]+(r*r/2.0)*(y[0]-2.0*y[nx-1]+y[nx-2]);
// Onda para t=T/8
copy(y,pas,nx);
int n_time=2;
for(j=1;j<n_time;j++){
  for(i=1;i<nx-1;i++)
  {fut[i] = (2.0*(1.0-r*r))*pres[i]-pas[i]+(r*r)*(pres[i+1]+pres[i-1]);}
   fut[0] = (2.0*(1.0-r*r))*pres[0]-pas[0]+(r*r)*(pres[1]+pres[nx-1]);
   fut[nx-1] = (2.0*(1.0-r*r))*pres[nx-1]-pas[nx-1]+(r*r)*(pres[0]+pres[nx-2]);
   copy(pres,pas,nx);
   copy(fut,pres,nx);
}
//n_time=2;
for(j=1;j<n_time;j++){
  for(i=1;i<nx-1;i++)
  {fut2[i] = (2.0*(1.0-r*r))*pres[i]-pas[i]+(r*r)*(pres[i+1]+pres[i-1]);}
   fut2[0] = (2.0*(1.0-r*r))*pres[0]-pas[0]+(r*r)*(pres[1]+pres[nx-1]);
   fut2[nx-1] = (2.0*(1.0-r*r))*pres[nx-1]-pas[nx-1]+(r*r)*(pres[0]+pres[nx-2]);
   copy(pres,pas,nx);
   copy(fut2,pres,nx);
}
for(j=1;j<n_time;j++){
  for(i=1;i<nx-1;i++)
  {fut3[i] = (2.0*(1.0-r*r))*pres[i]-pas[i]+(r*r)*(pres[i+1]+pres[i-1]);}
   fut3[0] = (2.0*(1.0-r*r))*pres[0]-pas[0]+(r*r)*(pres[1]+pres[nx-1]);
   fut3[nx-1] = (2.0*(1.0-r*r))*pres[nx-1]-pas[nx-1]+(r*r)*(pres[0]+pres[nx-2]);
   copy(pres,pas,nx);
   copy(fut3,pres,nx);
}

int n_time = periodo/8;
y2=y;
for(j=1;j<n_time;j++)
{
for(i=1;i<nx-1;i++)
{matriz[1][i]=(2.0*(1.0-r*r))*pres[i]-y2[i]+(r*r)*(pres[i+1]+pres[i-1]);}
 matriz[1][0]=(2.0*(1.0-r*r))*pres[0]-y2[0]+(r*r)*(pres[1]+pres[nx-1]);
 matriz[1][nx-1]=(2.0*(1.0-r*r))*pres[nx-1]-y2[nx-1]+(r*r)*(pres[0]+pres[nx-2]);
pres=y2;
fut=pres;
}
	for(j=0;j<nx;j++)
	{
	matriz[0][j]=y[j];
	
	}
	for(j=1;j<nx;j++)
	{
	matriz[1][j]=y[j]+(pow(r,2.0)/2.0)*(y[j+1]-2.0*y[j]+y[j-1]);
	}

//int n_time=periodo/4;
for(j=0;j<1;j++)
{first_iteration(matriz[0][j],y[j],iteraciones,r);}


int n_time=periodo/4; 
for(j=0;j<n_time;j++)
{
iteration(matriz[1][j],matriz[0][j],y[j],iteraciones,r);
}

        //AQUI HAGO LA SOLUCION PARA LA PRIMERA PARTE (AMBOS EXTREMOS FIJOS)
	for(i=0; i<nx -1;i++)
	{
	//x[i]=y[i]+pow(r,2)*0.5*(y[i+1]-2*y[i]+y[i-1]);
	x[i] = i*dx;
	}

	for (j=1; j<t; j++)
	{

		for(i=1;i<nx;i++)
		{
		
		//y2[i]=2*(1-pow(r,2))*x[i]-y[i]+pow(r,2)*(x[i+1]+x[i-1]);
		}
		//x[0]=sin((2*3.1415*velpropagacion/0.64)*(j*t));
		for(a=1; a<nx;a++)
		{
		//y[a]=x[a];
		//x[a]=y2[a];
		}
//matriz[1][j]=y[j];
		if (j==periodo/2|j==periodo/4|j==periodo/8)
		{
			for(i=0; i<nx ; i++)
			{
			//fprintf(datos2, "%f\n" , x[i]);
			}
			//fprintf(datos2, "\n");
		}
	}

//x[0]=0;
	//ARCHIVO CON LA SOLUCION DE LA PARTE 1
	for(i=0;i<nx;i++)
	{
	//fprintf(datos2,"%f %f\n",x[i],matriz[0][i]);
	//fprintf(datos2,"%f %f %f\n",x[i],matriz[0][i],fut[i]);
	fprintf(datos2,"%f %f %f %f %f\n",x[i],matriz[0][i],fut[i],fut2[i],fut3[i]);
	//fprintf(datos2, "%f %f %f %f %f\n",x[i], matriz[0][i],matriz[periodo/8][i],matriz[periodo/4][i], matriz[periodo/2][i]);
	}  
}
void copy(double*origen,double*destino,int n_puntos)
{
  int i;
  for(i=0;i<n_puntos;i++)
  {
   destino[i] = origen[i];
  }
}
 //PARTE 2

	//MATRIZ SOLUCION EN CEROS
	for(i=0; i<nx; i++)
	{
		for(j=0;j<iteraciones;j++)
		{
		matriz[j][i]=0.0;
		}
	}
	
	//EXTREMO FIJO
	for(j=1;j<iteraciones; j++)
	{
	matriz[j][0]=
	}

