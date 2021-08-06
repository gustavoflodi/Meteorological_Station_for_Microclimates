# Meteorological_Station_for_Microclimates

# Materiais e Métodos 

A arquitetura do sistema pode ser dividida em 3 blocos: A interface do usuário, o microprocessador e o sensor. A interface irá apresentar de forma visual os dados que o sensor BME280 adquirir, que são temperatura e pressão. Estes dados então são lidos pelo microprocessador, que seria a BeagleBone Black (dependo da disponibilidade no laboratório) e convertidos através do código em linguagem C.
A ideia inicial do nosso projeto era utilizar a BeagleBone Black. No entanto, pela indisponibilidade, utilizamos a Toradex VF Colibri.
A imgem abaixo resumo a lógica de aquisição e exibição dos dados.

Projeto de Sistemas Embarcados. Será aplicado os conhecimentos de embarcados para simular uma estação meteorológica de microclimas.

O projeto foi dividido, respectivamente, nas macroetapas de:

1) Definição do ambiente de trabalho, especificamente, a máquina Host, o SO que usaríamos pela disponibilidade do grupo, a IDE, a ferramenta de versionamento, as bibliotecas e, finalmente, o micro-controlador target do projeto. Para consolidação e validação com todo o grupo e com os doscentes da disciplina, foi confeccionado um diagrama de blocos, contendo os componentes a serem utilizados.

2) Considerações de hardware, ou seja, especificação do microcontrolador, protocolo de comunicação, particularmente o modelo de barramento compatível com o projeto, sensores dos parâmetros que seriam medidos e, finalmente, o projeto mecânico, ou seja, ancoragem de conectores, necessidade de encapsulamento tipo de estrutura.

3) Definição da linguagem de programação a ser utilizada e codificação do programa.

4) Testes e Validação do projeto.

Importante destacar que maiores detalhes juntamente com imagens são encontrados nos README dos sub-diretórios desse repositório referentes às macroetapas.
