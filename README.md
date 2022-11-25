# Projeto integrado - Controle de nível de caixa d'água para poço artesiano

### Contextualização

Para controlar o nível de água em um caixa da agua em poços artesianos utiliza-se uma boia, para que quando o nível fique baixo a bomba/motor seja acionado automaticamente. <br>
Entretanto, não é possível controlar o horário em que o motor será ligado, podendo ser em horários inconvenientes, como por exemplo, de madrugada.  <br>
O objetivo de desse projeto é poder acionar ou desligar o motor a qualquer momento de forma remota. Também informar o nível de agua para que possa completar a caixa manualmente durante o dia, assim evitando que o motor seja acionado a noite. <br>
Caso o motor seja acionado durante a noite, deve-se poder desligá-lo manualmente. <br>


### Contexto Técnico

Monitoramento do nivel de água da caixa d'água através de um microcontrolador ESP-32. <br>
Dados enviados para um Broker MQTT. <br>
Dados consumidos por um cliente MQTT. <br>

## Requisitos

### Requisitos funcionais

<b>RF001 – Nível da caixa</b><br>
O sistema deve informar o nível da caixa d’água.<br>
<b>RF002 – Acionar o motor</b> <br>
O sistema deve permitir acionar o motor de forma remota.  <br>
<b>RF003 – Desligar o motor</b> <br>
O sistema deve permitir desligar o motor de forma remota. <br>
<b>RF004 – Acionamento do motor automaticamente</b>  <br>
O motor deve ser acionado automaticamente quando o nível baixar de 25% para evitar o desabastecimento. <br>
<b>RF005 – Desligar o motor</b> <br>
O motor deve ser desligado automaticamente quando o nível da caixa chegar a 100%. <br>
<b>RF006 – Acionamento do motor remoto</b> <br>
O sistema deve permitir ligar ou desligar o motor remotamente quando o nível da caixa estiver entre 25 e 100%. Abaixo de 25% o motor não deve ser desligado para evitar falta de água. <br>

### Requisitos não funcionais

<b>RNF001 – Nível da caixa d’água</b><br>
Através de boias será medido o nível da caixa. Serão utilizadas quatro boias e o nível deverá ser indicado de 25 em 25 por cento (4 níveis).<br>
<b>RNF002 – Protocolo de comunicação MQTT</b><br>
Será utilizado o protocolo de comunicação MQTT utilizando clientes MQTT e um broker MQTT na nuvem.<br>
<b>RNF003 – ESP32</b><br>
O sistema será desenvolvido utilizando o microcontrolador ESP32<br>

### Diagrama

