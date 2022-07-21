# Trabalho 3 - Dados
Feito por [Daniel Luan Lourenço de Lima](https://github.com/DanieLuan).

Trabalho final da disciplina de Linguagem de Programação I. A atividade consiste em fazer uma aplicação que leia um arquivo e salve suas informações numa estrutura de dados para que seja possível interpretar e analisar esses dados.

# Funcionamento

Inicialmente é necessário ler um arquivo num formato específico para que as informações possam ser traduzidas de modo que o programa consiga interpretar. 
### Leitura
Um exemplo de formato do arquivo para ser lido seria

    @info
    @attribute att1 numeric
    @attribute    novo_atributo    numeric
    @attribute exemplo_conj {1  ,    "2", desconhecido   }
    @attribute complexo        {"valor com espaco", "outro valor"}
    @data
    1, 2, 1, "outro valor"
    5, 5, desconhecido, "valor com espaco"
    0, 0, ?, ?
Onde:
- `@info` indica o início do arquivo
- `@attribute` indica um novo atributo, o qual pode ser **Numeric** ou **Categoric**. O tipo Numeric pode receber qualquer valor real, já o tipo Categoric
- `@data` indica o inicio da leitura dos dados que irão preencher os campos determinados pelos `@attribute`'s

Cada linha do `@data` é um Objeto, o qual tem um certo numero de atributos.

Para isso, o programa foi dividido em três classes principais:
##### Classe `Attributes`
A classe `Attributes` serve para salvar quais são os nomes dos atributos e qual seu tipo. Para determinar um tipo de atributo, é usado um vector de strings. Caso esse vector seja de um único elemento, então o atributo é do tipo **NUMERIC**, caso contrário sempre será do tipo **CATEGORIC**.

##### Classe `Object`
A classe `Object` representa cada objeto à ser adicionado, ela possui uma lista de atributos numéricos e categóricos, além de um valor `dist`, que será usado na parte de análise.

#### Classe `Data`
A classe `Data` junta as duas classes anteriores, e dessa forma consegue armazenar os atributos e os objetos de forma eficiente, sem perder a precedência de ambos.

### Análise

Para realizar a análise, são necessários dois valores arbitrários:
- P : Percentual de 0 até 1 do número de objetos de teste.
- C : Número de objetos para calcular um registro.

Basicamente, serão utilizados duas listas de objetos, uma de *teste* e outra de *treino*. O percentual *P* será o número de quantos objetos do total serão escolhidos como objetos de teste. O Restante será escolhido como objeto de treino.
Cada objeto de teste será comparado com todos os de treino para calcular a distância entre cada um deles.
Quando a distância estiver calculada, o programa escolhe os *C* primeiros objetos e determinam a classe que mais aparece entre eles.
Assim, no final será apresentada uma matriz em que as colunas representam os valores reais dos registros de teste, e as linhas os valores calculados através dos *C* vizinhos mais próximos.

## Compilação

Para compilar, pode-se utilizar Makefile e rodar o comando a baixo na pasta principal.
```
make all
```
Isso gerará o arquivo executável.
Caso não tenha o Makefile, pode utilizar o comando a baixo que terá o mesmo efeito.
```
g++ -Wall -o main main.cpp src/*.cpp
```
## Execução

Para executar o programa deve-se indicar, além do programa executável, qual o diretório onde o arquivo para leitura se encontra. No caso, três arquivos de exemplo estão no diretório principal para teste, então por exemplo
```
./main Numeric.txt
```
Caso não coloque argumentos, ele irá rodar o arquivo de teste "Numeric.txt" por padrão.
