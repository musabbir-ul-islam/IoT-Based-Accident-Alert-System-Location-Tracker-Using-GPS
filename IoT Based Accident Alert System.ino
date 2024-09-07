#include "TinyGPS++.h"
#include <HardwareSerial.h>

#include <math.h>
#include <WiFi.h>
#include <HTTPClient.h>
//--------------------------------------------------------------
#define RXD2 16
#define TXD2 17 
//--------------------------------------------------------------

byte updateflag;
int led = 2;
int vs =34; // vibration sensor
int vs2= 35;
int buz = 26;
int sw = 27;
HardwareSerial neogps(1);

TinyGPSPlus gps;// GPS object to process the NMEA data
//Used to run impact routine every 2mS.
unsigned long time1;
//--------------------------------------------------------------

const char* ssid = "Wifi_Name";
const char* password = "Wifi_Password";
String server = "http://maker.ifttt.com";
String eventName =  "help" ;       //"Accident Alert";
String IFTTT_Key = "nv1fM_u2wFxLcYN00IZta5npuexth7UCN7yLqW43ECq";
String IFTTTUrl="https://maker.ifttt.com/trigger/help/with/key/nv1fM_u2wFxLcYN00IZta5npuexth7UCN7yLqW43ECq";//"https://maker.ifttt.com/trigger/Accident Alert/with/key/nv1fM_u2wFxLcYN00IZta5npuexth7UCN7yLqW43ECq";


// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;


void setup()
{
  //--------------------------------------------------------------
  Serial.begin(115200);
      //This opens up communications to the GPS
      neogps.begin(9600,SERIAL_8N1,RXD2,TXD2);
  Serial.println("GPS Start");        //To show in the serial monitor that the sketch has started
 time1 = micros(); 
  pinMode(led, OUTPUT);
  pinMode(vs, INPUT); 
  pinMode(vs2, INPUT);
  pinMode(buz,OUTPUT);
  pinMode(sw,INPUT_PULLUP); 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
  
//---------------------------------------------
       
  //--------------------------------------------------------------
  
  
  //Serial.print("time1 = "); Serial.println(time1);
  //--------------------------------------------------------------
}
void sendDataToSheet(void)
{
float value1 = 24.36419; //gps.location.lat(); 
float value2 = 88.63;    //gps.location.lng();
int value3 = gps.altitude.feet();
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((float)value1) + "&value2="+String((float)value2) +"&value3=" + String((int)value3);  
  Serial.println(url);
  //Start to send data to IFTTT
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin(url); //HTTP

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  if(gps.location.isUpdated())          //This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.print("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.print("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude:");
    Serial.println(gps.location.lng(), 6);
    
    Serial.print("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");

    Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  
  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".GMT");
  }
  Serial.println("");

}
}


void loop()
{
   
while(neogps.available())              //While there are incoming characters  from the GPS
  {
    gps.encode(neogps.read());           //This feeds the serial NMEA data into the library one char at a time
  }
  

long measurement =vibration();
long measurement2 =vibration2();
    
    //int x = digitalRead(sw); 
  delay(50);
  Serial.println(measurement);
  Serial.println(measurement2);
  
  if (measurement > 40000 || measurement2 > 40000 ){
  
    digitalWrite(led, HIGH);
  
        
        
       
        
          
       digitalWrite (buz,HIGH);
       
       
        
      
          sendDataToSheet();
          
    
  }
  else{
    digitalWrite(led, LOW); 
    digitalWrite (buz,LOW);
  }

  //--------------------------------------------------------------
  //call impact routine every 2mS
 


  
  //--------------------------------------------------------------
  
  //--------------------------------------------------------------

}

long vibration(){
  long measurement=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
long vibration2(){
  long measurement=pulseIn (vs2, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
