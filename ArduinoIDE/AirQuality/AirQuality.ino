#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h> 

#define DHTPIN D7
#define DHTTYPE DHT22
#define CONTROL_PIN_A 5  
#define CONTROL_PIN_B 4  
#define CONTROL_PIN_C 0  
#define ANALOG_PIN A0    
DHT dht22(DHTPIN, DHTTYPE);


String URL = "http://192.168.64.70/airquality_project/airquality_data.php";

const char* ssid = "Galaxy A13 5G 0730";
const char* password = "lift1239";

float temperature = 0;
float humidity = 0;
int mq135 = 0;
int mq7 = 0;

void setup() {
  Serial.begin(115200);

  dht22.begin();

  connectWiFI();

  pinMode(CONTROL_PIN_A, OUTPUT);
  pinMode(CONTROL_PIN_B, OUTPUT);
  pinMode(CONTROL_PIN_C, OUTPUT);
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    connectWiFI();
  }

  Load_DHT22_Data();
  Load_Mq135_and_Mq7_Data();
  String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity) + "&mq135=" + String(mq135) + "&mq7=" + String(mq7);

  WiFiClient client;
  HTTPClient http;
  http.begin(client, URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData);
  String payload = http.getString();
  

  Serial.print("URL: "); Serial.println(URL);
  Serial.print("Data: "); Serial.println(postData);
  Serial.print("httpCode: "); Serial.println(httpCode);
  Serial.print("payload: "); Serial.println(payload);
  Serial.println("-----------------------------------------");

  delay(10000);
}

void connectWiFI() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected to: ");Serial.println(ssid);
  Serial.println("IP address: ");Serial.println(WiFi.localIP());
}

void Load_DHT22_Data() {
  temperature = dht22.readTemperature();
  humidity = dht22.readHumidity();

  if(isnan(temperature) || isnan(humidity)) {
    Serial.println("Faild to read from DHT sensor");
    temperature = 0;
    humidity = 0;
  }
  Serial.printf("Temperature: %f °C\n", temperature);
  Serial.printf("Humidity: %f %%\n", humidity);
}

void selectMuxChannel(int channel) {
  // Set the control pins according to the channel number
  digitalWrite(CONTROL_PIN_A, (channel >> 0) & 0x01);
  digitalWrite(CONTROL_PIN_B, (channel >> 1) & 0x01);
  digitalWrite(CONTROL_PIN_C, (channel >> 2) & 0x01);
}

void Load_Mq135_and_Mq7_Data(){
    // Select channel 4 on the CD4051 (13th pin, connected to MQ135)
  selectMuxChannel(4);
  delay(10); // Small delay to allow the signal to stabilize
  mq135 = analogRead(ANALOG_PIN);
  
  // Select channel 5 on the CD4051 (14th pin, connected to MQ7)
  selectMuxChannel(5);
  delay(10); // Small delay to allow the signal to stabilize
  mq7 = analogRead(ANALOG_PIN);

  // Print the sensor values to the serial monitor
  Serial.printf("MQ-135: %d & MQ-7: %d\n", mq135, mq7);
}
