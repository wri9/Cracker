// ---------------------------------------------------------------------------
// This example code was used to successfully communicate with 9 ultrasonic sensors. You can adjust
// the number of sensors in your project by changing SONAR_NUM and the number of NewPing objects in the
// "sonar" array. You also need to change the pins for each sensor for the NewPing objects. Each sensor
// is pinged at 33ms intervals. So, one cycle of all sensors takes 297ms (33 * 9 = 297ms). The results
// are sent to the "oneSensorCycle" function which currently just displays the distance data. Your project
// would normally process the sensor results in this function (for example, decide if a robot needs to
// turn and call the turn function). Keep in mind this example is event-driven. Your complete sketch needs
// to be written so there's no "delay" commands and the loop() cycles at faster than a 33ms rate. If other
// processes take longer than 33ms, you'll need to increase PING_INTERVAL so it doesn't get behind.
// ---------------------------------------------------------------------------
#include <ArduinoJson.h>
#include <NewPing.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>

#define SONAR_NUM     9 // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.
int check = 0;
  
char ssid[] = "Cracker";
char pass[] = "blackoxen3";  
//char ssid[] = "LeePhone";
//char pass[] = "65640329";  
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
IPAddress server(192,168,0,4);  

WiFiClient client;

String data;
StaticJsonBuffer<200> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

int index = 0;

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  NewPing(22, 23, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(24, 25, MAX_DISTANCE),
  NewPing(26, 27, MAX_DISTANCE),
  NewPing(12, 13, MAX_DISTANCE),
  NewPing(30, 31, MAX_DISTANCE),
  NewPing(32, 33, MAX_DISTANCE),
  NewPing(34, 35, MAX_DISTANCE),
  NewPing(36, 37, MAX_DISTANCE),
  NewPing(38, 39, MAX_DISTANCE),

};

void setup() {
  Serial.begin(115200);
    //while(!Serial);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:/'
    while (true);
  }
  
  connectWifi();
  // You're connected now, so print out the status
  printWifiStatus();
  
  pingTimer[0] = millis() + 75;  // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {  
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) {
        oneSensorCycle();
      }// Sensor ping cycle complete, do something with the results.
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
  
  // Other code that *DOESN'T* analyze ping results can go here.
}

void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  root["i"] = index;
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    data ="";
    Serial.print(cm[i]);
    Serial.print("\t");
    //Serial.print("cm \t");
    //data = "s" + i;
    //root[data] = cm[i];
  }
  root["s0"] = cm[0];
  root["s1"] = cm[1];
  root["s2"] = cm[2];
  root["s3"] = cm[3];
  root["s4"] = cm[4];
  root["s5"] = cm[5];
  root["s6"] = cm[6];
  root["s7"] = cm[7];
  root["s8"] = cm[8];
  
  //Serial.println(data);
  root.printTo(Serial);
  index++;
  postData();
  Serial.println();
}


void connectWifi() {
  // Attempt to connect to wifi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // Wait 10 seconds for connection
    delay(10000);
  }
}

void printWifiStatus() {
  // Print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}



// This method makes a HTTP connection to the server and POSTs data
void postData() {
  // If there's a successful connection, send the HTTP POST request
  if (client.connect(server, 80)) {
    Serial.println("connecting...");

    // EDIT: The POST 'URL' to the location of your insert_mysql.php on your web-host
    client.println("POST /add.php HTTP/1.1");
    client.println("Host: 192.168.0.4");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(root.measureLength());
    //client.println(data.length());
    client.println();
    //client.println(data); 
    root.printTo(client);
    //jsonBuffer = StaticJsonBuffer<200>();
    //JsonObject& root = jsonBuffer.createObject();

    delay(2000);    
    client.flush();
    client.stop();
  } 
  else {
    // If you couldn't make a connection:
    Serial.println("Connection failed");
    Serial.println("Disconnecting.");
    client.stop();
  }
}
