#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>
// #include "SoftwareSerial.h"

//Init softwareserial for printing to arduino
//SoftwareSerial sendChar;

//Access Point details
const char* ssid = "SpyRover";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

//Ip details
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

//Init server
WebServer server(80);

//Init camera
#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

#if defined(CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#else
#error "Camera model not selected"
#endif

void startCameraServer();

void setup() {
  //Config Output Pins
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(15,OUTPUT);


  //Init serial
  //sendChar.begin(9600, SWSERIAL_8N1, 4,1);

  //Camera Setup
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  
  esp_err_t err = esp_camera_init(&config); //Actually initialize
  if (err != ESP_OK) {
    // Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  //drop down frame size for higher initial frame rate
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_UXGA);





  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);


  server.on("/", handle_onConnect);
  server.on("/forward", handle_forward);
  server.on("/backward", handle_backward);
  server.on("/left", handle_left);
  server.on("/right", handle_right);
  server.onNotFound(handle_NotFound);

  server.begin();
  // Serial.println("HTTP server started");

  startCameraServer();
}

void loop() {
  server.handleClient();
}

void handle_onConnect() {
  server.send(200, "text/html", BasicReply("No motion")); 
}

void handle_forward() {
  server.send(200, "text/html", BasicReply("forward"));
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(15, HIGH);

  delay(30);

  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);
}

void handle_backward() {
  server.send(200, "text/html", BasicReply("backward")); 
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(15, LOW);

  delay(30);

  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);

}

void handle_right() {
  server.send(200, "text/html", BasicReply("right")); 
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(15, HIGH);

  delay(30);

  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);
}

void handle_left() {
  server.send(200, "text/html", BasicReply("left")); 
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);

  delay(30);

  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);

}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String BasicReply(String inputStr){
  String htmlOut = "<!DOCTYPE html> <html>\n";
  htmlOut += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  htmlOut += "This is not what you are looking for";
  // htmlOut += "<title>Spy Rover</title>\n";
  // htmlOut += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  // htmlOut += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  // htmlOut += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  // htmlOut += "</style>\n";
  // htmlOut += "</head>\n";
  // htmlOut += "Spy Rover Online\n<br>";
  // htmlOut += "<body>\n";
  // htmlOut += "<img style=\"-webkit-user-select: none;margin: auto;\" src=\"http://192.168.1.1:81/stream\" width=\"530\" height=\"397\"><br>";
  // htmlOut += inputStr + "\n";
  htmlOut += "<body>\n";
  htmlOut += "</html>\n";
  return htmlOut;
}
