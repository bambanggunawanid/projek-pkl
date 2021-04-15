/*
  Source Code Kelompok PKL KJFD FILKOM
  Projek Pembuatan "Maze Omniwheels Robot"
  Bambang Gunawan,Ahmad Mustafa Kamal,Adhly Hasbi
*/
/*
  Menggunakan library motor shield dari Adafruit yakni AFMotor.h
  library ini memudahkan developer dalam menginisiasikan pin pada driver
  alasan kuat dari penggunaan library ini terletak pada posisi pin dari driver
  developer harus membaca dokumentasi driver dan mendefinisikan setiap pin pada Arduino
  dengan menggunakan library kita tinggal memanggil class yang sudah dibuat oleh tim Adafruit
*/
#include <Arduino.h>
#include <AFMotor.h>

/*
  Pin dari sensor ultrasonik berada pada pin analog A0-A5
  penomoran pada pin mengacu pada penomoran sensor secara fisik
*/
#define trigPin1 A0
#define echoPin1 A1
#define trigPin2 A2
#define echoPin2 A3
#define trigPin3 A4
#define echoPin3 A5

/*
  Deklarasi variabel global
  untuk memudahkan perhitungan
  dan distribusi variabel dinamis
*/
long duration, distance, FIRSTSensor, SECONDSensor, THIRDSensor;
char command;
bool ultraOn = false;

/*
  Inisiasi objek motor dc
  menggunakan class AF_DCMotor
  menyesuaikan desain arsitektur robot
*/
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);

/*
  Fungsi SonarSensor() ini sebagai "working function sensor"-nya ultrasonik
  cara kerjanya, pertama trigger di clear terlebih dahulu selama 2 mikrosekon
  kemudian trigger high untuk memancarkan gelombang ultrasonik selama 10 mikrosekon
  lalu pulseIn() akan memerintahkan sistem untuk menunggu hingga pin Echo bernilai HIGH.
  Lamanya proses menunggu akan dianggap atau dihitung sebagai durasi pengiriman + penerimaan
  pada sinyal echo yang dipantulkan oleh benda. Proses ini kemudian disimpan pada variabel duration.
  Output dari sensor tidaklah akurat maka dari itu digunakan kalibrasi perhitungan pada baris kode ke 64
*/
long SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return distance = (duration / 2) / 29.1;
}

/*
  Nilai PWM adalah 0 hingga 255, semakin besar nilai bit maka akan semakin
  besar nilai duty cyclenya dan karena duty cyclenya semakin besar maka voltase
  akan semakin besar yang membuat motor dc bergerak semakin cepat hingga maksimum 255
*/
/*
  Fungsi forward() untuk membuat robot bergerak jalan maju ke depan
  parameter pada fungsi setSpeed() adalah nilai PWM yang kita inginkan
*/
void forward()
{
  motor1.setSpeed(240); // Inisiasi kecepatan maksimum untuk motor 1 sebesar 100% duty cycle
  motor1.run(FORWARD);  // Motor berputar searah jarum jam
  motor2.setSpeed(240); // Inisiasi kecepatan maksimum untuk motor 2 sebesar 100% duty cycle
  motor2.run(FORWARD);  // Motor berputar searah jarum jam
  motor3.setSpeed(0);   // Inisiasi kecepatan minimum untuk motor 3 sebesar 0% duty cycle
  motor3.run(FORWARD);  // Motor berputar searah jarum jam
}

/*
  Fungsi backward() untuk membuat robot bergerak jalan mundur
*/
void backward()
{
  motor1.setSpeed(240); // Inisiasi kecepatan maksimum untuk motor 1 sebesar 100% duty cycle
  motor1.run(BACKWARD); // Motor berputar melawan jarum jam
  motor2.setSpeed(240); // Inisiasi kecepatan maksimum untuk motor 2 sebesar 100% duty cycle
  motor2.run(BACKWARD); // Motor berputar melawan jarum jam
  motor3.setSpeed(0);   // Inisiasi kecepatan minimum untuk motor 3 sebesar 0% duty cycle
  motor3.run(BACKWARD); // Motor berputar melawan jarum jam
}

/*
  Fungsi left() untuk membuat robot bergerak jalan ke kiri
*/
void left()
{
  motor1.setSpeed(90);  // Inisiasi kecepatan motor 1 sebesar 37% duty cycle
  motor1.run(BACKWARD); // Motor berputar melawan jarum jam
  motor2.setSpeed(90);  // Inisiasi kecepatan motor 2 sebesar 37% duty cycle
  motor2.run(FORWARD);  // Motor berputar searah jarum jam
  motor3.setSpeed(240); // Inisiasi kecepatan motor 3 sebesar 75% duty cycle
  motor3.run(FORWARD);  // Motor berputar searah jarum jam
}

/*
  Fungsi obliqueLeft() untuk membuat robot bergerak jalan ke pojok kiri
*/
void obliqueLeft()
{
  motor1.setSpeed(0);   // Inisiasi kecepatan motor 1 sebesar 37% duty cycle
  motor1.run(BACKWARD); // Motor berputar melawan jarum jam
  motor2.setSpeed(195); // Inisiasi kecepatan motor 2 sebesar 37% duty cycle
  motor2.run(FORWARD);  // Motor berputar searah jarum jam
  motor3.setSpeed(195); // Inisiasi kecepatan motor 3 sebesar 75% duty cycle
  motor3.run(FORWARD);  // Motor berputar searah jarum jam
}

