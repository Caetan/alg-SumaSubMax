/**********************************************************************

Copyright (C) 2017  Álex Velo Santórum y Caetán Tojeiro Carpente

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/agpl-3.0.html>

**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


int sumaSubMax1(int v[], int n) {
	int sumaMax = 0;
	int i = 0;
	int j;
	int sumaActual = 0;
	
	for (i=0; i<n ; i++) {
		sumaActual = 0;
		for(j=i; j<n; j++){
			sumaActual = sumaActual + v[j];
			if (sumaActual > sumaMax){
				sumaMax = sumaActual;
			}
		}
	}
	return sumaMax;
}

int sumaSubMax2(int v[], int n) {
	int sumaActual = 0;
	int sumaMax = 0;
	int j;

	for (j = 0;j<n;j++){
		sumaActual = sumaActual + v[j];
		if(sumaActual>sumaMax){
			sumaMax=sumaActual;
		}else if(sumaActual<0){
			sumaActual=0;
		}
	}
	return sumaMax;
}

void listar_vector(int v[], int n) {
	int i = 0;
	printf("[ ");
	for(i=0; i<n; i++){
		printf("%i ", v[i]);
		
	}
	printf("]");
}

void test1(){
	int i, a, b;
	int v[][5] = {
		{-9,2,-5,-4,6},
		{4, 0, 9, 2, 5},
		{-2, -1, -9, -7, -1},
		{9, -2, 1, -7, -8},
		{15, -2, -5, -4, 16},
		{7, -5, 6, 7, -7},
		};
	printf("\n\ntest 1\n");
	printf("%25s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
	for(i=0;i<6;i++){
		listar_vector(v[i],5);
		a = sumaSubMax1(v[i],5);
		b = sumaSubMax2(v[i],5);
		printf("%20d%15d\n", a, b);
	}		
}		
		


void inicializar_semilla() {
	srand(time(NULL));
}


void aleatorio(int v [], int n) {
	int i, m=2*n+1;
	for (i=0; i < n; i++){
		v[i] = (rand() % m) - n;
	}
}

void test2(){
	int v[9];
	int i, a, b;

	printf("\n\ntest 2\n");
	printf("%30s%20s%20s\n", "", "sumaSubMax1", "sumaSubMax2");
	for(i=0;i<10;i++){
		aleatorio(v,9);
		listar_vector(v,9);
		a = sumaSubMax1(v,9);
		b = sumaSubMax2(v,9);
		printf("%20d%15d\n", a, b);
	}
}



double microsegundos(){
	struct timeval t;
	if(gettimeofday(&t, NULL) <0 ){
		return 0.0;
	}
	return (t.tv_usec + t.tv_sec * 1000000.0);
}


void pintarTablaA(int cont_a, int n, double t_a){

	if(cont_a == 1){
		printf("(*)");
		printf("%12i%15f%20f%20f%20f\n", n, t_a, t_a/(pow (n,1.8)), t_a/(pow (n,2)), t_a/(pow (n,2.2)));
	}else{
		printf("%15i%15f%20f%20f%20f\n", n, t_a, t_a/(pow (n,1.8)), t_a/(pow (n,2)), t_a/(pow (n,2.2)));	
	}	
	
}

void pintarTablaB(int cont_b, int n, double t_b){
        
	if(cont_b == 1){
		printf("(*)");
		printf("%12i%15f%20f%20f%20f\n", n, t_b, t_b/(pow (n,0.8)), t_b/n, t_b/(n*log(n)));
	}else{
		printf("%15i%15f%20f%20f%20f\n", n, t_b, t_b/(pow (n,0.8)), t_b/n, t_b/(n*log(n)));	
	}
}


void t_ejecucionA(int n){
	int v[n];
	int j = 0;
	int cont_a = 0;
	double t_ini_a, t_fin_a, t_a, t_a2;
	double t_a_aux = 0;

	aleatorio(v,n);
	t_ini_a = microsegundos();
	sumaSubMax1(v,n);
	t_fin_a = microsegundos();
	t_a = t_fin_a - t_ini_a;

	if(t_a<500){
		cont_a = 1;
		t_ini_a = microsegundos();
		for(j=0;j<100;j++){
			aleatorio(v,n);
			sumaSubMax1(v,n);
		}
		t_fin_a = microsegundos();
		t_a_aux = t_fin_a - t_ini_a;
		t_ini_a = microsegundos();
		for(j=0;j<100;j++){
			aleatorio(v,n);			
		}
		t_fin_a = microsegundos();
		t_a2 = t_fin_a - t_ini_a;
		t_a = (t_a_aux - t_a2) / 100;
	}

	pintarTablaA(cont_a, n, t_a);
}

void t_ejecucionB(int n){
	int v[n];
	int j = 0;
	int cont_b = 0;
	double t_ini_b, t_fin_b, t_b, t_b2;
	double t_b_aux = 0;

	aleatorio(v,n);
	t_ini_b = microsegundos();
	sumaSubMax2(v,n);
	t_fin_b = microsegundos();
	t_b = t_fin_b - t_ini_b;

	if(t_b<500){
		cont_b = 1;
		t_ini_b = microsegundos();
		for(j=0;j<10000;j++){
			aleatorio(v,n);
			sumaSubMax2(v,n);			
		}
		t_fin_b = microsegundos();
		t_b_aux = t_fin_b - t_ini_b;
		t_ini_b = microsegundos();
		for(j=0;j<10000;j++){
			aleatorio(v,n);			
		}
		t_fin_b = microsegundos();
		t_b2 = t_fin_b - t_ini_b;
		t_b = (t_b_aux - t_b2) / 10000;
	}
	pintarTablaB(cont_b, n, t_b);
}

int main(){
	
	test1();
	inicializar_semilla();
	test2();
	printf("\n%s\n", "sumaSubMax 1");
	printf("%15s%15s%20s%20s%20s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
	t_ejecucionA(500);
	t_ejecucionA(1000);
	t_ejecucionA(2000);
	t_ejecucionA(4000);
	t_ejecucionA(8000);
	t_ejecucionA(16000);
	t_ejecucionA(32000);

	printf("\n\n%s\n", "sumaSubMax 2");
	printf("%15s%15s%20s%20s%20s\n", "n", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/(n*log(n))");
	t_ejecucionB(500);
	t_ejecucionB(1000);
	t_ejecucionB(2000);
	t_ejecucionB(4000);
	t_ejecucionB(8000);
	t_ejecucionB(16000);
	t_ejecucionB(32000);

	return 0;
}


