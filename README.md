# Trabalho_EBD2
Calculadora HP

Conversão de Pos para in = Arvore \n
+,* = Tanto faz o lado \n
/,-,^,% = Verificar se a orddem ta correta \n
log,sen,cos,tg,raiz = 1 operador \n
\n
Conversão de In para pos = Pilha de Shunting Yard \n
Verifica se tem ( ou se tem numero ou sinal \n
Se sim, verifica se tem numero ou sinal (se for sinal armazena, se numero sai) \n
Faz o passo anterior até encontrar ) ou terminar leitura \n
\n
Verificador de numero/sinal = Carro de string \n
Confere se é um sinal(+,-,*,/,^,%), operação unica(log10,sen,cos,tg,raiz) (pre colocados) ou numero \n
Empilha numeros na saida ou na pilha até encontrar sinal \n
Se é numero tenta transformar em double