/*
  Fungsi right() untuk membuat robot bergerak jalan ke kanan
*/
void right()
{
  motor1.setSpeed(90);  // Inisiasi kecepatan motor 1 sebesar 37% duty cycle
  motor1.run(FORWARD);  // Motor berputar searah jarum jam
  motor2.setSpeed(90);  // Inisiasi kecepatan motor 2 sebesar 41% duty cycle
  motor2.run(BACKWARD); // Motor berputar melawan jarum jam
  motor3.setSpeed(240); // Inisiasi kecepatan motor 3 sebesar 75% duty cycle
  motor3.run(BACKWARD); // Motor berputar melawan jarum jam
}

/*
  Fungsi obliqueRight() untuk membuat robot bergerak jalan ke pojok kanan
*/
void obliqueRight()
{
  motor1.setSpeed(195); // Inisiasi kecepatan motor 1 sebesar 37% duty cycle
  motor1.run(FORWARD);  // Motor berputar searah jarum jam
  motor2.setSpeed(0);   // Inisiasi kecepatan motor 2 sebesar 41% duty cycle
  motor2.run(BACKWARD); // Motor berputar melawan jarum jam
  motor3.setSpeed(195); // Inisiasi kecepatan motor 3 sebesar 75% duty cycle
  motor3.run(BACKWARD); // Motor berputar melawan jarum jam
}

/*
  Fungsi spin() untuk membuat robot bergerak berputar 360 derajat searah jarum jam
*/
void spin()
{
  motor1.setSpeed(255); // Inisiasi kecepatan motor 1 sebesar 100% duty cycle
  motor1.run(FORWARD);  // Motor berputar searah jarum jam
  motor2.setSpeed(255); // Inisiasi kecepatan motor 2 sebesar 100% duty cycle
  motor2.run(BACKWARD); // Motor berputar melawan jarum jam
  motor3.setSpeed(255); // Inisiasi kecepatan motor 3 sebesar 100% duty cycle
  motor3.run(FORWARD);  // Motor berputar searah jarum jam
}

/*
  Fungsi backspin() untuk membuat robot bergerak berputar 360 derajat melawan jarum jam
*/
void backspin()
{
  motor1.setSpeed(255); // Inisiasi kecepatan motor 1 sebesar 100% duty cycle
  motor1.run(BACKWARD); // Motor berputar melawan jarum jam
  motor2.setSpeed(255); // Inisiasi kecepatan motor 2 sebesar 100% duty cycle
  motor2.run(FORWARD);  // Motor berputar searah jarum jam
  motor3.setSpeed(255); // Inisiasi kecepatan motor 3 sebesar 100% duty cycle
  motor3.run(BACKWARD); // Motor berputar melawan jarum jam
}

/*
  Fungsi Stop() untuk membuat robot berhenti bergerak
  fungsi ini digunakan ketika kondisi dari sensor tidak
  terpenuhi atau saat tombol tidak sedang ditekan atau dilepas
*/
void Stop()
{
  // stop the motor when release the button
  motor1.run(RELEASE); // Menghentikan motor dc atau setara dengan setSpeed 0
  motor2.run(RELEASE); // Menghentikan motor dc atau setara dengan setSpeed 0
  motor3.run(RELEASE); // Menghentikan motor dc atau setara dengan setSpeed 0
}

/*
  Fungsi ini yang akan dijalankan pertama kali
  untuk itu dilakukan deklarasi komunikasi serial
  dan deklarasi pinMode pada setiap sensor di arduino
*/
void setup()
{
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  Stop();
}

/*
  Fungsi ini adalah fungsi yang akan terus dijalankan. Semua proses yang ada di dalam
  fungsi loop akan selalu diulang tanpa henti (forever loop) sehingga sistem selalu aktif.
*/
void loop()
{
  // Ketika Bluetooth terdeteksi connect
  if (Serial.available() > 0)
  {
    // Baca isi command dari bluetooth
    command = Serial.read();
    // Lalu cetak isi command ke dalam Serial monitor
    Serial.print(command);

    /*
  Fungsi ini adalah fungsi yang akan terus dijalankan. Semua proses yang ada di dalam
  fungsi loop akan selalu diulang tanpa henti (forever loop) sehingga sistem selalu aktif.
*/
    if (ultraOn == false)
    {
      switch (command)
      {
      case 'F':
        forward();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'B':
        backward();
        break;
      case 'I':
        obliqueRight();
        break;
      case 'G':
        obliqueLeft();
        break;
      case 'H':
        backspin();
        break;
      case 'J':
        spin();
        break;
      case 'V':
        ultraOn = true;
        break;
      case 'v':
        ultraOn = false;
        break;
      default:
        Stop();
        break;
      }
    }
  }

  if (ultraOn == true)
  {
    SonarSensor(trigPin1, echoPin1);
    FIRSTSensor = distance;
    SonarSensor(trigPin2, echoPin2);
    SECONDSensor = distance;
    SonarSensor(trigPin3, echoPin3);
    THIRDSensor = distance;

    // Robot akan berjalan jika sensor 3 tidak ada halangan sejauh 14 cm
    if (THIRDSensor > 14)
    {
      // Jika sensor 2 mendeteksi tembok lebih dari 0 hingga 8 cm maka
      if (SECONDSensor<8 & SECONDSensor> 0)
      {
        left();
        delay(150);
      }
      // Jika sensor 1 mendeteksi tembok lebih dari 0 hingga 8 cm maka
      else if ((FIRSTSensor<8 & FIRSTSensor> 0) && (SECONDSensor<8 & SECONDSensor> 0))
      {
        right();
        delay(150);
      }
      forward();
    }
    else if (THIRDSensor < 14)
    {
      // Jika terdapat halangan sejauh 14 cm maka robot berhenti
      Stop();
    }
  }
  if (command == 'v')
    ultraOn = false;
}
