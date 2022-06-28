# Trabalho - Arquivos

## Instruções:
- A atividade é individual e será verificado plágio;
- A implementação deve usar a notação de classes vista em aula;
- É possível consultar, porém, não troque informações com os colegas;
- Submeta o link repositório do GitHub Classroom na tarefa do SIGAA.

## Aplicação

O trabalho consiste em desenvolver uma aplicação no contexto de análise dados. Tais aplicações são conhecidas por extrair informações de um conjunto de dado que pode estar armazenados num banco de dados ou em um arquivo estruturado. Em nosso trabalho, os dados estarão num arquivo de texto simples com dados estruturados.

Os dados podem ser representados por uma tabela em que cada linha representa um registro de informação e cada coluna representa um dos campos do registro. Os campos podem ser de apenas dois tipos: informações numéricas ou categóricas. As informações numéricas, como o nome sugere, representa valores reais e as informações categóricas representam valores discretos num conjunto pré-definido. O objetivo da aplicação consiste em recuperar essas informações de um arquivo de texto e utilizá-las num algoritmo de análise. A próxima seção descreve a estrutura do arquivo e a segunda seção descreve o algoritmo de análise que deve ser desenvolvido.

### Formato do Arquivo

O arquivo é estruturado em duas seções. A primeira seção inicia com a palavra "@info" e deve ser a primeira linha do arquivo. As demais n linhas iniciando com a palavra "@attribute" determinam os tipos de informações de cada coluna da tabela de dados na mesma ordem de especificação, isto é, a primeira linha determina o tipo de dados da primeira coluna, a segunda linha determina o tipo de dados da segunda linha, e assim por diante. Logo, a quantidade de linha com "@attribute" determina a quantidade de colunas da tabela.

A palavra "@attribute" é sempre seguida por um nome, isto é, o nome da coluna, isto é, uma palavra formada apenas por letras, números ou subtraço. Por sua vez, o nome é seguido pelo tipo de dado ambos separados por um ou mais espaços. O tipo de dado pode representado pela palavra "numeric" ou então pela representação de um conjunto, isto é, sequências de ao menos dois textos separados por uma vírgula iniciando pelo caractere '{' e encerrando com o caractere '}'. Os textos podem aparacer entre aspas duplas que são obrigatórias caso a palavra contenham espaços. O texto a seguir apresenta um exemplo da primeira seção do arquivo:

    @info
    @attribute att1 numeric
    @attribute    novo_atributo    numeric
    @attribute exemplo_conj {1  ,    "2", desconhecido   }
    @attribute complexo        {"valor com espaco", "outro valor"}

No exemplo, a primeira linha determina o início da seção. A segunda linha determina que o primeiro campo dos registros possui o nome "att1" e podem assumir valores reais. A terceira linha corresponde ao segundo campo do registro e possui nome "novo_atributo" que também pode assumir valores numéricos. A duas últimas linhas especificam atributos categóricos, o penúltimo de nome "exemplo_conj" e o último de nome "complexo". Cada um é seguido pela especificação de um conjunto onde cada elemento é um texto. Assim, o terceiro campo dos registros podem assumir somente os valores "1", "2" ou "desconhecido" e nenhum outro. De modo análogo, o último campo só pode assumir os valores "valor com espaco" ou "outro valor".

A segunda seção do arquivo incia por uma linha contendo a palavra "@data" e as demais linhas especificam os registros do arquivo, isto é, cada linha da tabela de dados. Um registro será representado por contendo valores separados por vírgula. Cada registro contém uma quantidade de valores igual à quantidade de campos indicados na seção inicial do arquivo. Assim como nos conjuntos, os valores categóricos podem estar representados entre aspas duplas.

Além disso, pode ocorrer situações que um registro não possui um valor para um determinando campo, por exemplo, o campo não é aplicável para aquele registro, o valor não foi preenchido ou é desconhecido. Nesses caso, o campo terá o caractere '?' e ele não é um valor válido para um dos valores do conjunto. Essa informação também precisa ser representada no sistema.

Logo, usando o exemplo inicial do arquivo, um possível conteúdo seria:

    @info
    @attribute att1 numeric
    @attribute    novo_atributo    numeric
    @attribute exemplo_conj {1  ,    "2", desconhecido   }
    @attribute complexo        {"valor com espaco", "outro valor"}
    @data
    1, 2, 1, "outro valor"
    5, 5, desconhecido, "valor com espaco"
    0, 0, ?, ?

