#include <BluetoothSerial.h>

// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int motor2Pin1 = 16; 
int motor2Pin2 = 17; 
int motor2Pwm = 4;
int motor1Pwm = 14;

const int freq = 10000;
const int pwmChannel = 0;
const int pwmChannel2 = 1;

const int resolution = 8;
int dutyCycle = 50;
// Setting PWM properties

BluetoothSerial SerialBT;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  pinMode(motor2Pwm, OUTPUT);
  pinMode(motor1Pwm, OUTPUT);

  ledcSetup(motor2Pwm, freq, resolution);
  ledcSetup(motor1Pwm, freq, resolution);

  ledcAttachPin(motor2Pwm, pwmChannel2);
  ledcAttachPin(motor1Pwm, pwmChannel);


  Serial.begin(115200);
  SerialBT.begin("YourBluetoothName");  // Define o nome do dispositivo Bluetooth
  SerialBT.println("Testing DC Motor...");

  // Inicializar motores em estado neutro
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void loop() {
  ledcWrite(pwmChannel, dutyCycle);   
  if (SerialBT.available()) {
    char command = SerialBT.read();
    processCommand(command);
  }
}

void processCommand(char command) {
  // Implemente aqui a lógica para controlar os motores com base no comando recebido
  switch (command) {
    case 'F':  // Frente
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      break;
    case 'B':  // Ré
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      break;
    case 'L':  // Esquerda

      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);

      delay(3000);
      
      digitalWrite(motor1Pin2, LOW);
      break;
    case 'R':  // Direita

      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);

      delay(3000);
      
      digitalWrite(motor2Pin2, LOW);
      
      // Implemente a lógica de giro à direita
      break;
    case 'S':  // Parar
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      break;

    case 'T':  // Test PWM
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      
      for (int i = 0; i <= 1024; i++) {
        analogWrite(motor1Pwm, i); // speed up
        analogWrite(motor2Pwm, i);
        delay(100);  // Delay for a smoother transition
      }

      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      
      break;
    default:
      break;
  }
}
