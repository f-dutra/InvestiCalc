#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <locale.h>

mpf_t m, c, r, i, a, aux, acpy, ccpy;
int t;

void clr_stdin(void){
    int q;
    do {
        q = getchar();
    } while (q != '\n' && q != EOF);
}

void print_menu(){
	system("@cls||clear");
	printf(" ===========================================\n"
		" \tInvestiCalc v1.1\n"
		" ===========================================\n\n"
	);
}

void perguntas(){
	printf(" Informe o capital inicial: ");
	gmp_scanf("%Ff", c);

	printf(" Informe a taxa de juros (sem %%): ");
	gmp_scanf("%Ff", i);
	mpf_div_ui(i, i, 100);

	printf(" Informe o aporte: ");
	gmp_scanf("%Ff", a);

	printf(" Informe o tempo do investimento: ");
	scanf("%d", &t);
}

void calc_invest(){
	// Formula: m = c(1 + i)^t + a(((1+i)^t)/i)

	mpf_set(acpy, a); // usadas pra calcular o rendimento
	mpf_set(ccpy, c);

	mpf_add_ui(aux, i, 1); 		// primeira parte da formula
	mpf_pow_ui(aux, aux, t);	// c(1+i)^t
	mpf_mul(c, c, aux);

	mpf_sub_ui(aux, aux, 1); 	// segunda parte da formula
	mpf_div(aux, aux, i);		//  a(((1+i)^t)-1)/i
	mpf_mul(a, a, aux);

	mpf_add(m, a, c); // resultado final

	mpf_mul_ui(acpy, acpy, t); //calculo do rendimento
	mpf_sub(r, m, ccpy);
	mpf_sub(r, r, acpy);	// r = m - (c + a * t)
}

void print_res(){
	gmp_printf("\n\n Montante: R$ %.2Ff\n"
		   " Rendimento: R$ %.2Ff\n\n\n\n",
		   m, r);
}

int main(){
	setlocale(LC_ALL, "portuguese");
	mpf_inits(m, c, r, i, a, aux, acpy, ccpy, NULL);
	char ch;

	while(ch != 'n' && ch != 'N'){
		print_menu();
		perguntas();
		calc_invest();
		print_res();

		clr_stdin();
		printf("\n\n Realizar outro calculo (s/n)? ");
		scanf("%c", &ch);
	}

	mpf_clears(m, c, r, i, a, aux, acpy, ccpy, NULL);
	return 0;
}

