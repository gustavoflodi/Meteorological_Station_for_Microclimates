#### Gustavo Fernandes Lodi - 10308801
#### Gustavo Ogera Malavazi - 10388645
#### Nicholas Jose Peçanha - 10309312

# Meteorological_Station_for_Microclimates


# Introdução

O projeto teve como objetivo a construção de uma Estação Meteorológica para Microclimas, utilizando como base os conhecimentos adquiridos ao longo do desenvolvimento da disciplina de Sistemas Embarcados. O projeto teve como macroetapas: 

* Definição do ambiente de trabalho, especificamente, a máquina Host, o SO que usaríamos pela disponibilidade do grupo, a IDE, a ferramenta de versionamento, as bibliotecas e, finalmente, o micro-controlador target do projeto. Para consolidação e validação com todo o grupo e com os doscentes da disciplina, foi confeccionado um diagrama de blocos, contendo os componentes a serem utilizados. 

* Considerações de hardware, ou seja, especificação do microcontrolador, protocolo de comunicação, particularmente o modelo de barramento compatível com o projeto, sensores dos parâmetros que seriam medidos e, finalmente, o projeto mecânico, ou seja, ancoragem de conectores, necessidade de encapsulamento tipo de estrutura. 

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
  
# Plataforma de Desenvolvimento e Ferramentas

Durante o desenvolvimento do projeto, algumas ferramentas foram essenciais. Como sistema operacional, foi usado o Linux. Para desenvolver o código do projeto, o grupo optou pela IDE VS Code, pela experiência prévia com a plataforma. Para o versionamento do código, foi usado Git nas máquinas dos integrantes e GitHub para garantir que todos pudessem estar atualizados quanto ao código. Algumas interfaces gráficas ajudaram nisso, sendo elas o GitKraken e o p4merge.

# Desenvolvimento

## Lógica de programação

Apesar de ter sido escolhido o sensor BMP280 para fazer as medições do projeto, durante a etapa de desenvolvimento foi também explorado a ideia de usar o sensor de temperatura, pressão e umidade OAK RH. Esse sensor foi uma sugestão do professor, por já estar disponível no laboratório e ser da própria toradex. Foram desenvolvidas algumas amostras de código com base nesse sensor que ainda se encontra neste repositório, mas, por fim, o grupo decidiu seguir como o BMP280. Portanto, essa seção irá abordar apenas o código desse sensor usado.

De forma resumida, podemos descrever o código da seguinte forma: Declaração das bibliotecas (padrões da linguagem C e algumas esepcíficas do sensor), conexão com o bus da placa, configuração dos modos de operação do sensor e da sua calibração, conversões para interpretar as medidas e finalmente a impressão dessas medidas para o usuário no prompt de comando. Vale ressaltar que há algumas condições dentro do código que garantem a segurança do seu funcionamento, abortando a execução e avisando o usuário que existe um problema caso a conexão falhe ou caso a calibração não ocorra pela conexão erradas dos pinos. Todos esses procedimento estão comentados no código para acompanhar com mais facilidade. Segue abaixo um fluxograma demonstrando toda a lógica:   

