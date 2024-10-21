#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>

int opt;

double m, c, j, i, t, aporte;
/*
	m = montante
	c = capital inicial
	i = taxa de juros (interest)
	t = tempo
	j = juros
*/

void clr_stdin(void){	// limpar a entrada de texto
    int q;		// evitar bugs ao escanear chars 
    do {
        q = getchar();
    } while (q != '\n' && q != EOF);
}

void print_menu(){
	system("@cls||clear"); //limpar a tela
	printf("===========================================\n"
		" INVESTICALC v2.0\n"
		"===========================================\n\n"
		"(1) Calcular juros simples\n"
		"(2) Calcular juros compostos\n"
		"(3) Calcular um investimento\n\n"
		
		"(4) Sair\n\n"
	);
	if(opt == 404){
		printf("Erro! Opção inválida.\n\n");
	}	
}

print_menu_calc(){
	char tipo[16] = "JUROS SIMPLES";
	
	system("@cls||clear"); //limpar a tela
	if (opt == 2){
		strcpy(tipo, "JUROS COMPOSTOS");
	} else if (opt == 3){
		strcpy(tipo, "INVESTIMENTO");
	}
	
	if (opt == 3){
	
		printf(	"===========================================\n"
			" %s\n"
			"===========================================\n\n", tipo);
	}
	else{
		printf(	"===========================================\n"
			" %s\n"
			"===========================================\n"
			" Digite 0 para indicar uma icógnita\n"
			"-------------------------------------------\n\n", tipo);
		
	}
}


void perguntas(){
	printf("Informe o capital inicial: ");
	scanf("%lf", &c);

	printf("Informe a taxa de juros (sem %%): ");
    scanf("%lf", &i);
    i /= 100;
	
	if (opt == 3){
		printf("Informe o aporte: ");
		scanf("%lf", &aporte);
	}

	printf("Informe o tempo do investimento: ");
	scanf("%lf", &t);
	
	if (opt != 3 && c == 0 || i == 0 || t == 0){
		printf("Informe o montante: ");
		scanf("%lf", &m);
	}
}

void print_res(){
	if (opt == 3){
		printf("\n\nMontante: R$ %.2f"
			"\nRendimento: R$ %.2f\n\n\n\n",
		   	m, j);
	}
	else{
		j = m - c;
		double parcela = m / t;

		printf("\n\nMontante: R$ %.2f"
		 	"\nJuros: R$ %.2f"
		  	"\nParcelas: R$ %.2f\n\n\n\n",
		   m, j, parcela);
	}

}

void calc_jur_simples(){
	if (c == 0){
		c = m/(i*t+1);
		printf("\n\nCapital inicial: R$ %.2f\n\n\n\n", c);
	} 
	else if (i == 0){
		i = ((m/c)-1)/t;
		printf("\n\nTaxa de juros: %.2f%%\n\n\n\n", i*100);
	} 
	else if (t == 0){
		t = ((m/c)+1)/i;
		printf("\n\nTempo de aplicação/parcelas: %.2f\n\n\n\n", t);
	}
	else{
		m = c * (1+i*t);
		print_res();
	}
}

void calc_jur_comp(){
	if (c == 0){
		c = m/pow((i+1), t);
		printf("\n\nCapital inicial: R$ %.2f\n\n\n\n", c);
	} 
	else if (i == 0){
		i = pow((m/c), (1/t))-1;
		printf("\n\nTaxa de juros: %.2f%%\n\n\n\n", i*100);
	} 
	else if (t == 0){
		t = log(m/c)/log(i+1);
		printf("\n\nTempo de aplicação/parcelas: %.2f\n\n\n\n", t);
	}
	else{
		m = c * pow((1+i), t);
		print_res();
	}
}

		

void calc_res(){
	if (opt == 1){ calc_jur_simples(); } 
	else if (opt == 2){ calc_jur_comp(); }
	else{
		// investimento com aporte
   		m = c*pow((1+i), t) + aporte*(pow((1+i), t)-1)/i;
		j = m - (c+aporte*t);
		
		print_res();
	}
}

void continuar(){
		char ch;
	
		clr_stdin();
		printf("\n\nRealizar outro calculo (s/n)? ");		
		scanf("%c%*[^\n]", &ch); // escaneia apenas a 1a letra
	
		if(ch == 'n' || ch == 'N'){
			opt = 7;
		}
}

int main(){
	setlocale(LC_ALL, "portuguese");

	while(opt != 4){
		print_menu();
		scanf("%d", &opt);
		
		switch(opt){
			case 1: case 2: case 3:
				while(opt != 7){
					print_menu_calc();
					perguntas();
					calc_res();
					
					continuar();
				} break;
			case 4:
				printf("Encerrando o programa...");
				break;
			default:
				if(opt != 404){ opt = 404; }
				break;
		}
	}
	return 0;
}
