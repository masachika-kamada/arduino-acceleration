#define LED_PIN 10
#define THRESHOLD 950 // 値の変動を考慮して、余裕を持たせる
#define NORMAL_Z 945

bool isExercising = false; // exercise flag
int exerciseCount = 0;     // count of exercises

void setup()
{
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT); // Set the LED pin as output
}

void loop()
{
    long x, y, z;
    x = y = z = 0;
    x = analogRead(3); // X軸
    y = analogRead(4); // Y軸
    z = analogRead(5); // Z軸

    if (z > THRESHOLD && !isExercising)
    {
        // When the z value goes up beyond the threshold
        digitalWrite(LED_PIN, HIGH); // Turn on the LED
        isExercising = true;
    }
    else if (z <= NORMAL_Z && isExercising)
    {
        // When the z value goes back to normal
        digitalWrite(LED_PIN, LOW); // Turn off the LED
        isExercising = false;
        exerciseCount++; // Count the exercise
        Serial.print("Exercise count: ");
        Serial.println(exerciseCount);
    }

//    Serial.print("X:");
//    Serial.println(x);
//    Serial.print(" Y:");
//    Serial.println(y);
//    Serial.print(" Z:");
//    Serial.println(z);
    delay(50);
}
