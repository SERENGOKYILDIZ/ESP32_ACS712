////////////////////////////////////////////////////////////////////////////////////////////
// ACS712 ile akım ölçümü yapan Arduino kodu (30A modeli)
const int analogPin = 39; // ACS712'nin bağlı olduğu analog pin
const float sensitivity = 0.066; // ACS712 30A modeli için hassasiyet (mV/A)
const float offsetVoltage = 2.30; // ACS712'nin sıfır akımda çıkardığı voltaj

int R1 = 1; //k ohm
int R2 = 2; //k ohm
int count_current = 0;
int32_t total_current;
float CURRENT;
////////////////////////////////////////////////////////////////////////////////////////////
void Read_Current()
{
  int analogValue = analogRead(analogPin); // Analog değeri oku
  total_current+=analogValue;
 
  count_current++;
  if(count_current > 150)
  {
    float readVoltage = (float)total_current/count_current * (3.3 / 4095.0); // Voltajı hesapla
    float sensorVoltage = readVoltage * ((float)(R2+R1)/R2);
    CURRENT = (sensorVoltage - offsetVoltage) / sensitivity; // Akımı hesapla
    
    Serial.print("Reading Voltage: ");
    Serial.print(readVoltage);
    Serial.print(" V, Sensor Voltage: ");
    Serial.print(sensorVoltage);
    Serial.print(" V, Current: ");
    Serial.print(CURRENT);
    Serial.println(" A");
    total_current=0;
    count_current=0;

    
    delay(1000); // 1 saniye bekle
  }
}

void setup() {
  Serial.begin(115200); // Seri iletişimi başlat
}

void loop() {
  Read_Current();
}
