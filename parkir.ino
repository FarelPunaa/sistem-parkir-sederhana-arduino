#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Definisi objek
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD dan ukuran 16x2

// Pin definisi
const int trigPin = 2;
const int echoPin = 3;
const int ledRed = 4;
const int ledGreen = 5;

// Variabel
long duration;
int distance;

void setup() {
  servo.attach(8);          // Pin kontrol servo
  lcd.init();               // Inisialisasi LCD
  lcd.backlight();          // Nyalakan lampu latar LCD
  Serial.begin(9600);      // Mulai komunikasi serial

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void loop() {
  // Kirim pulsa ke sensor ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca jarak dari sensor
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2;

  // Debug Print untuk Sensor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Kontrol pintu berdasarkan jarak
  if (distance > 10) { // Kendaraan terdeteksi (jarak kurang dari 10 cm)
    servo.write(90); // Buka pintu
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Selamat Datang");

  } else { // Tidak ada kendaraan (jarak lebih dari atau sama dengan 10 cm)
    servo.write(0); // Tutup pintu
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Silahkan Masuk");
  }

  delay(2000); // Penundaan untuk mencegah pembacaan terlalu cepat
}
