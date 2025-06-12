# Trabalho_EBD2
Calculadora HP

Conversão de Pos para in = Arvore <br />
+,* = Tanto faz o lado <br />
/,-,^,% = Verificar se a orddem ta correta <br />
log,sen,cos,tg,raiz = 1 operador <br />
<br />
Conversão de In para pos = Pilha de Shunting Yard <br />
Verifica se tem ( ou se tem numero ou sinal <br />
Se sim, verifica se tem numero ou sinal (se for sinal armazena, se numero sai) <br />
Faz o passo anterior até encontrar ) ou terminar leitura <br />
<br />
Verificador de numero/sinal = Carro de string <br />
Confere se é um sinal(+,-,*,/,^,%), operação unica(log10,sen,cos,tg,raiz) (pre colocados) ou numero <br />
Empilha numeros na saida ou na pilha até encontrar sinal <br />
Se é numero tenta transformar em double = strtod
