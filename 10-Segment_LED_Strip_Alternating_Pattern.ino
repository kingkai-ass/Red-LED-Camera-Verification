// Pin configuration for the 10-segment LED strip
int ledPins[] = {27, 25, 33, 21, 26, 23, 22, 12, 19, 13};

void setup() {
    // Initialize all pins as outputs
    for (int i = 0; i < 10; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
}

void loop() {
    // Example: Turn on LEDs 1, 3, 5, 7, 9 (odd segments)
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            digitalWrite(ledPins[i], LOW);  // Turn off even segments
        } else {
            digitalWrite(ledPins[i], HIGH); // Turn on odd segments
        }
    }
    delay(3000); // Keep this pattern for 3 seconds

    // Example: Turn on LEDs 2, 4, 6, 8, 10 (even segments)
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            digitalWrite(ledPins[i], HIGH); // Turn on even segments
        } else {
            digitalWrite(ledPins[i], LOW);  // Turn off odd segments
        }
    }
    delay(3000); // Keep this pattern for 3 seconds
}
