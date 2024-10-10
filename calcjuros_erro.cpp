#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

float capital, montante, juros, taxa, tempo, parcelas;
int opt, subopt;
char aux[6], tax1[6], tax2[6] = " ";

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
		   "(2) Calcular Juros Compostos\n"
		   "(3) Converter taxas\n\n"

		   "(4) Sair\n\n"
		   );

	if(opt == 404){
		printf("Erro! Opção inválida.\n\n");
	}
}

void print_calc(){
	clrscr();
	char tipo[10] = "Simples";
	if (opt == 2){
		strcpy(tipo, "Compostos");
	}
	printf(	"===========================================\n"
		"\t\tJuros %s\n"
		"===========================================\n"
		" Digite 0 para indicar uma icógnita\n"
		"-------------------------------------------\n\n", tipo);

}

void print_menu_taxa(){
	clrscr();
	printf("===========================================\n"
		   "\tConverter taxas\n"
		   "===========================================\n"
		   " Convertendo de (%s) para (%s)"
		   "-------------------------------------------\n\n"

		   "(1) Diária\t\t		(4)Semanal\n"
		   "(2) Mensal\t\t		(5)Trimestral\n"	
		   "(3) Anual\t\t		(6)Semestral)\n\n"	

		   "(7) Sair\n\n", tax1, tax2
		   );
	}

void texto_taxa(){
	switch(opt){
		case 1:
			strcpy(aux, "a.d.");
			break;
		case 2:
			strcpy(aux, "a.m.");
			break;
		case 3:
			strcpy(aux, "a.a.");
			break;
		case 4:
			strcpy(aux, "a.sm.");
			break;
		case 5:
			strcpy(aux, "a.t.");
			break;
		case 6: 
			strcpy(aux, "a.a.");
			break;
	}
}

void perguntas(){
	printf("Informe o capital inicial: ");
	scanf("%f", &capital);
	printf("Informe a taxa de juros (sem %%): ");
	scanf("%f", &taxa);
	taxa = taxa / 100;
	printf("Informe o tempo/parcelas: ");
	scanf("%f", &tempo);
	if (capital == 0 || taxa == 0 || tempo == 0){
		printf("Informe o montante: ");
		scanf("%f", &montante);
	}
}

void print_result(){
	printf("\nMontante: R$ %.2f\n"
			"Juros: R$ %.2f\n"
			"Parcelas: R$ %.2f\n", montante, juros, parcelas);
}

void func_simples(){
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
		print_result();
	}
}

void func_composto(){
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
	    	print_result();
	}
}

void continuar(){
	char c;

	limpar_buffer();
			printf("\n\nRealizar outro cálculo (s/n)? ");
			scanf("%c", &c);
			if (c == 'n'){
				opt = 0;
			}
}



int main(){
	setlocale(LC_ALL, "Portuguese");
	while(opt != 4){
		print_menu();
		scanf(" %d", &opt);

		switch(opt){
		case 1: case 2:
			while (opt != 0){
				clrscr();
				print_calc();
				perguntas();

				if (opt == 1){func_simples();}
				else{func_composto();}
				continuar();
			}
			break;
			
		case 3:
			while (opt != 7){
				print_menu_taxa();
				scanf("%d" &opt);
				texto_tax();
				strcpy(tax1, aux);
				print_menu(taxa);
				scanf("%d", &opt);
				texto_tax();
				strcpy(tax2, aux);
				print_menu_taxa();
		}
			
		
		case 4:
			printf("Encerrando o programa...");
			break;
		default:
			opt = 404;
			break;
		}
	}
}

