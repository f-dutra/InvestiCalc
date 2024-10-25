programa
{
  inclua biblioteca Matematica --> mat

	inteiro opt = 0, cntrl = 0
	real m, c, i, t, x, aporte = 0.0

  /*
    m = montante          t = tempo
    c = capital inicial   i = taxa de juros (interest)
  */

	funcao print_menu(){		
      limpa()

			escreva("===========================================\n")
			escreva(" INVESTICALC v2.2\n")
			escreva("===========================================\n\n")
			escreva("(1) Calcular investimento\n")
			escreva("(2) Calcular juros simples\n")
			escreva("(3) Calcular juros compostos\n\n")
		
			escreva("(4) Sair\n\n")

			se(opt == 404){
					escreva("Erro! opção inválida")
				}
					
	}

	funcao print_menu_calc(){
    limpa()

		cadeia txt = "INVESTIMENTO"
		se(opt == 2){txt = "JUROS SIMPLES"}
		senao se (opt == 3){txt = "JUROS COMPOSTOS"}

		se(opt == 1){
				escreva("===========================================\n")
				escreva(" " + txt + "\n")
				escreva("===========================================\n\n")
			} senao{
				escreva("===========================================\n")
				escreva(" " + txt + "\n")
				escreva("===========================================\n")
				escreva(" Digite 0 pra indicar uma variável\n")
				escreva("-------------------------------------------\n\n")
			}
	}

	funcao perguntas(){
		escreva("Informe o capital inicial: ")
		leia(c)

		escreva("Informe a taxa de juros: ")
		leia(i)
		i /= 100

		escreva("Informe o tempo da aplicação: ")
		leia(t)

		se(opt == 1){
			escreva("Informe o aporte: ")
			leia(aporte)
		} 
		se(opt != 1 e c == 0 ou i == 0 ou t == 0){
			escreva("Informe o montante: ")
			leia(m)
			cntrl = 1 // indica à função print_res() que o resultado é uma icógnita
		} 
		senao{cntrl = 0}
		
	}

	funcao print_res(){
		real j, p
    se(cntrl == 1){
      x = mat.arredondar(x, 2)
      escreva("Valor da icógnita: " + x)
    } senao{
		  se(opt == 1){
        j = m - (c + aporte * t)
      }
	  	senao{j = m - c}

      m = mat.arredondar(m, 2)
      j = mat.arredondar(j, 2)

	  	escreva("\n\nMontante: R$" + m)
	  	escreva("\nRendimento: R$" + j)
	  	se(opt != 1){
		  	p = m / t
        p = mat.arredondar(p, 2)

		  	escreva("\nParcelas: R$"+ p)
		  }
    }
	}

	funcao calc_simples(){
		se(c == 0){
			x = m / (i * t + 1)
		} 
		senao se (i == 0){
			x = ((m / c) - 1) / t	
      x *= 100
		} 
		senao se (t == 0){
			x = ((m / c) - 1) / i
		} 
		senao{
			m = c * (i * t + 1)	
		} 
	}

	funcao calc_composto(){
		se(c == 0){
			x = m / mat.potencia(i + 1, t)
		} 
		senao se (i == 0){  
			x = mat.raiz((m / c), t) - 1
      x *= 100
		} 
		senao se (t == 0){
      real eu = 2.71828
			x = mat.logaritmo((m / c), eu) / mat.logaritmo((i + 1), eu)
		} 
		senao{
			m = c * mat.potencia((i + 1), t)	
		} 
	}

	funcao calc_res(){
		se(opt == 2) {calc_simples()}
		senao se (opt == 3) {calc_composto()}
		senao{
			m = c * mat.potencia((i + 1), t)	+ (aporte * (mat.potencia((i + 1), t) - 1) / i)
		}
	}

	funcao continuar(){
		caracter ch
		escreva("\n\n\n\n\nDeseja continuar (s/n)? ")
		leia(ch)

		se(ch == 'n' ou ch == 'N'){opt = 7}
	}
	
	funcao inicio()
	{
		enquanto(opt != 4){
			print_menu()
			leia(opt)

			escolha(opt){
					caso 1:caso 2:caso 3:
						enquanto(opt != 7){
							print_menu_calc()
							perguntas()
							calc_res()
              print_res()

							continuar()
						}
						pare
					caso 4: 
						escreva("Encerrando o programa...")
						pare
					caso contrario:
						se(opt != 404){opt = 404}
						pare
				}
		}
	}
}
/* $$$ Portugol Studio $$$ 
 * 
 * Esta seção do arquivo guarda informações do Portugol Studio.
 * Você pode apagá-la se estiver utilizando outro editor.
 * 
 * @POSICAO-CURSOR = 542; 
 * @PONTOS-DE-PARADA = ;
 * @SIMBOLOS-INSPECIONADOS = ;
 * @FILTRO-ARVORE-TIPOS-DE-DADO = inteiro, real, logico, cadeia, caracter, vazio;
 * @FILTRO-ARVORE-TIPOS-DE-SIMBOLO = variavel, vetor, matriz, funcao;
 */