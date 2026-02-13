/* simple test for Arduino IDE to check the wiring.
 * LED will be lit when the butten is pressed, unlit otherwise. */

#define LED_PIN 8
#define BUTTON_PIN 7

void setup() {
    Serial.begin(9600);
    Serial.println("Starting");
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == HIGH) {
        Serial.println("Button Pressed!");
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}
