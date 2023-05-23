#define LED1_PIN 10
#define LED2_PIN 9
#define A_PIN 5
#define A_RESET_PIN 2

#define AZ_THRESH 1
#define V_THRESH 30
#define INTERVAL 50

int count = 0;

int az;
int az_normal = 945;
int az_prev = az_normal;

int velocity = 0; // 積分結果の速度
int distance = 0; // 積分結果の距離
int max = 0;
int min = 0;
bool direction = true; // true: 正方向, false: 負方向

void setup() {
    Serial.begin(9600);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(A_RESET_PIN, INPUT);
}

void loop() {
    az = analogRead(A_PIN);

    if (digitalRead(A_RESET_PIN) == HIGH) {
        az_normal = az;
        az_prev = az;
        velocity = 0;
        distance = 0;
        max = 0;
        min = 0;
        direction = true;
        Serial.print("Normal z: ");
        Serial.println(az_normal);
    }

    // TODO: タイマ割り込みで実行するようにする
    velocity += az - az_normal;
    az_prev = az;

    if (abs(az - az_normal) <= AZ_THRESH) velocity = 0;

    else {
        if      (velocity < -V_THRESH) velocity = -V_THRESH;
        else if (velocity >  V_THRESH) velocity =  V_THRESH;
        distance += velocity;

        if (direction) {
            digitalWrite(LED1_PIN, HIGH);
            digitalWrite(LED2_PIN, LOW);
            if (max < distance) max = distance;
            else {
                direction = false;
                min = distance;
            }
        }
        else {  // direction == false
            digitalWrite(LED1_PIN, LOW);
            digitalWrite(LED2_PIN, HIGH);
            if (min > distance) min = distance;
            else {
                direction = true;
                max = 0;
                az_prev = az_normal;
                velocity = 0;
                distance = 0;
                // Serial.println("Reset!");
                count++;
            }
        }

        // Serial.print("Acceleration z: ");
        // Serial.print(az);
        // Serial.print("\tVelocity: ");
        // Serial.print(velocity);
        Serial.print("\tDistance: ");
        Serial.println(distance);
    }

    delay(INTERVAL);
}