![alt text](https://github.com/selnoom/Meteorological_Station_for_Microclimates/blob/main/Imagens/Untitled%20Diagram.png)

## Conexões

A conexão entre o sensor e a placa foi obtido por meio de um protoboard. Se baseou no protocolo I2C, que providencia o bus nos pinos 194/196. Porém, conectando o viola na placa, é necessário estar atento as novas posições dos pinos a serem usados, o 5 e 6. Nesses pinos foram conectados o SDA (comunicação serial) e SCL (controle de clock) do sensor. Também foi necessário alimentar o sensor, mas isso foi feito com os pinos 5V e GND da própria placa. A comunicação entre o computador e o embarcado foi feito com conexão USB, mas também é possível com um cabo de ethernet.

## Comunicação Cliente - Servidor

Para o projeto, foi criado também um servidor em Python, hosteando a Interface, e que também recebe mensagens do Cliente, este último presente no Sistema Embarcado. As mensagens consistem nos dados de Temperatura e Pressão, obtidos pela leitura do sensor no código principal BMP280.c.

Para desenvolver a interface a ser utilizada pelos usuários da estação de microclimas, foi utilizada a ferramenta Qt Design. Tal ferramenta desenvolve o códigoem .c a ser visualizado de forma gráfica, em seguida, o código da interface é convertido para Python. Para a parte estática, foi desenvolvido o fundo de tela na aplicação Photoshop, sendo uma imagem .png (adicionada no código), e três outros recursos, a saber, um botão de connect, cujo acionamento acarreta na comunicação com o servidor e dois display para mostrar os parâmetros lidos pelo sensor.

A escolha da ferramenta Qt Designer para configuração da aplicação gráfica é justificada pela facilidade que ela adiciona ao projeto à configuração de variáveis como tamanho de letra, posição dos componentes, cor dos itens, o que aumentaria o tempo de implementação, ou seja, a ferramenta adicionou uma parte Low-code efetiva ao trabalho.

![alt text](https://github.com/selnoom/Meteorological_Station_for_Microclimates/blob/main/Code/Interface.jpeg)

# Resultados

Devido a situação anormal da realização da disciplina, sendo todo o aprendizado e as práticas feitas a distância, surgiram alguns desafios que impactaram nos resultados obtidos. Isso foi observado especialmente na etapa de conexão entre placa e sensor, que é algo que deve ser testado repetidamente para funcionar, porém não foi possível ter tantas oportunidades de executar estes testes. A imagem a seguir mostra um pouco da trajetória do código desenvolvido:
![alt text](https://github.com/selnoom/Meteorological_Station_for_Microclimates/blob/main/Imagens/GitKraken.png)

Como mencionado anterirormente, foi avaliado a possiblidade de seguir com o sensor OAK RH ao invés do BMP280. Isso se deve pelas dificuldades encontradas de usar o BMP280 mencionados anteriormente. O sensor Oak tinha um sensor de humidade além do de pressão e temperatura e uma quantidade relevante de material disponível sobre seu funcionamento. Porém, essa possibilidade foi considerada em um momento em que o código todo do BMP280 já estava desenvolvido. Por ter pouco tempo de aprender completamente sobre esse outro sensor, o grupo acabou descartando a ideia. Mas foram feitos algumas amostras de código, que chegou a ser compilado:
![alt text](https://github.com/selnoom/Meteorological_Station_for_Microclimates/blob/main/Imagens/Screenshot%20from%202021-08-06%2004-08-00.png)

Apesar das dificuldades encontradas de chegar ao funcionamento do projeto, ainda foram obtidos resultados satisfatórios. O código desenvolvido para o BMP280 apresentou uma ótima qualidade, sendo necessários poucas mudanças para conseguir fazer a compilação cruzada, como vemos a seguir:
![alt text](https://github.com/selnoom/Meteorological_Station_for_Microclimates/blob/main/Imagens/Compila%C3%A7%C3%A3o_cruzada.jpeg)

Além disso, a transferência do executável para a placa, com o comando scp, também na imagem acima, ocorreu sem nenhum problema. O próximo passo foi executar o arquivo agora na placa, porém foi nessa etapa que começou os problemas de conexão. O código do sensor foi feito todo sem testes praticamente, devido a situação de como estava sendo realizada a disciplina. Assim, quando foi possível testar o sensor, já estava próximo da data de entrega, o que permitiu pouco tempo de correção. Essas correções foram feitas e o código atualizado, agora para incluir o protocolo IC2 (/dev/colibri-i2c1) e com algumas configurações ajustadas depois de analisar o datasheet. Esse código compila normalmente e já está corrigido para conexão com a placa.

Outros pontos importantes que valem ser destacados são que o sensor não foi soldado no seu próprio bórneo, o que pode ser também um motivo de impedir a conexão, e que a pinagem da viola altera a configuração planejada para ter sido feito na placa. Há poucos materiais disponíveis explicando sobre a pinagem dessa carrier board, e nenhum diagrama detalhando realmente a numeração dos pinos, o que abre espaço para ajustar de forma errada os pinos do sensor. 

# Conclusão
A disciplina de Sistemas Embarcados se mostrou ao mesmo tempo como algo importante para tecnologia moderna e essencial para a formação do engenheiro, quanto como uma área muito desafiadora e que exige dedicação para conseguir aplicar ela na prática. Para poder criar um projeto baseado num sistema de embarcado, é necessário ter conhecimento de muitos tópicos, como toda a estrutura dentro dela, conhecimento de sistemas operacionais, Kernel, ToolChain, de hardware e de toda a comunicação a ser feito entre essas unidades, o que torna projetos deste tipo extremamente complexos. Além disso, o fato das práticas serem a distância colocam certa dificuldade de poder experimentar esse aprendizado, já que não é sempre que terá disponibilidade de testar os códigos desenvolvidos.

Mesmo com essa complexidade e dificuldade, ainda foi possível tirar um imenso aproveito da disciplina. Poder conhecer mais sobre todos os tópicos citados da computação é um grande diferencial pro mercado de trabalho e permite encarar problemas da engenharia de uma forma muito eficiente. O projeto desenvolvido ao longo do semestre consolidou esse aprendizado e, apesar de não ter funcionado perfeitamente no dia do teste, compilou de forma correta e com base nos erros, foi possível corrigir o código. Esses resultados foram muito significativos considerando a complexidade do desafio.

# Referências
Datasheets: 

	https://docs.toradex.com/100090-oak-humidity-datasheet.pdf
	https://docs.toradex.com/102879-colibri-arm-viola-carrier-board-datasheet.pdf
	https://developer1.toradex.com/files/toradex-dev/uploads/media/Oak/Oak_ProgrammingGuide.pdf
	
Configurando a placa e comandos:

	https://developer.toradex.com/getting-started/module-2-my-first-hello-world-in-c/build-from-command-line?som=colibri-vf61&board=colibri-evaluation-board&os=linux&desktop=linux
	https://developer.toradex.com/knowledge-base/i2c-linux#tab-bsp-5
	https://developer.toradex.com/knowledge-base/oak-programming-tutorial-for-windows
	
Tutorial:

	https://www.youtube.com/watch?v=j_ulsIMLq_s
	
	
