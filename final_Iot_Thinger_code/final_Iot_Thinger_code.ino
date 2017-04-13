
#include <ESP8266WiFi.h>

#include <ThingerESP8266.h>



#define DEBUG true

#define USERNAME "....."
#define DEVICE_ID "....."
#define DEVICE_CREDENTIAL "....."

#define SSID "...."
#define SSID_PASSWORD "........"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);


String getTime() {
  WiFiClient client;
  while (!!!client.connect("google.com", 80)) {
    Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");
 
  while(!!!client.available()) {
     yield();
  }

  while(client.available()){
    if (client.read() == '\n') {    
      if (client.read() == 'D') {    
        if (client.read() == 'a') {    
          if (client.read() == 't') {    
            if (client.read() == 'e') {    
              if (client.read() == ':') {    
                client.read();
                String theDate = client.readStringUntil('\r');
                client.stop();
                return theDate;
              }
            }
          }
        }
      }
    }
  }
}

String convertTime(){
  

}
void setup() {
  Serial.begin(115200);

  pinMode(00, OUTPUT);
  pinMode(02, OUTPUT);
  pinMode(04, OUTPUT);
  pinMode(05, OUTPUT);
  pinMode(13, OUTPUT);

   int a=0;
  
  thing.add_wifi(SSID, SSID_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(13, HIGH);
    Serial.println("WiFi connectedddddddddddddddddddddddddddddddddddddddddddddd");
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
  }
  digitalWrite(13, HIGH);

  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());



  //thing["led1"] << digitalPin(00);
  //thing["led2"] << invertedDigitalPin(02);
  //thing["led3"] << digitalPin(04);
  //thing["led4"] << digitalPin(05);
  
    thing["Light One"] << [](pson& in){
    digitalWrite(00,  in ? LOW:HIGH);
    int n1=in?1:0;
    Serial.println(n1);
    Serial.println("one");
    pson tweet_content;
      if(n1==1){ 
        tweet_content["value2"] ="ON"; 
      }else{
        tweet_content["value2"] ="OFF";
      }
      tweet_content["value1"] = "One";
      tweet_content["value3"] = getTime();
      
      thing.call_endpoint("lightup", tweet_content);
      
    };
    thing["Light Two"] << [](pson& in){
    digitalWrite(02, in ? LOW:HIGH);
    int n2=in?1:0;
    Serial.println(n2);
    Serial.println("Two");
    pson tweet_content;
    if(n2==1){ 
        tweet_content["value2"] ="ON"; 
      }else{
        tweet_content["value2"] ="OFF";
      }
      tweet_content["value1"] = "Two";
      tweet_content["value3"] = getTime();
      thing.call_endpoint("lightup", tweet_content);

    };
    thing["Light Three"] << [](pson& in){
    digitalWrite(04,in ? LOW:HIGH);
    int n3=in?1:0;
    Serial.println(n3);
    Serial.println("Three");
    pson tweet_content;
    if(n3==1){ 
        tweet_content["value2"] ="ON"; 
      }else{
        tweet_content["value2"] ="OFF";
      }
      tweet_content["value1"] = "Three";
      tweet_content["value3"] = getTime();
      thing.call_endpoint("lightup", tweet_content);
    
    };
    thing["Light Four"] << [](pson& in){
    digitalWrite(05, in ? LOW:HIGH);
    int n4=in?1:0;
    Serial.println(n4);
    Serial.println("Four");
    pson tweet_content;
    if(n4==1){ 
        tweet_content["value2"] ="ON"; 
      }else{
        tweet_content["value2"] ="OFF";
      }
      tweet_content["value1"] = "Four";
      tweet_content["value3"] = getTime();
      thing.call_endpoint("lightup", tweet_content);

    };

  thing["millis"] >> outputValue(millis());
}

void loop() {
  thing.handle();
  //Serial.println(getTime());
}




