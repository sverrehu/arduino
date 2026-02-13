#include <stdint.h>
#include <string.h>
#include <avr/io.h>

/* Arduino Uno GPIO pin 7 is PD7, pin 8 is PB0 */
/* as seen on https://docs.arduino.cc/resources/pinouts/A000066-full-pinout.pdf */
#define LED_PIN PB0
#define LED_DDR DDRB
#define LED_OUT PORTB  /* output: PORTx */
#define LED_MASK (1 << (LED_PIN))

#define BUTTON_PIN PD7
#define BUTTON_DDR DDRD
#define BUTTON_IN PIND /* input: PINx */
#define BUTTON_MASK (1 << (BUTTON_PIN))

#define F_CPU 16000000L /* clock frequency */
#define USART_BPS 9600
#define USART_BPS_SCALED (F_CPU / (16L * USART_BPS) - 1)

#define MAX_INPUT_CHARS 80

static char input[MAX_INPUT_CHARS];
static int input_index = 0;

static void init_usart(void) {
    /* see http://www.rjhcoding.com/avrc-uart.php */
    UBRR0L = (uint8_t) (USART_BPS_SCALED & 0xFF);
    UBRR0H = (uint8_t) (USART_BPS_SCALED >> 8);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

static void write_usart(const char *s) {
    while (*s) {
        do {
        } while(!(UCSR0A & (1 << UDRE0)));
        UDR0 = *s++;
    }
}

static void init_ports(void) {
    LED_DDR |= LED_MASK;
    BUTTON_DDR &= ~BUTTON_MASK;
}

static bool is_button_pressed(void) {
    return BUTTON_IN & BUTTON_MASK;
}

static void set_led_lit(const bool is_on) {
    if (is_on) {
        LED_OUT |= LED_MASK;
    } else {
        LED_OUT &= ~LED_MASK;
    }
}

static void handle_input(void) {
    if (strcmp(input, "ON") == 0) {
        set_led_lit(true);
    } else if (strcmp(input, "OFF") == 0) {
        set_led_lit(false);
    }
}

static bool is_eol(const char c) {
    return c == '\r' || c == '\n';
}

static void read_usart(void) {
    if (!(UCSR0A & (1 << RXC0))) {
        return;
    }
    const char c = UDR0;
    input[input_index++] = c;
    if (is_eol(c) || input_index == sizeof(input) - 1) {
        if (is_eol(c)) {
            --input_index; /* don't include end of line char */
        }
        input[input_index] = '\0';
        if (input_index > 0) {
            handle_input();
        }
        input_index = 0;
    }
}

int main(void) {
    init_usart();
    init_ports();
    write_usart("Starting...\r\n");
    for (;;) {
        if (is_button_pressed()) {
            write_usart("Button Pressed!\r\n");
        }
        read_usart();
    }
}
