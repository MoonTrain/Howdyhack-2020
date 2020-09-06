#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>


//Access Point details
const char* ssid = "SpyRover";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

//Ip details
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

//Init server
WebServer server(80);

//Initialize led for testing
uint8_t LED_BUILTIN = 4;
bool LED_BUILTIN_STATUS = LOW;


// Select camera model
#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

//const char* ssid = "LAPTOP-JHQHEPNG 0277";
//const char* password = "4A184p5@";

void startCameraServer();

void setup() {
  //init serial
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  pinMode(LED_BUILTIN, OUTPUT);

  //Print info
  Serial.println();
  Serial.print("ssid= ");
  Serial.println(ssid);
  Serial.print("password= ");
  Serial.println(password);

//  //Do weird esoteric pin setup
//  camera_config_t config;
//  config.ledc_channel = LEDC_CHANNEL_0;
//  config.ledc_timer = LEDC_TIMER_0;
//  config.pin_d0 = Y2_GPIO_NUM;
//  config.pin_d1 = Y3_GPIO_NUM;
//  config.pin_d2 = Y4_GPIO_NUM;
//  config.pin_d3 = Y5_GPIO_NUM;
//  config.pin_d4 = Y6_GPIO_NUM;
//  config.pin_d5 = Y7_GPIO_NUM;
//  config.pin_d6 = Y8_GPIO_NUM;
//  config.pin_d7 = Y9_GPIO_NUM;
//  config.pin_xclk = XCLK_GPIO_NUM;
//  config.pin_pclk = PCLK_GPIO_NUM;
//  config.pin_vsync = VSYNC_GPIO_NUM;
//  config.pin_href = HREF_GPIO_NUM;
//  config.pin_sscb_sda = SIOD_GPIO_NUM;
//  config.pin_sscb_scl = SIOC_GPIO_NUM;
//  config.pin_pwdn = PWDN_GPIO_NUM;
//  config.pin_reset = RESET_GPIO_NUM;
//  config.xclk_freq_hz = 20000000;
//  config.pixel_format = PIXFORMAT_JPEG;
//
//
//  //init with high specs to pre-allocate larger buffers
//  if(psramFound()){
//    config.frame_size = FRAMESIZE_UXGA;
//    config.jpeg_quality = 10;
//    config.fb_count = 2;
//  } else {
//    config.frame_size = FRAMESIZE_SVGA;
//    config.jpeg_quality = 12;
//    config.fb_count = 1;
//  }
//
//
//  // camera init
//  esp_err_t err = esp_camera_init(&config);
//  if (err != ESP_OK) {
//    Serial.printf("Camera init failed with error 0x%x", err);
//    return;
//  }
//
//  sensor_t * s = esp_camera_sensor_get();
//  //initial sensors are flipped vertically and colors are a bit saturated
//  if (s->id.PID == OV3660_PID) {
//    s->set_vflip(s, 1);//flip it back
//    s->set_brightness(s, 1);//up the blightness just a bit
//    s->set_saturation(s, -2);//lower the saturation
//  }
//  //drop down frame size for higher initial frame rate
//  s->set_framesize(s, FRAMESIZE_QVGA);

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
  Serial.println("HTTP server started");

  // startCameraServer();
}

void loop() {
  server.handleClient();

  digitalWrite(LED_BUILTIN, LED_BUILTIN_STATUS);

  // put your main code here, to run repeatedly:
  delay(100);
}

void handle_onConnect() {
  server.send(200, "text/html", BasicReply("No motion")); 
}

void handle_forward() {
  server.send(200, "text/html", BasicReply("forward")); 
}

void handle_backward() {
  server.send(200, "text/html", BasicReply("backward"));  
}

void handle_left() {
  server.send(200, "text/html", BasicReply("left")); 
}

void handle_right() {
  server.send(200, "text/html", BasicReply("right")); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String BasicReply(String inputStr){
  String htmlOut = "<!DOCTYPE html> <html>\n";
  htmlOut += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  htmlOut += "<title>Spy Rover</title>\n";
  htmlOut += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  htmlOut += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  htmlOut += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  htmlOut += "</style>\n";
  htmlOut += "</head>\n";
  htmlOut += "Spy Rover Online/n";
  htmlOut += "<body>\n";
  htmlOut += inputStr + "/n";
  htmlOut += "<body>\n";
  htmlOut += "</html>\n";
  return htmlOut;
}
