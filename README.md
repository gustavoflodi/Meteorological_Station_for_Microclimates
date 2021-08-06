# Meteorological_Station_for_Microclimates


# Introdução

O projeto teve como objetivo a construção de uma Estação Meteorológica para Microclimas, utilizando como base os conhecimentos adquiridos ao longo do desenvolvimento da disciplina de Sistemas Embarcados. O projeto teve como macroetapas: 

* Definição do ambiente de trabalho, especificamente, a máquina Host, o SO que usaríamos pela disponibilidade do grupo, a IDE, a ferramenta de versionamento, as bibliotecas e, finalmente, o micro-controlador target do projeto. Para consolidação e validação com todo o grupo e com os doscentes da disciplina, foi confeccionado um diagrama de blocos, contendo os componentes a serem utilizados. **Melhor descrito em Materiais e Métodos.**

* Considerações de hardware, ou seja, especificação do microcontrolador, protocolo de comunicação, particularmente o modelo de barramento compatível com o projeto, sensores dos parâmetros que seriam medidos e, finalmente, o projeto mecânico, ou seja, ancoragem de conectores, necessidade de encapsulamento tipo de estrutura. **Melhor descrito em Materiais e Métodos.**

* Definição da linguagem de programação a ser utilizada e codificação do programa. Ou seja, desenvolvimento da aplicação e maior entendimento do Build Process do microcontrolador Toradex VF Colibri para acesso aos registradores e espaços específicos do memory map do sensor. Implementação da comunicação entre cliente e servidor para simulação de uma interação com a Estação Meteorológica. E, finalmente, design da interface a ser visualizada pelo cliente ou usuário da estação. **Melhor descrito em Desenvolvimento.**

* Testes e validação do projeto. **Melhor descrito em Testes e Resultados.**

# Materiais e Métodos 

A arquitetura do sistema pode ser dividida em 3 blocos: A interface do usuário, o microprocessador e o sensor. A interface irá apresentar de forma visual os dados que o sensor BMP280 adquirir, que são temperatura e pressão. Estes dados então são lidos pelo microprocessador, que seria a BeagleBone Black (dependo da disponibilidade no laboratório) e convertidos através do código em linguagem C.
A ideia inicial do nosso projeto era utilizar a BeagleBone Black. No entanto, pela indisponibilidade, utilizamos a Toradex VF Colibri.
A imagem abaixo resumo a lógica de aquisição e exibição dos dados.

![alt text](https://github.com/selnoom/Meteorological_Station_for_Microclimates/blob/main/Overview%20Specs/DiagramaComponentes_toradex.jpg?raw=true)

Falando mais especificamente do sensor BMP280:
  Capacidade de medição pressão:  300 a 1100 hPa, que seria de +9000m a -500m em relação ao nível do mar
	Erro: 0.12 hPa equivalente a ± 1m
	Capacidade de medição temperatura: -40°C a +80°C
  Interface digital: I²C (up to 3.4 MHz) e SPI (3 and 4 wire, up to 10 MHz)
  Consumo de corrente: 2.7 μA a 1 Hz de aquisição


