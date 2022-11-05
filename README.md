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

<b>RF001 – Nível da caixa<\b><br>
O sistema deve informar o nível da caixa d’água.
RF002 – Acionar o motor
O sistema deve permitir acionar o motor de forma remota.
RF003 – Desligar o motor
O sistema deve permitir desligar o motor de forma remota.
RF004 – Acionamento do motor automaticamente.
O motor deve ser acionado automaticamente quando o nível baixar de 25% para evitar o desabastecimento.
RF005 – Desligar o motor
O motor deve ser desligado automaticamente quando o nível da caixa chegar a 100%.
RF006 – Acionamento do motor remoto
O sistema deve permitir ligar ou desligar o motor remotamente quando o nível da caixa estiver entre 25 e 100%. Abaixo de 25% o motor não deve ser desligado para evitar falta de água.

 
### Requisitos não funcionais
 RNF1 - ......
 
### Diagrama
[Comment] <> *Apresentar diagramas (UML, funcionamento...)

### Descrição Funcional

## Testes
[Comment] <> *Descrever os testes a serem executados

## Changelog
[Comment] <> *Descrever as mudanças, quem fez a mudança e quando.
