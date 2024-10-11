#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

float capital, montante, juros, taxa, tempo, parcelas;
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
		   "(3) Converter taxas\n\n"

		   "(4) Sair\n\n"
		   );

	if(opt == 404){
		printf("Erro! Opção inválida.\n\n");
	}
}

void print_menu_juros(){
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

void print_menu_taxa(){
	clrscr();
	printf("===========================================\n"
		   "\tConverter taxas\n"
		   "===========================================\n"
		   " Convertendo de (%s) para (%s)\n"
		   "-------------------------------------------\n\n"

		   "(1) Diária\t\t(4) Semanal\n"
		   "(2) Mensal\t\t(5) Trimestral\n"
		   "(3) Anual\t\t(6) Semestral\n\n"

		   "(7) Voltar\n\n", txt1, txt2
		   );

	if(opt == 404){
		printf("Erro! Opção inválida.\n\n");
	}

}

void texto_taxa(int *o){
	switch(*o){
		case 1: strcpy(aux, "a.d."); break;
		case 2: strcpy(aux, "a.m."); break;
		case 3: strcpy(aux, "a.a."); break;
		case 4: strcpy(aux, "a.sm."); break;
		case 5:	strcpy(aux, "a.t."); break;
		case 6: strcpy(aux, "a.a."); break;
		case 7: break;
		// default: *o = 404; break;  ## Não funciona no momento ##
	}
}

int menu_taxa(int o){
	while(o != 7){
		print_menu_taxa(o);
		scanf("%d", &o);
		texto_taxa(&o);
		if(o == 404){continue;}
		else{
			return o;
		}
	}
}

void convert_mensal(){
	switch(opt){
		case 1: taxa *= 30; break;
		case 2: break;
		case 3: taxa /= 12; break;
		case 4: taxa *= 4.28; break;
		case 5: taxa /= 3; break;
		case 6: taxa /= 6; break;
		case 7: break;
	}
	printf("Taxa convertida: %.2f%% a.m.", taxa);

}

void calc_taxa(){
	printf("Informe a taxa: ");
	scanf("%f", &taxa);
	printf("Taxa convertida: %.2f%% %s", taxa, txt1);

	convert_mensal();
	switch(subopt){
		case 1: taxa /= 30; break;
		case 2: break;
		case 3: taxa *= 12; break;
		case 4: taxa /= 4.28; break;
		case 5: taxa *= 3; break;
		case 6: taxa *= 6; break;
		case 7: break;
	}
	printf("Taxa convertida: %.2f%% %s", taxa, txt2);
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
		case 1: case 2:
		while (opt != 7){
			print_menu_juros();
			perguntas();

			if (opt == 1){func_simples();}
			else{func_composto();}

			continuar();
			}
			break;
		case 3:
		while(opt != 7){
			opt = menu_taxa(opt);
			if (opt == 7){break;}
			strcpy(txt1, aux);

			subopt = menu_taxa(subopt);
			if (subopt == 7){
				subopt = 0;
				strcpy(txt1, " ");
				continue;
			}
			strcpy(txt2, aux);
			print_menu_taxa();

			calc_taxa();

			continuar();
			strcpy(txt1, " ");
			strcpy(txt2, " ");
		} break;
		case 4:
			printf("Encerrando o programa...");
			break;
		default:
			opt = 404;
			break;
		}
	}
}

