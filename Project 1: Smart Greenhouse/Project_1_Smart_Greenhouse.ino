//-------------Libraries to include-------------//

#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

//-------------Pin and variable assignments-------------//

const int pirPin=26;
const int redPin=12;
const int greenPin=14;
const int bluePin=27;
#define DHTPIN 13
#define LDRPIN 16
#define buzzerPIN 25

#define DHTTYPE DHT22
int pirState = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize LCD
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT22

const float GAMMA = 0.7;
const float RL10 = 50;

String statmessage="";
String pirMotion="";
String tempValueSTR ="";
String humValueSTR ="";
String owtemperatureSTR ="";
String owhumiditySTR ="";
String luxSTR ="";


float tempValue = 0.0;
float humValue = 0.0;
float lux = 0.0;

//-------------WiFi Login-------------//

#define WLAN_SSID "Wokwi-GUEST"
#define WLAN_PASS ""

//-------------OpenWeather API Setup-------------//
String openWeatherMapApiKey = "YOUR_KEY";
String city = "San%20Antonio";
String countryCode = "US";

float owtemperature = 0.0;
float owhumidity = 0.0;

//-------------Adafruit IO Setup-------------//

#define AIO_SERVER "io.adafruit.com"

// Using port 8883 for MQTTS
#define AIO_SERVERPORT 8883

// Adafruit IO Account Configuration
// (to obtain these values, visit https://io.adafruit.com and click on Active Key)
#define AIO_USERNAME "YOUR_USERNAME"
#define AIO_KEY      "YOUR_KEY"

// WiFiFlientSecure for SSL/TLS support
WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// io.adafruit.com root CA
const char* adafruitio_root_ca = \
      "-----BEGIN CERTIFICATE-----\n"
      "MIIEjTCCA3WgAwIBAgIQDQd4KhM/xvmlcpbhMf/ReTANBgkqhkiG9w0BAQsFADBh\n"
      "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
      "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\n"
      "MjAeFw0xNzExMDIxMjIzMzdaFw0yNzExMDIxMjIzMzdaMGAxCzAJBgNVBAYTAlVT\n"
      "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
      "b20xHzAdBgNVBAMTFkdlb1RydXN0IFRMUyBSU0EgQ0EgRzEwggEiMA0GCSqGSIb3\n"
      "DQEBAQUAA4IBDwAwggEKAoIBAQC+F+jsvikKy/65LWEx/TMkCDIuWegh1Ngwvm4Q\n"
      "yISgP7oU5d79eoySG3vOhC3w/3jEMuipoH1fBtp7m0tTpsYbAhch4XA7rfuD6whU\n"
      "gajeErLVxoiWMPkC/DnUvbgi74BJmdBiuGHQSd7LwsuXpTEGG9fYXcbTVN5SATYq\n"
      "DfbexbYxTMwVJWoVb6lrBEgM3gBBqiiAiy800xu1Nq07JdCIQkBsNpFtZbIZhsDS\n"
      "fzlGWP4wEmBQ3O67c+ZXkFr2DcrXBEtHam80Gp2SNhou2U5U7UesDL/xgLK6/0d7\n"
      "6TnEVMSUVJkZ8VeZr+IUIlvoLrtjLbqugb0T3OYXW+CQU0kBAgMBAAGjggFAMIIB\n"
      "PDAdBgNVHQ4EFgQUlE/UXYvkpOKmgP792PkA76O+AlcwHwYDVR0jBBgwFoAUTiJU\n"
      "IBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQGCCsG\n"
      "AQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMDQGCCsGAQUFBwEB\n"
      "BCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQuY29tMEIGA1Ud\n"
      "HwQ7MDkwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEds\n"
      "b2JhbFJvb3RHMi5jcmwwPQYDVR0gBDYwNDAyBgRVHSAAMCowKAYIKwYBBQUHAgEW\n"
      "HGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9DUFMwDQYJKoZIhvcNAQELBQADggEB\n"
      "AIIcBDqC6cWpyGUSXAjjAcYwsK4iiGF7KweG97i1RJz1kwZhRoo6orU1JtBYnjzB\n"
      "c4+/sXmnHJk3mlPyL1xuIAt9sMeC7+vreRIF5wFBC0MCN5sbHwhNN1JzKbifNeP5\n"
      "ozpZdQFmkCo+neBiKR6HqIA+LMTMCMMuv2khGGuPHmtDze4GmEGZtYLyF8EQpa5Y\n"
      "jPuV6k2Cr/N3XxFpT3hRpt/3usU/Zb9wfKPtWpoznZ4/44c1p9rzFcZYrWkj3A+7\n"
      "TNBJE0GmP2fhXhP1D/XVfIW/h0yCJGEiV9Glm/uGOa3DXHlmbAcxSyCRraG+ZBkA\n"
      "7h4SeM6Y8l/7MBRpPCz6l8Y=\n"
      "-----END CERTIFICATE-----\n";

