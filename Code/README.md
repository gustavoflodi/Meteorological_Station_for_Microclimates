## Testes e Validação

Para os testes e validação, compilamos o código com o comando 'gcc BMP280.c -o BMP280', gerando o executável, e, posteriormente, rodamos o executável com o './BMP280'.
Para os testes, estivemos no laboratório da USP, acessamos a rede para comunicar com as placas e, finalmente, compilamos o código na máquina host.
Na máquina host foi criado o arquivo BMP280.c com o código do github, compilado pelo comando '{CC} -Wall BMP280.c -o BMP280c, gerando o executável. Para transferir o executável 
a placa, foi usado o comando 'scp BMP280 root@XXX.X.XXX:home/root', sendo os X's, o endereço de IP da placa do laboratório. 

Além disso, foram criados os arquivos de Cliente e Servidor, respectivamente em C e em Python, o último sendo desenvolvido por meio da aplicação Qt Design.

BMP280.c -> código de leitura do sensor
BMP280 -> Executável
Server_Python.py -> código do servidor feito pelo Qt Design
TesteClienteC.c -> código para o embarcado
Embarcados_Nich.zip -> histórico de desenvolvimento do servidor python
Dev_Interface.zip -> histórico do desenvolvimento do servidor já convertido para c
