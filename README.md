Projeto Banco de Criptomoedas em C . Nomes -Pedro de Oliveira Schwank RA: 24.124.052-2 -Felipe Franco Falcon RA: 24.124.035-7 -Leonardo Pera Chacon Guadagni RA:24.124.022-5 . 
Sistema de Investimentos - Gerenciamento de Criptomoedas e Investidores
Este programa implementa uma plataforma em C para gerenciar investidores e suas operações com criptomoedas. Ele oferece funcionalidades tanto para administradores quanto para investidores, permitindo operações como cadastro, exclusão, consulta de saldos e extratos, além da compra e venda de criptomoedas.

O sistema é dividido em dois perfis principais: Administrador e Investidor.

Funcionalidades
Administrador
O administrador possui privilégios para gerenciar os investidores e as criptomoedas cadastradas no sistema. O acesso é realizado por meio de uma senha fixa e predeterminada:

CPF: 12345678900
Senha: 123456
As principais ações disponíveis para o administrador incluem:

Cadastrar e excluir investidores.
Consultar saldo e extrato de qualquer investidor.
Cadastrar, excluir e atualizar a cotação de criptomoedas.
Gerenciar taxas de compra e venda de cada criptomoeda.
Investidor
Os investidores podem realizar transações financeiras e acessar suas informações pessoais após o login. Suas ações disponíveis incluem:

Consultar saldo e extrato pessoal.
Depositar e sacar dinheiro.
Comprar e vender criptomoedas com base nas cotações e taxas aplicadas.
Estrutura de Dados
Os dados são armazenados em arquivos de texto simples:

investidores.txt: Registra os dados de todos os investidores, incluindo nome, CPF, senha, saldo e a quantidade de criptomoedas que possuem.
criptomoedas.txt: Contém informações sobre as criptomoedas cadastradas, como cotação atual e taxas de compra e venda.
<cpf>_extrato.txt: Armazena o histórico de transações de cada investidor, como depósitos, saques, compras e vendas.
Como Funciona
Ao iniciar o sistema, o usuário é direcionado para um painel inicial onde escolhe entre:

Acessar o painel do administrador.
Acessar o painel de investidor.
Cadastrar um novo investidor.
O administrador usa as credenciais fixas para acessar suas funcionalidades, enquanto os investidores fazem login com seus dados pessoais cadastrados.

Operações com Criptomoedas
O sistema permite:

Cadastro de novas criptomoedas: Nome, cotação inicial, e taxas de compra/venda.
Compra e venda de criptomoedas: Realizadas pelos investidores com base no saldo disponível.
Atualização automática das cotações: Simula variações no mercado financeiro, gerando valores aleatórios entre 90% e 110% da cotação atual.
Observações
A senha fixa do administrador foi incluída como funcionalidade básica para testes e pode ser modificada para maior segurança.
O sistema utiliza arquivos de texto simples para armazenamento, sendo uma solução educativa e não recomendada para produção sem melhorias de segurança, como criptografia de senhas.
Execução
Compile o programa:
bash
Copiar código
gcc sistema_investimentos.c -o sistema_investimentos
Execute:
bash
Copiar código
./sistema_investimentos
Com isso, o sistema estará pronto para uso, permitindo que administradores e investidores explorem todas as funcionalidades disponíveis.
