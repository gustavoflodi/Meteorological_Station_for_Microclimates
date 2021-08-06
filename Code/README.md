## Testes e Validação

Para os testes e validação, compilamos o código com o comando 'gcc BMP280.c -o BMP280', gerando o executável, e, posteriormente, rodamos o executável com o './BMP280'.
Para os testes, estivemos no laboratório da USP, acessamos a rede para comunicar com as placas e, finalmente, compilamos o código na máquina host.
Na máquina host foi criado o arquivo BMP280.c com o código do github, compilado pelo comando '{CC} -Wall BMP280.c -o BMP280c, gerando o executável. Para transferir o executável 
a placa, foi usado o comando 'scp BMP280 root@XXX.X.XXX:home/root', sendo os X's, o endereço de IP da placa do laboratório. 

