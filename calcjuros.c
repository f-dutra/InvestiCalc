#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

float capital, montante, juros, taxa, tempo, parcelas;
int opt;

void clrscr()
{
    system("@cls||clear");
}

void limpar(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void printMenu(){
	clrscr();
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
	scanf("%f", &capital);
	printf("Informe a taxa de juros (sem %%): ");
	scanf("%f", &taxa);
	printf("Informe o tempo/parcelas: ");
	scanf("%f", &tempo);
	if (capital == 0 || taxa == 0 || tempo == 0){
		printf("Informe o montante: ");
		scanf("%f", &montante);
	}
}

void printResult(){
	printf("\nMontante: R$ %.2f\n"
			"Juros: R$ %.2f\n"
			"Parcelas: R$ %.2f\n", montante, juros, parcelas);
}

void funcSimples(){
	if (capital == 0){
		capital = montante / ((taxa*tempo)+1);
		printf("Capital inicial: R$ %.2f", capital);
	} else if(taxa == 0){
		taxa = ((montante/capital)-1)/tempo;
		printf("Taxa de juros: %.2f%%", taxa*100);
	} else if (tempo == 0){
		tempo = ((montante/capital)+1)/taxa;
		printf("Tempo de aplicação/parcelas: %.2f", tempo);
	} else {
		montante = capital*((taxa*tempo)+1);
		juros = montante - capital;
		parcelas = montante / tempo;
		printResult();
	}
}

void funcComposto(){
	if (capital == 0){
		capital = montante / pow((taxa+1), tempo);
		printf("Capital inicial: R$ %.2f", capital);
	} else if(taxa == 0){
		taxa = pow((montante/capital), 1/tempo)-1;
		printf("Taxa de juros: %.2f%%", taxa*100);
	} else if (tempo == 0){
		tempo = log((montante/capital))/log((taxa/+1));
		printf("Tempo de aplicação/parcelas: %.2f", tempo);
	} else {
		montante = capital*pow((taxa+1), tempo);
		juros = montante - capital;
		parcelas = montante / tempo;
	    printResult();
	}
}

void continuar(){
	char controle;

	limpar();
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
			taxa = taxa / 100;
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
			taxa = taxa / 100;
			funcComposto();
			continuar();
			}
		}
		else if (opt == 3){
			printf("Encerrando o programa...");
		} else{
			opt = 404;
		}
	}
}