![diagrama](https://user-images.githubusercontent.com/46695647/200136950-279a5a30-f1a9-4d95-9d20-b016de873bc5.jpg)

### Descrição Funcional
<br>
O sistema possuí 4 sensores de nível de água.<br>
<br>
<b>Sensor 1 - 25% </b><br>
<b>Sensor 2 – 50% </b><br>
<b>Sensor 3 – 75% </b><br>
<b>Sensor 4 – 100% </b><br>
<br>
Quando o sensor 1 é acionado, é enviado para o broker a informação de que a caixa está com 25% de capacidade. Quando o sensor 2 é acionado significa que a caixa tem 50% da capacidade e assim sucessivamente até chegar aos 100%.<br>
Quando o nível da caixa atinge 25%, o motor deve ser acionado automaticamente. Ao atingir 100% o sistema deve desligar o motor automaticamente.<br>
Quando o nível da caixa estiver entre 50% e 100% o sistema permite desligar o motor remotamente através de um comando.<br>

## Testes

1 - Teste da conexão com broker MQTT.<br>
2 - Teste dos sensores utilizados para monitorar o nível da caixa<br>
3 - Verificar se o motor é acionado quando o nível da caixa for menor que 25%<br>
4 - Verificar se o motor é desligado quando o nível da caixa atingir 100%<br>
5 - Verificar se o motor é acionado pelo client MQTT quando o nível estiver entre 25% e 100%.<br>

### Descrição dos testes
<b>Teste de conexão com broker MQTT </b><br>
Publicado uma string em um tópico de testes. Consumido o mesmo tópico e verificando se a string é a mesma que foi postada.<br>

<b>Teste dos sensores </b><br>
Os sensores são de contato seco. Testado a continuidade utilizando um multímetro.<br>

<b>Teste do código da leitura dos sensores </b><br>
Todos os sensores desacionados. Verificado o valor lido pelo código. Com todos os sensores em zero esperasse que o valor lido seja Zero.<br>
Acionado somente o sensor 1. O valor esperado é 25%. O valor lido foi de 25%.<br>
Acionado sensor 1 e sensor 2. O valor esperado é de 50 %. O valor lido foi de 50%<br>
Acionado sensor 1, 2 e 3. O valor esperado é 75%. O valor lido foi de 75%.<br>
Acionado todos os sensores. O valor esperado é 100%. O valor lido foi de 100%.<br>

<b>Teste do motor </b><br>

Acionado somente o sensor 1 para simular o nível da caixa d’água em 25%. O motor é simulado pelo led do ESP-32 (GPIO2). O led foi acionado quando o nível atinge 25%.<br>
Acionado todos os sensores para simular o nível da caixa d’água em 100%. O motor simulado pelo led do ESP-32 foi desligado.<br>
Acionado o sensor 1 e o motor foi acionado, acionado o sensor 2 e motor continuou acionado, acionado o sensor 3 e o motor continuou acionado , acionado o sensor 4 e o motor foi desligado.<br>
Desacionado o sensor 4 e o motor continuo desligado, desacioando sensor 3 e o motor continuou desligado, desacionado sensor 2 e o motor foi religado pois a caixa atingiu 25%.<br>

<b>Teste acionamento remoto </b><br>
Acionado sensores 1 e 2 para simular o nível da caixa em 50%. Nesse momento o motor está acionado. Pressionado o botão para desligar o motor no MQTT Dashboard. O led foi desligado indicando que o motor foi desligado.<br>
Pressionado o botão novamente e o motor foi religado.<br>
Acionado sensores 1,2 e 3 para simular o nível da caixa em 75%. Acionado o botão no MQTT Dashboard e o motor foi desligado. Pressionado novamente e o motor foi religado.<br>
Acionado somente o sensor 1 para simular o nível da caixa d’água em 25%. Pressionado o botão no MQTT Dash para desligar o motor. O sistema não permitiu desligar o motor conforme definido no RF004.<br>
Acionado todos os sensores para simular o nível em 100%. Acionado o botão no MQTT Dash para acionar o motor. O sistema não permitiu acionar o motor, pois a caixa já está cheia conforme definido no RF005.<br>

<b>Teste da leitura dos sensores </b><br>

O sistema espera que os sensores sejam acionados na seguinte sequência: <br>
1 – Sensor 1<br>
2 – Sensor 2<br>
3 – Sensor 3 <br>
4 – Sensor 4<br>
Quando o sensor 4 estiver acionado, esperasse que os sensores 1, 2 e 3 também estejam acionados, pois estão abaixo do sensor 4. Quando o sensor 3 estiver acionado, esperasse que o sensor 1 e 2 estejam acionados. E assim sucessivamente.<br>
Quando essa ordem não for respeitado devido algum problema nos sensores, no MQTT Dash na parte que indica o nível da caixa será exibido “999”e o motor deve ser desligado automaticamente.<br>
Para realizar o teste foi acionado somente o sensor 4 e os demais foram desacionados. O motor foi desligado e no MQTT Dash indicou um erro na leitura.<br>

## Protótipo
![WhatsApp Image 2022-11-21 at 12 44 10 (1)](https://user-images.githubusercontent.com/46695647/203999991-8c9ad55e-8fc0-4ddb-91ed-d29cdb2336b9.jpeg)
![WhatsApp Image 2022-11-21 at 12 44 10](https://user-images.githubusercontent.com/46695647/203999898-18b58d77-fc13-4c6a-985a-01553af6b5b0.jpeg)

###Resultados no MQTT Dashboard

![MQTT](https://user-images.githubusercontent.com/46695647/204000580-a95d3c51-c536-4ac5-9f1d-ba7d57ce1158.png)



## Changelog
Versão   |  Data     | Responsável       | Change  <br>
1.0      |  01/11/22 | Gustavo           |Readme completado <br>
1.1      |  02/11/22 | Gustavo           |Conexão com wifi e MQTT <br>
1.2      |  04/11/22 | Gustavo           |Leitura dos sensores <br>
1.3      |  10/11/22 | Gustavo           |Finalização do código  <br>
1.4      |  15/11/22 | Gustavo           |Realização dos testes <br>
