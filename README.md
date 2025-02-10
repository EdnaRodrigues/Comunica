# 🖥️ Serial Display com Raspberry Pi Pico W

## 📌 Descrição do Projeto
Este projeto implementa um sistema de exibição de caracteres utilizando o **Serial Monitor do VS Code**, um **display SSD1306** e uma **matriz de LEDs WS2812**. Cada caractere digitado no Serial Monitor é exibido no display, enquanto números de **0 a 9** são representados por símbolos correspondentes em uma **matriz de LEDs 5x5 WS2812**. Além disso, **dois botões físicos** permitem alternar o estado dos **LEDs RGB Verde e Azul**, exibindo mensagens informativas no display e no Serial Monitor.

---

## 🛠️ Funcionalidades
- **Exibição de caracteres digitados no Serial Monitor no display SSD1306**.
- **Representação de números digitados (0 a 9) na matriz de LEDs 5x5 WS2812**.
- **Alternância do LED RGB Verde ao pressionar o botão A**.
  - Mensagem exibida no display: "LED Verde Ligado!".
  - Mensagem enviada ao Serial Monitor: "Botão A pressionado. LED Verde foi ligado.".
- **Alternância do LED RGB Azul ao pressionar o botão B**.
  - Mensagem exibida no display: "LED Azul Ligado!".
  - Mensagem enviada ao Serial Monitor: "Botão B pressionado. LED Azul foi ligado.".
- **Simulação no Wokwi integrada ao VS Code, utilizando comunicação UART**.
- **Rotinas de interrupção (IRQ) para a detecção dos botões**.
- **Tratamento de bouncing dos botões via software**.
- **Fonte personalizada de 6x8 pixels para exibição de símbolos, letras e números**.
- **Uso do protocolo I2C para comunicação com o display SSD1306**.

---

## 🔧 Hardware Necessário - Presentes na Placa de Desenvolvimento BitDogLab
- **Microcontrolador Raspberry Pi Pico W**
- **Display SSD1306 (I2C)**
- **Matriz de LEDs 5x5 WS2812**
- **LED RGB, pinos Verde e Azul**
- **Botões físicos (Botão A e Botão B)**
- **Fonte de alimentação adequada**

---

## 📝 Código Principal
O código principal:
- **Gerencia a exibição de caracteres nos respectivos displays necessários**.
- **Mapeia números para exibição na matriz de LEDs 5x5 WS2812**.
- **Controla os LEDs RGB por meio de interrupções nos botões físicos**.
- **Implementa debounce via software para garantir leituras confiáveis dos botões**.
- **Gerencia mensagens a serem recebidas pelo display SSD1306 e pelo Serial Monitor**.

---

## 📌 Como Rodar o Projeto
### **Softwares Necessários**
1. **VS Code** com a extensão **Raspberry Pi Pico** instalada.
2. **CMake** e **Ninja** configurados.
3. **SDK do Raspberry Pi Pico** corretamente configurado.
4. Simulador **Wokwi** instalado e integrado ao VS Code.

### **Clonando o Repositório**
Para começar, clone o repositório no seu computador:
```bash
 git clone https://github.com/EdnaRodrigues/Comunica.git
 cd Comunica
```

---

### **Execução do Projeto no VS Code**

#### **1. Importar o Projeto**
Após clonar o repositório:
1. Abra o **VS Code**.
2. No menu **Raspberry Pi Pico**, selecione **Import Project**.
3. Escolha a pasta clonada e clique em **Import**.

#### **2. Compilar o Código**
1. Clique no ícone **Raspberry Pi Pico** no lado esquerdo do VS Code.
2. Escolha a opção **Compile Project** para compilar o código.

---

### **Execução no Simulador Wokwi**

#### **1. Configurar o Simulador Wokwi**
1. Abra o arquivo `diagram.json` incluído no repositório.
2. Certifique-se de que o arquivo JSON está configurado corretamente para a simulação do hardware necessário:
   - Display SSD1306 conectado via I2C.
   - Matriz de LEDs WS2812 corretamente configurada.
   - Botões físicos conectados aos GPIOs corretos.
   - LED RGB devidamente conectado aos GPIOs corretos.

#### **2. Executar a Simulação**
1. Abra o painel do simulador Wokwi no VS Code.
2. Clique em **Play** para iniciar a simulação.

---

### **Execução na Placa BitDogLab**

#### **1. Coloque em Modo Reboot**
1. Aperte o botão **BOOTSEL** no microcontrolador Raspberry Pi Pico W.
2. Ao mesmo tempo, aperte o botão de **Reset**.

#### **2. Upload de Arquivo `Comunica.uf2`**
1. Abra a pasta `build` incluída no repositório.
2. Mova o arquivo `Comunica.uf2` para a placa de desenvolvimento.

#### **3. Acompanhar Execução do Programa**
1. Digite caracteres no **Serial Monitor** e veja-os no **display SSD1306**.
2. Digite números de **0 a 9** e veja os símbolos na **matriz de LEDs 5x5 WS2812** e no **display SSD1306**.
3. Pressione **Botão A** e **Botão B** para alternar os LEDs RGB.
4. Monitore o **Serial Monitor** para visualizar as mensagens informativas, assim o **display SSD1306** para mensagens de estado dos LEDs.

---

## 📽️ Vídeo de Demonstração

[Assista ao vídeo explicativo aqui!](https://youtu.be/K4VpBxCfF8g)

---

## ✉️ Contato
Caso tenha dúvidas ou sugestões, entre em contato com o desenvolvedor.