Observe que esse arquivo representa uma tabela de 3 linhas por 4 colunas. O primeiro registro é formado pelos campos <1, 2, 1, "outro valor">, o segundo registro assume o valor "desconhecido" para o terceiro campo que difere da situação do valor indeterminado representado pelo caractere '?' exemplificado na última linha.

Desse modo, a aplicação deve conseguir recuperar as informações do arquivo de dados e representá-los num formato adequado para a análise dos dados. Ela também deve analisar se o arquivo está estruturado de modo correto e caso contrário deve indicar a linha e o caractere do primeiro erro como também o que era esperado. Por exemplo, se o arquivo estiver vazio então uma mesagem de erro adequada seria "Erro na linha 0 e caractere 0. Era esperado a palavra "@info"" ou então caso um registro tenha uma quantidade insuficiente de campos "Erro na linha 20 e caractere 30. Fim prematuro do registro. Faltam valores para 4 campos".


### Análise

Para a análise serão fornecidos um arquivo de dados, uma porcentagem P e um valor inteiro C. O arquivo fornecido representará uma base de dados em que a última coluna é chamada de 'classe' e consiste em um tipo categórico. O objetivo da aplicação é determinar a classe de um registro pode ser determinado pelos registros mais próximo onde a noção de proximidade será determinada de acordo com uma métrica.

Assim, a aplicação deve selecionar de modo aleatório uma quantidade de registros equivalente à porcentagem P especificada sobre o total de registros dos dados. A parte selecionada será chamada de 'dados de teste' e a restante de 'dados de treinamento'. Em seguida, para cada um dos registros dos dados de teste a aplicação deve determinar os C registros mais próximos na base de treinamento determinada pela seguinte função:

<img src="https://latex.codecogs.com/svg.latex?dist(A,B)=\sum_{i=1}^{n}(diff(A_i,B_i))^2" title="dist(A,B)=\sum_{i=1}^{n}(diff(A_i,B_i))^2" />

Onde A e B são dois registros da mesma base de dados, contento n campos (excluindo o último campo que é a classe) e diff é uma função que determina a diferença entre os valores de dois campos. Se o campo é do tipo numérico então a função consiste na diferença entre os dois valores e para o tipo categórico a função retorna 1 se os valores diferem e 0 caso sejam iguais. Além disso, pode ocorrer que algum valor Ai seja desconhecido, isto é, seja '?', logo, se algum dos valores é igual à '?' então a função retorna 1.

Ao determinar os C registros mais próximos de um registro da base de teste, a aplicação deve calcular qual o valor da classe mais frequente nos C registros e comparar com o valor presente no campo da classe do registro e armazenar essa informação para apresentação na saída de dados.

## Saída de Dados

Para cada instância da base de testes, deve ser apresentado o registro e a classe dos C registros mais próximos. Por fim, deve ser apresentada uma matriz relacionando os valores da classe (coluna) das classes dos registros de teste com a classe determinada pelos seus vizinhos (colunas) como na figura abaixo que considera uma base de dados em que o campo da classe pode assumir três valores {A, B, C}:

| |A|B|C|
|-|-|-|-|
|A|3|0|0|
|B|0|3|1|
|C|2|0|2|

Na tabela acima, as colunas representam o valor real dos registros no campo classe e as linhas representam os valores determinados pelos vizinhos. Cada valor representa as quantidades de associações, por exemplo, 3 registros da classe A foram associados a classe A pelos seus vizinhos, 1 registro da classe C foi associado a classe B, 2 registros da classe A foram associados a classe C e assim por diante.

## Avaliação

A implementação deve ser entregue até o final do dia 18 de julho e teremos uma entrega parcial até o final do dia 8 de julho em que deve ser submetidos a parte da aplicação responsável pela leitura do arquivo de dados (seção de Formato do Arquivo). Além disso, teremos uma avaliação parcial no dia 12 de julho correspondendo a metade da nota da unidade.

O trabalho será avaliado quanto a modelagem do problema apresentado na linguagem C++, isto é, uso de classes, uso da biblioteca padrão da linguagem C++, manipulação de arquivos e quanto ao uso dos conceitos estudados em estrutura de dados, ou seja, algoritmos de busca, ordenação e estruturas de dados sequenciais.



