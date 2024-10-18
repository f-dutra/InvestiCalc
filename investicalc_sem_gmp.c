#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

double m, c, r, i, a;
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
	scanf("%lf", &c);

	printf(" Informe a taxa de juros (sem %%): ");
    scanf("%lf", &i);
    i /= 100;

	printf(" Informe o aporte: ");
	scanf("%lf", &a);

	printf(" Informe o tempo do investimento: ");
	scanf("%d", &t);
}

void calc_invest(){
    m = c*pow((1+i), t) + a*(pow((1+i), t)-1)/i;
	r = m - (c+a*t);
}

void print_res(){
	printf("\n\n Montante: R$ %.2f\n"
		   " Rendimento: R$ %.2f\n\n\n\n",
		   m, r);
}

int main(){
	setlocale(LC_ALL, "portuguese");
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
	return 0;
}

