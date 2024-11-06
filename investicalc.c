#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>

int opt, cntrl;
double m, c, x, i, j, t, aporte;
/*
	m = montante		c = capital inicial	
	i = taxa de juros 	j = juro
	t = tempo
*/
void limpar_tela(){
		system("@cls||clear"); 
}

void limpar_entrada(void){	// limpar o buffer de entrada
    int q;				// evitar que o scanf capture lixo 
    do {
        q = getchar();
    } while (q != '\n' && q != EOF);
}

void print_menu(){
	limpar_tela();
	printf("===========================================\n"
		" INVESTICALC v2.2\n"
		"===========================================\n\n"
		"(1) Calcular investimento\n"
		"(2) Calcular juros simples\n"
		"(3) Calcular juros compostos\n\n"
		
		"(4) Sair\n\n"
	);
	if(opt == 404){
		printf("Erro! Opção inválida.\n\n");
	}	
}

print_menu_calc(){
	char tipo[16] = "INVESTIMENTO";

	limpar_tela();	
	if (opt == 2){
		strcpy(tipo, "JUROS SIMPLES");
	} else if (opt == 3){
		strcpy(tipo, "JUROS COMPOSTOS");
	}
	
	if (opt == 1){
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

void print_res(){
	if (cntrl == 1){
		printf("Valor da icógnita: %.2f", x);
	} 
	else if (opt == 1){
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

void perguntas(){
	printf("Informe o capital inicial: ");
	scanf("%lf", &c);

	printf("Informe a taxa de juros (sem %%): ");
    scanf("%lf", &i);
    i /= 100;
	
	if (opt == 1){
		printf("Informe o aporte: ");
		scanf("%lf", &aporte);
	}

	printf("Informe o tempo do investimento: ");
	scanf("%lf", &t);
	
	if (opt != 1 && c == 0 || i == 0 || t == 0){
		printf("Informe o montante: ");
		scanf("%lf", &m);
		cntrl = 1; // indica para a função print_res() que o resultado é uma icógnita
	} else {cntrl = 0;};
}

void calc_jur_simples(){
	if (c == 0){
		x = m / (i * t + 1);
	} 
	else if (i == 0){
		x = ((m / c) - 1)/t;
	} 
	else if (t == 0){
		x = ((m / c) + 1) / i;
	}
	else{
		m = c * (1 + i * t);
	}
}

void calc_jur_comp(){
	if (c == 0){
		x = m / pow((i + 1), t);
	} 
	else if (i == 0){
		x = pow((m / c), (1 / t)) - 1;
	} 
	else if (t == 0){
		x = log(m / c) / log(i + 1);
	}
	else{
		m = c * pow((1 + i), t);
	}
}

		

void calc_res(){
	if (opt == 2){ calc_jur_simples(); } 
	else if (opt == 3){ calc_jur_comp(); }
	else{
		//investimento com aporte
   		m = c * pow((1 + i), t) + aporte*(pow((1 + i), t) - 1)/i;
		j = m - (c + aporte * t);
	}
}

void continuar(){
		char ch;

		limpar_entrada();
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
		limpar_entrada(); // captura valores não-inteiros (float, char)
						  // impede um bug que causava um loop infinito do menu
		switch(opt){
			case 1: case 2: case 3:
				while(opt != 7){
					print_menu_calc();
					perguntas();
					calc_res();
					print_res();
					
					continuar();
				}
				break;
			case 4:
				printf("Encerrando...");
				break;
			default:
				if(opt != 404){ opt = 404; }
				break;
			}
	}
	return 0;
}