//-------------Adafruit IO Feeds-------------//

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
//Adafruit_MQTT_Subscribe TOGGLE = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/TOGGLE");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish light = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light");
Adafruit_MQTT_Publish motion = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/motion");
Adafruit_MQTT_Publish message = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/message");
Adafruit_MQTT_Publish openweathertemperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/openweathertemperature");
Adafruit_MQTT_Publish openweatherhumidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/openweatherhumidity");

//-------------LED Assignment-------------//

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setup() {
  // put your setup code here, to run once:

//-------------Wireless Connection-------------//

  Serial.begin(115200);
  delay(10);

  // Connect to WiFi access point.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  delay(1000);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  delay(2000);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set Adafruit IO's root CA
  client.setCACert(adafruitio_root_ca);

//-------------Pin & Component Setups-------------//
  dht.begin();
  pinMode(pirPin, INPUT);
  lcd.clear();  lcd.init(); lcd.backlight();

  pinMode(LDRPIN, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
}


void indicatorPublish() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  humValue = dht.readHumidity();
  tempValue = dht.readTemperature();
  pirState = digitalRead(pirPin);

  if (isnan(humValue) || isnan(tempValue) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  tempValueSTR = String(tempValue) + " °C";

  if (!temperature.publish(tempValueSTR.c_str())) {
    Serial.println(F("Failed"));
  } else {
    Serial.print("Temperature: ");
    Serial.println(tempValueSTR);
  }

  humValueSTR = String(humValue) + " %";

  if (!humidity.publish(humValueSTR.c_str())) {
    Serial.println(F("Failed"));
  } else {
    Serial.print("Humidity: ");
    Serial.println(humValueSTR);
  }

   if (!motion.publish(pirMotion.c_str())) {
    Serial.println(F("Failed"));
  } else {
    Serial.print("PIR: ");
    Serial.println(pirMotion);
  }

  owtemperatureSTR = String(owtemperature) + " °C";

   if (!openweathertemperature.publish(owtemperatureSTR.c_str())) {
    Serial.println(F("Failed"));
  } else {
    Serial.print("API Temperature: ");
    Serial.println(owtemperatureSTR);
  }

  owhumiditySTR = String(owhumidity) + " %";

  if (!openweatherhumidity.publish(owhumiditySTR.c_str())) {
    Serial.println(F("Failed"));
  } else {
    Serial.print("API Humidity: ");
    Serial.println(owhumiditySTR);
  }

  luxSTR = String(lux) + " lux";

  if (!light.publish(luxSTR.c_str())) {
    Serial.println(F("Failed"));
  } else {
    Serial.print("Light: ");
    Serial.println(luxSTR);
  }

  if (!message.publish(statmessage.c_str())) {
    Serial.println(F("Failed"));
  } else {
    Serial.print("Message: ");
    Serial.println(statmessage);
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {  // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1)
        ;
    }
  }
  Serial.println("MQTT Connected!");
}

void updateWeather() {

  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;

  String serverPath =
    "http://api.openweathermap.org/data/2.5/weather?q=" +
    city + "," + countryCode +
    "&units=metric&APPID=" + openWeatherMapApiKey;

  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    JSONVar myObject = JSON.parse(payload);

    if (JSON.typeof(myObject) != "undefined") {
      owtemperature = (double) myObject["main"]["temp"];
      owhumidity    = (double) myObject["main"]["humidity"];
    }
  }

  http.end();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //-------------Feed Connection & Publishing-------------//
  
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  Serial.println("Attempting OpenWeather update.");
  updateWeather();
  Serial.println("Completed OpenWeather update.");

  //-------------Logic Checks-------------//

  Serial.println("Attempting Adafruit IO update.");
  indicatorPublish();
  Serial.println("Completed Adafruit IO update.");

 if (pirState == HIGH) {
    pirMotion = "Motion Detected";
    tone(buzzerPIN, 1000); 
    delay(500);            
    noTone(buzzerPIN);    
    setColor(255, 255, 0); // Yellow
  } else {
    pirMotion = "No Motion";
    setColor(0, 255, 0); // Green
  }

  if (tempValue > 60) {
  statmessage = "Too Hot!";
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print(statmessage);
  lcd.setCursor(0,1);
  lcd.print(pirMotion);
  setColor(255, 0, 0); // Red
  } else if (tempValue < 30) {
  statmessage = "Too Cold!";
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print(statmessage);
  lcd.setCursor(0,1);
  lcd.print(pirMotion);
  setColor(255, 0, 0); // Red
  } else {
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print(pirMotion);
  }  

  int analogValue = analogRead(LDRPIN);
  float voltage = analogValue / 4095.0 * 5.0;
  if (voltage >= 5.0) voltage = 4.99; // avoid div by zero
  float resistance = 2000 * voltage / (1 - voltage / 5); // change 2000 to real resistance value
  lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

  // wait 10 seconds for subscription messages
  mqtt.processPackets(10000);

  delay(100);
}
