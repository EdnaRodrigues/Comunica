Comunica.c

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "pico/bootrom.h"

//Arquivo .pio
#include "matriz.pio.h"

//Número de LEDs
#define NUM_PIXELS 25

//Pinos de saída
#define matriz_pin 7
#define green_pin 11
#define blue_pin 12

//Pinos de entrada
#define button_A 5
#define button_B 6
#define button_Joy 22

//Variáveis Globais para permitir a função de saída da matriz de LEDs
PIO pio;
uint sm;
double r = 0, b = 0, g = 1;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

double numeros[10][25] = {
    { // Número 0
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    },
    { // Número 1
        0, 0, 1, 0, 0,
        0, 0, 1, 1, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0
    },
    { // Número 2
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    },
    { // Número 3
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1
    },
    { // Número 4
        1, 0, 0, 1, 0,
        0, 1, 0, 0, 1,
        1, 1, 1, 1, 1,
        0, 1, 0, 0, 0,
        0, 0, 0, 1, 0
    },
    { // Número 5
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1
    },
    { // Número 6
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    },
    { // Número 7
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 0, 0
    },
    { // Número 8
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    },
    { // Número 9
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1
    }
};

uint32_t matrix_rgb (double r, double g, double b) {
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void desenho (int n) {
    uint32_t valor_led;
    double *desenho = numeros[n];// Obtém o vetor de 25 elementos do número desejado

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(r*desenho[24-i], g*desenho[24-i], b*desenho[24-i]); // LED apagado para os espaços vazios
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

//Rotinas de Interrupção
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if (current_time - last_time > 200000) { //Apenas ativa as funções quando o intervalo entre acionamentos é superior a 0.2 segundos
        last_time = current_time; //Atualiza o tempo do último evento

        if (gpio == button_A) {
            gpio_put(green_pin, !gpio_get(green_pin));
            // Registrar o estado do LED no display SSD1306
            printf("LED Verde %s\n", gpio_get(green_pin)? "ligado." : "desligado."); // Imprime na saída serial o estado atual do LED Verde ("ligado" ou "desligado").
            // Texto descritivo da operação enviado ao Serial Monitor
        } else if (gpio == button_B) {
            gpio_put(blue_pin, !gpio_get(blue_pin));
            // Registrar o estado do LED no display SSD1306
            printf("LED Azul %s\n", gpio_get(blue_pin)? "ligado." : "desligado."); // Imprime na saída serial o estado atual do LED Verde ("ligado" ou "desligado").
            // Texto descritivo da operação enviado ao Serial Monitor
        } else if (gpio == button_Joy) {
            reset_usb_boot(0,0); //Habilita o modo de gravação do microcontrolador
        } else {
            // Não faz nada
        }   
    }
}

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 14
#define I2C_SCL 15


int main() {
    
    // Inicializa comunicação USB CDC para monitor serial
    stdio_init_all(); 

    // Váriáveis utilizadas na main()
    pio = pio0;

    //Coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    set_sys_clock_khz(128000, false);

    //Configurações da PIO
    uint offset = pio_add_program(pio, &matriz_program);
    sm = pio_claim_unused_sm(pio, true);
    matriz_program_init(pio, sm, offset, matriz_pin);
    
    // Inicializa os pinos dos LEDs como saída
    gpio_init(green_pin);
    gpio_set_dir(green_pin, GPIO_OUT);
    gpio_init(blue_pin);
    gpio_set_dir(blue_pin, GPIO_OUT);
    
    //Inicializa os botões de interrupção
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN);
    gpio_pull_up(button_A);
    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN);
    gpio_pull_up(button_B);
    gpio_init(button_Joy);
    gpio_set_dir(button_Joy, GPIO_IN);
    gpio_pull_up(button_Joy);

    //Interrupções da gpio habilitadas
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, & gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, true, & gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_Joy, GPIO_IRQ_EDGE_FALL, true, & gpio_irq_handler);

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    desenho (0);

    printf("RP2040 inicializado.\n"); // Imprimir mensagem inicial ao usuário;

    while (true) {
        if (stdio_usb_connected()) { // Certifica-se de que o USB está conectado
            char c;
            if (scanf("%c", &c)== 1) {
            // Lê caractere apenas quando é detectada uma entrada
            printf("Recebido: '%c'\n", c);
            }
            // Exibição do caractere no display SSD1306 ou na matriz de LED quando for um número
        }
        sleep_ms(10);
    }
}
