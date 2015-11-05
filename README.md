# uBox

O projeto uBox foi concebido para ser usado na introdução de iOT.

O rôbo pode funcionar em modo autônomo ou controlado por comunicação serial: por bluetooth (android) ou PC, através de web site.  
Possui alguns sensores para capturar o ambiente externo e publicar na web.

Além de alguns sensores, possui também uma webcam que pode ser usada para obtenção de fotos e publicação na web.

## Características básicas (periféricos e sensores)

- Cubietruck para processamento e conexão com a internet e hospedagem do site web
  - Bluetooth
  - Wirelles
- Arduino Mega 2506
- Display LCD (16x2) para exibição de informações
- Webcam para filmagem
- Sensor Ultrassonico para medir distâncias e evitar colisões;
- Sensor LDR para detectar presença de luz;
- Cabeça com giro na horizontal para movimentar o sensor de obstáculo e identificar colisões.

## Código do projeto

O código do projeto é dividio em várias partes para melhor gerenciamento, controle e manutenabilidade.  
Abaixo segue uma breve descrição de cada classe do projeto.

### Ubox_Command

Processa a entrada de comandos do robô e determina a ação a ser executada.  
A entrada de comandos por ser feita por celular (android) via bluetooh (módulo conectado ao arduino) ou por comunicação serial via USB. Quando conectado ao celular por bluetooth aceita comandos de voz, pela aplicação AMR_Voice, ou comandos em modo texto.

### Ubox_Engines

Gerencia os motores do robô. 
De acordo com o comando recebido movimenta o robô na direção especificada.

### Ubox_Sensors

Gerencia os sensores do robô. 
Auxilia a obtenção de valores dos sensores para determinar o comportamento do robô.

### Ubox_Head

Controla o comportamento da cabeça do robô.

## Rotina principal (Ubox.ino)

A rotina main do robô instância e utiliza cada uma das classes descritas anteriormente, além de definir os pinos usados pelo robô.

O processamento de cada rotina segue uma ordem especifica que permite ao robô tomar decisões e interferir em comandos recebidos.
Seu comportamento é variável, pois, mesmo que lhe seja fornecido um comando a ser executado, ele irá avaliar as condições do ambiente para determinar se deve ou não obedecer ao comando. Esta regra não é válida para todos os comandos, e basicamente funciona para os comandos de movimentação do robô. O robô sempre verifica a existência de obstáculos antes de se locomover e evita bloqueios.

#### Ordem de processamento das rotinas no metódo loop principal:
1. Processa os comando recebido (por bluetooth, serial, pc) e determina os movimentos do robô ou ação a ser executada;
2. Obtêm dados dos sensores para verificar a situação do ambiente;
3. Executa a ação determinada.
