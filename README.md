<h1> Feeding The chain </h1> 

>Status: Em desenvolvimento ⚙️ 

<h2>Repositório destinado ao desenvolvimento do projeto Feeding The Chain </h2>
<p> Solução visando o problema do desperdicio de alimentos, focando na etapa do transporte onde em média 45% dos alimentos são desperdiçados por conta das más condições em que são transportados, portanto criamos uma solução que visa monitorar esses ambientes de transporte dos alimentos </p>


## Equipamentos utilizados 🧰 : 

<table> 
  <tr>
    <td>Fotorresistor</td>
    <td>LCD 16 x 2</td>
    <td>Verde LED</td>
    <td>SW 200D / ADXL 345 </td>
    <td>Vermelho LED</td>
    <td>220 Ω Resistor</td>
    <td>Arduino Uno R3</td>
    <td>10 kΩ resistor</td>
    <td>3 kΩ Resistor</td>
    <td>Piezo</td>
    <td>1KΩ resistor</td>
    <td>Teclado 4x4 </td>
    <td>Posicional Micro Servo</td>
    <td>Baseado em PCF8574, 32 LCD 16 x 2 (I2C)</td>
    <td>DHT 11/ TMP36 </td>
  </tr>
  <tr>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>2</td>
    <td>2</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
  </tr>
</table>


## Pontos Importantes do projeto ⚠️ : 

O circuito e projeto real utilizam de um DHT11, sensor de umidade e temperatura e um ADXL 345 para a medição de vibração do ambiente

Por conta da falta desse equipamento na plataforma tinkercad fizémos com base em sensores disponíveis, no caso o TMP36 para simular temperatura e umidade e o SW200D para simular vibração

Assim sendo, para simular o uso de uma blockchain que gravaria os dados permanentemente foi utilizada a EEPROM do próprio arduino para simular a gravação de informações 
 
## Funcionalidades📟: 

* Medir Temperatura
* Medir Luminosidade do ambiente
* Medir Umidade 
* Medir Vibração do container
* Alertar quando os níveis estão Inadequados 
* Exibir as medidas no display LCD 
* Possuir Leds que ajudam no alerta dos níveis do ambiente
* Restringir a  abertura das portas à apenas aqueles que tem a senha
* fechar e abrir as portas com o servo motor 
* Ativar o buzzer com níveis inadequados de qualquer parâmetro 
* Salvar os dados de forma permanente na EEPROM do arduino simulando Blockchain 
