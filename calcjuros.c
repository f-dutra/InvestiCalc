#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>

float c, m, j, i, n, p;
int opt;

void clrscr()
{
    system("@cls||clear");
}

void printMenu(){
	printf("===========================================\n"
		   "\tCalculadora Financeira\n"
		   "===========================================\n\n"
		   
		   "(1) Calcular juros simples\n"
		   "(2) Calcular Juros Compostos\n\n"
		   
		   "(3) Sair\n\n"
		   );
}

void perguntas(){
	printf("Informe o capital inicial: ");
	scanf("%f", &c);
	printf("Informe a taxa de juros (sem %%): ");
	scanf("%f", &i);
	printf("Informe o tempo/parcelas: ");
	scanf("%f", &n);
	if (c == 0 || i == 0 || n == 0){
		printf("Informe o montante: ");
		scanf("%f", &m);
	}
}

void printResult(){
	printf("\nMontante: R$ %.2f\n"
			"Juros: R$ %.2f\n"
			"Parcelas: R$ %.2f\n", m, j, p);
}

void funcSimples(){
	if (c == 0){
		c = m / ((i/100*n)+1);
		printf("Capital inicial: R$ %.2f", c);
	} else if(i == 0){
		i = ((m/c)-1)/n;
		printf("Taxa de juros: %.2f%%", i);
	} else if (n == 0){
		n = ((m/c)+1)/i/100;
		printf("Tempo de aplicação/parcelas: %.2f", n);
	} else {
		m = c*((i/100*n)+1);
		j = m - c;
		p = m / n;
		printResult();
	}
}

void funcComposto(){
	if (c == 0){
		c = m / pow((i/100*n), n);
		printf("Capital inicial: R$ %.2f", c);
	} else if(i == 0){
		i = pow((m/c), 1/n)-1;
		printf("Taxa de juros: %.2f%%", i);
	} else if (n == 0){
		n = log((m/c))/log((i/100+1));
		printf("Tempo de aplicação/parcelas: %.2f", n);
	} else {
		m = c*pow((i/100+1), n);
		j = m - c;			
		p = m / n;
	    printResult();
	}		
}

void continuar(){
	char controle;
	
	fflush(stdin);
			printf("\n\nRealizar outro cálculo (s/n)? ");
			scanf("%c", &controle);
			if (controle == 'n'){
				opt = 0;
			}
}



int main(){
	setlocale(LC_ALL, "Portuguese");
	while(opt != 3){
		printMenu();
		if(opt == 404){
			printf("Erro! Opção inválida.\n\n");
		}
		scanf(" %d", &opt);
		
		if(opt == 1){
		while (opt == 1){
			clrscr();
			printf(	"===========================================\n"
			   		"\tJuros Simples\n"
			   		"===========================================\n"
					" Digite 0 para indicar uma icógnita\n"
					"-------------------------------------------\n\n");
			perguntas();
			funcSimples();
			continuar();
			}
		} else if (opt == 2){
			while(opt == 2){
			clrscr();
			printf(	"===========================================\n"
		  	 		"\tJuros Compostos\n"
			   		"===========================================\n"
					" Digite 0 para indicar uma icógnita\n"
					"-------------------------------------------\n\n");
			perguntas();
			funcComposto();
			continuar();
			}
		} 
		else if (opt == 3){
			printf("Encerrando o programa...");
		} else{
			opt = 404;
		}
		clrscr();
	}
}
