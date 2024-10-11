#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <limits.h>

long double capital, montante, juros, taxa, tempo, parcelas, aporte;
int opt, subopt;
char aux[6], txt1[6] = " ", txt2[6] = " ";

void clrscr()
{
    system("@cls||clear");
}

void limpar_buffer(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void print_menu(){
	clrscr();
	printf("===========================================\n"
		   "\tCalculadora Financeira\n"
		   "===========================================\n\n"

		   "(1) Calcular juros simples\n"
		   "(2) Calcular juros compostos\n"
		   "(3) Calcular um Investimento\n\n"

		   "(4) Sair\n\n"
		   );

	if(opt == 404){
		printf("Erro! Opção inválida.\n\n");
	}
}

void print_menu_juros(){
	clrscr();
	char tipo[16] = "Juros Simples";
	if (opt == 2){
		strcpy(tipo, "Juros Compostos");
	} else if (opt == 3){
		strcpy(tipo, "Investimento");
	}
	printf(	"===========================================\n"
		"\t\t%s\n"
		"===========================================\n"
		" Digite 0 para indicar uma icógnita\n"
		"-------------------------------------------\n\n", tipo);
}

void perguntas(){
	printf("Informe o capital inicial: ");
	scanf("%f", &capital);

	printf("Informe a taxa de juros (sem %%): ");
	scanf("%f", &taxa);
	taxa = taxa / 100;

	printf("Informe o tempo/parcelas: ");
	scanf("%f", &tempo);
	
	if (opt == 3){
		printf("Informe o aporte: ");
		scanf("%f", &aporte);
	}

	if (capital == 0 || taxa == 0 || tempo == 0){
		printf("Informe o montante: ");
		scanf("%f", &montante);
	}
}

void func_simples(){

	if (capital == 0){
		capital = montante / ((taxa*tempo)+1);
		printf("Capital inicial: R$ %.2f\n", capital);
	} else if(taxa == 0){
		taxa = ((montante/capital)-1)/tempo;
		printf("Taxa de juros: %.2f%%\n", taxa*100);
	} else if (tempo == 0){
		tempo = ((montante/capital)+1)/taxa;
		printf("Tempo de aplicação/parcelas: %.2f\n", tempo);
	} else {
		montante = capital*((taxa*tempo)+1);
		juros = montante - capital;
		parcelas = montante / tempo;

		printf("\nMontante: R$ %.2f\n"
		"Juros: R$ %.2f\n"
		"Parcelas: R$ %.2f\n", montante, juros, parcelas);
	}
}

void func_composto(){
	if (capital == 0){
		capital = montante / pow((taxa+1), tempo);
		printf("Capital inicial: R$ %.2f\n", capital);
	} else if(taxa == 0){
		taxa = pow((montante/capital), 1/tempo)-1;
		printf("Taxa de juros: %.2f%%\n", taxa*100);
	} else if (tempo == 0){
		tempo = log((montante/capital))/log((taxa/+1));
		printf("Tempo de aplicação/parcelas: %.2f\n", tempo);
	} else {
		montante = capital*pow((taxa+1), tempo);
		juros = montante - capital;
		parcelas = montante / tempo;

		printf("\nMontante: R$ %.2f\n"
		"Juros: R$ %.2f\n"
		"Parcelas: R$ %.2f\n", montante, juros, parcelas);
	}
}

void func_investimento(){
	if (capital == 0){
		capital = montante / pow((taxa+1), tempo) + aporte * pow((taxa+1), tempo);
		printf("Capital inicial: R$ %.2f\n", capital);
	} else if(taxa == 0){
		taxa = pow((montante/capital+aporte), 1/tempo)-1;
		printf("Taxa de juros: %.2f%%\n", taxa*100);
	} else if (tempo == 0){
		tempo = log((montante/capital+aporte))/log((taxa/+1));
		printf("Tempo de aplicação/parcelas: %.2f\n", tempo);
	} else {
		montante = capital * pow((taxa+1), tempo) + aporte * pow((taxa+1), tempo);
		juros = montante - capital;

		printf("\nMontante: R$ %.2f\n"
		"Rendimento: R$ %.2f\n"
		, montante, juros);
	}
}

void continuar(){
	char c;

	limpar_buffer();
			printf("\n\nRealizar outro cálculo (s/n)? ");
			scanf("%c", &c);
			if (c == 'n'){
				opt = 7;
			}
}

int main(){
	setlocale(LC_ALL, "portuguese");
	while(opt != 4){
		print_menu();
		scanf(" %d", &opt);

		switch(opt){
		case 1: case 2: case 3:
		while (opt != 7){
			print_menu_juros();
			perguntas();

			if (opt == 1){func_simples();}
			else if (opt == 2){func_composto();}
			else{func_investimento();}

			continuar();
			}
			break;
		case 4:
			printf("Encerrando o programa...");
			break;
		default:
			opt = 404;
			break;
		}
	}
}

