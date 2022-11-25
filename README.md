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

## Testes

1 - Teste da conexão com broker MQTT.<br>
2 - Teste dos sensores utilizados para monitorar o nível da caixa<br>
3 - Verificar se o motor é acionado quando o nível da caixa for menor que 25%<br>
4 - Verificar se o motor é desligado quando o nível da caixa atingir 100%<br>
5 - Verificar se o motor é acionado pelo client MQTT quando o nível estiver entre 25% e 100%.<br>

## Changelog
Versão   |  Data     | Responsável       | Change  <br>
1.0      |  01/11/22 | Gustavo           |Readme completado <br>
1.1      |  02/11/22 | Gustavo           |Conexão com wifi e MQTT <br>
1.2      |  04/11/22 | Gustavo           |Leitura dos sensores <br>
1.3      |  10/11/22 | Gustavo           |Finalização do código
1.4      |  15/11/22 | Gustavo           |Realização dos testes
