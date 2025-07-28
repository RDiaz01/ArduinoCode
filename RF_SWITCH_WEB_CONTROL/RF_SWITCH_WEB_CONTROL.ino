#include <WiFiManager.h>
#include <WiFi.h>
#include <WebServer.h>
#include "index.h" //web page header ffile

#define SEL1_EN 14
#define SEL2_EN 13
#define SEL3_EN 18

#define CTL1_0  25
#define CTL1_1  26
#define CTL1_2  27

#define CTL2_0  15  //use 21 -> GPIO15
#define CTL2_1  2 //use 22 -> GPIO2
#define CTL2_2  5 //use 34 -> GPIO5

#define CTL3_0  4
#define CTL3_1  16
#define CTL3_2  17

#define COMMON  33

#define RESET_CREDENTIAL  0

int PIN_MAP[]={CTL1_0,CTL1_1,CTL1_2,
               CTL2_0,CTL2_1,CTL2_2,
               CTL3_0,CTL3_1,CTL3_2};


// Set up the server object
//ESP8266WebServer server;
WebServer  server(80);
WiFiManager wm;
//char color[8];

const char* PARAM_INPUT_1 = "input1";
char outputText[1000];

String sw1="";
String sw2="";
String sw3="";


//char* outText = "Switch 1 : All OFF<br>Switch 2 : All OFF<br>Switch 3 : All OFF<br>\0";

void setup() {

  pinMode(SEL1_EN, OUTPUT);
  pinMode(SEL2_EN, OUTPUT);
  pinMode(SEL3_EN, OUTPUT);
  
  pinMode(COMMON, OUTPUT);
  pinMode(RESET_CREDENTIAL, INPUT_PULLUP);
  digitalWrite(RESET_CREDENTIAL, HIGH);

    //Disable all muxes
  digitalWrite(SEL1_EN, HIGH);
  digitalWrite(SEL2_EN, HIGH);
  digitalWrite(SEL3_EN, HIGH);

  for(int i=0; i<9;i++){  
    pinMode(PIN_MAP[i], OUTPUT);
  }

  sw1="ALL OFF";
  sw2="ALL OFF";
  sw3="ALL OFF";
   
  // WiFi.mode(WIFI_AP);
  // WiFi.softAPConfig(ip,gateway,subnet);
  // WiFi.softAP(ssid_ap,password_ap);
  // Print IP Address as a sanity check

  WiFi.mode(WIFI_STA); 
  Serial.begin(115200);
  

  bool res;  //192.168.4.1  AP  //192.168.1.62 - 67
  res = wm.autoConnect("RFControlAP"); // anonymous ap

  if(!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  } 
  else {
    //if you get here you have connected to the WiFi    
    //Serial.println("connected...yeey :)");
    Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  }
  
  // Serial.println();
  // Serial.print("IP Address: "); Serial.println(WiFi.localIP());

  snprintf (outputText, 1000, "Switch 1 : %s<br>Switch 2 : %s<br>Switch 3 : %s<br>","ALL OFF","ALL OFF","ALL OFF");
  
  // Configure the server's routes
  server.on("/",handleUpdate); // use the top root path to report the last sensor value
  server.on("/update",handleUpdate); // use this route to update the sensor value
  server.on("/?",handleUpdate);
  server.begin();
  digitalWrite(COMMON, HIGH);
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  if(digitalRead(RESET_CREDENTIAL) == LOW){
    wm.resetSettings();
    delay(500);
  }
}
void handleRoot() {

  String html = MAIN_page;
  server.send ( 200, "text/html", html );
}

void handleUpdate() {

  if(server.arg("state"))
    selectSwitch(server.arg("state").toInt());

  handleRoot();
}
void selectSwitch(int pos){

  switch(pos){
    case 0:
      digitalWrite(SEL1_EN, HIGH);
      break;
    case 1:
      //activateSwitch(0, 1, 0, 0, 0);
      activateSwitch(0, 1, 0, 0, 1);
      break;
    case 2:
      //activateSwitch(0, 1, 0, 0, 1);
      activateSwitch(0, 1, 0, 1, 1);
      break;
    case 3:
      //activateSwitch(0, 1, 0, 1, 0);
      activateSwitch(0, 1, 1, 0, 1);
      break;
    case 4:
      //activateSwitch(0, 1, 0, 1, 1);
      activateSwitch(0, 1, 1, 1, 1);
      break;
    case 5:
      //activateSwitch(0, 1, 1, 0, 0);
      activateSwitch(0, 1, 0, 0, 0);
      break;
    case 6:
      //activateSwitch(0, 1, 1, 0, 1);
      activateSwitch(0, 1, 0, 1, 0);
      break;
    case 7:
      //activateSwitch(0, 1, 1, 1, 0);
      activateSwitch(0, 1, 1, 0, 0);
      break;
    case 8:
      //activateSwitch(0, 1, 1, 1, 1);
      activateSwitch(0, 1, 1, 1, 0);
      break;
    

    case 9:
      digitalWrite(SEL2_EN, HIGH);
      break;
    case 10:
      //activateSwitch(3, 2, 0, 0, 0);
      activateSwitch(3, 2, 0, 0, 1);
      break;
    case 11:
      //activateSwitch(3, 2, 0, 0, 1);
      activateSwitch(3, 2, 0, 1, 1);
      break;
    case 12:
      //activateSwitch(3, 2, 0, 1, 0);
      activateSwitch(3, 2, 1, 0, 1);
      break;
    case 13:
      //activateSwitch(3, 2, 0, 1, 1);
      activateSwitch(3, 2, 1, 1, 1);
      break;
    case 14:
      //activateSwitch(3, 2, 1, 0, 0);
      activateSwitch(3, 2, 0, 0, 0);
      break;
    case 15:
      //activateSwitch(3, 2, 1, 0, 1);
      activateSwitch(3, 2, 0, 1, 0);
      break;
    case 16:
      //activateSwitch(3, 2, 1, 1, 0);
      activateSwitch(3, 2, 1, 0, 0);
      break;
    case 17:
      //activateSwitch(3, 2, 1, 1, 1);
      activateSwitch(3, 2, 1, 1, 0);
      break;

    case 18:
      digitalWrite(SEL3_EN, HIGH);
      break;
    case 19:
      //activateSwitch(6, 3, 0, 0, 0);
      activateSwitch(6, 3, 0, 0, 1);
      break;
    case 20:
      //activateSwitch(6, 3, 0, 0, 1);
      activateSwitch(6, 3, 0, 1, 1);
      break;
    case 21:
      //activateSwitch(6, 3, 0, 1, 0);
      activateSwitch(6, 3, 1, 0, 1);
      break;
    case 22:
      //activateSwitch(6, 3, 0, 1, 1);
      activateSwitch(6, 3, 1, 1, 1);
      break;
    case 23:
      //activateSwitch(6, 3, 1, 0, 0);
      activateSwitch(6, 3, 0, 0, 0);
      break;
    case 24:
      //activateSwitch(6, 3, 1, 0, 1);
      activateSwitch(6, 3, 0, 1, 0);
      break;
    case 25:
      //activateSwitch(6, 3, 1, 1, 0);
      activateSwitch(6, 3, 1, 0, 0);
      break;
    case 26:
      //activateSwitch(6, 3, 1, 1, 1);
      activateSwitch(6, 3, 1, 1, 0);
      break;
    default:
         //ERROR
      break;

  }
}
void activateSwitch(int index, int s, int b1, int b2, int b3){ 
  switch(s){
    case 1:
      digitalWrite(SEL1_EN, LOW);
      break;
    case 2:
      digitalWrite(SEL2_EN, LOW);
      break;
    case 3:
      digitalWrite(SEL3_EN, LOW);
      break;
  }
// Serial.print(b3);
// Serial.print(",");
// Serial.print(b2);
// Serial.print(",");
// Serial.println(b1);

// Serial.print(PIN_MAP[index]);
// Serial.print(",");
// Serial.print(PIN_MAP[index+1]);
// Serial.print(",");
// Serial.println(PIN_MAP[index+2]);

  digitalWrite(PIN_MAP[index],  b3);
  digitalWrite(PIN_MAP[index+1],b2);
  digitalWrite(PIN_MAP[index+2],b1);
}
//SWA:1:1
//0123456  
// void activateSwitch(String sw){
//   int swSelected;
//   int bits [] = {0,0,0};
//   String port="";
  
//   digitalWrite(COMMON, HIGH);

//   if((sw.substring(0, 2) == "SW") && (sw[3] == ':') && (sw[5] == ':')){   
//     switch(sw[4]){
//       case '1':
//         //enable switch 1
//         bits[0] = 0;
//         bits[1] = 0;
//         bits[2] = 0;
//         port="P1 ON";
//         break;
//       case '2':
//         //enable switch 2
//         bits[0] = 0;
//         bits[1] = 0;
//         bits[2] = 1;
//         port="P2 ON";
//         break;
//       case '3':
//         //enable switch 3
//         bits[0] = 0;
//         bits[1] = 1;
//         bits[2] = 0;
//         port="P3 ON";
//         break;
//       case '4':
//         //enable switch 4
//         bits[0] = 0;
//         bits[1] = 1;
//         bits[2] = 1;
//         port="P4 ON";
//         break;
//       case '5':
//         //enable switch 5
//         bits[0] = 1;
//         bits[1] = 0;
//         bits[2] = 0;
//         port="P5 ON";
//         break;
//       case '6':
//         //enable switch 6
//         bits[0] = 1;
//         bits[1] = 0;
//         bits[2] = 1;
//         port="P6 ON";
//         break;
//       case '7':
//         //enable switch 7
//         bits[0] = 1;
//         bits[1] = 1;
//         bits[2] = 0;
//         port="P7 ON";
//         break;
//       case '8':
//         //enable switch 8
//         bits[0] = 1;
//         bits[1] = 1;
//         bits[2] = 1;
//         port="P8 ON";
//         break;
//       default:
//         //ERROR
//         break;
//     }
//      switch(sw[2]){
//       case '0':         //diable all switches.....
//         digitalWrite(SEL1_EN, HIGH);
//         digitalWrite(SEL2_EN, HIGH);
//         digitalWrite(SEL3_EN, HIGH);
//         sw1="ALL OFF";
//         sw2="ALL OFF";
//         sw3="ALL OFF";
//         digitalWrite(COMMON, LOW);
//         snprintf (outputText, 1000, "Switch 1 : %s<br>Switch 2 : %s<br>Switch 3 : %s<br>",sw1,sw2,sw3);        
//         return;
//       case '1':
//         if(sw[6] == '1'){
//           //enable switch 1
//           digitalWrite(SEL1_EN, LOW);
//           sw1 = port;
//           swSelected = 0; 
//         }else{
//           digitalWrite(SEL1_EN, HIGH);
//           sw1 = "ALL OFF";
//           //return;
//         }        
//         break;
//       case '2':
//         if(sw[6] == '1'){
//           //enable switch 2
//           digitalWrite(SEL2_EN, LOW);
//           sw2 = port;
//           swSelected = 3;
//         }else{
//           digitalWrite(SEL2_EN, HIGH);
//           sw2 = "ALL OFF";
//          // return;
//         }  
//         break;
//       case '3':
//         if(sw[6] == '1'){
//           //enable switch 3
//           digitalWrite(SEL3_EN, LOW);
//           sw3 = port;
//           swSelected = 6;
//         }else{
//           digitalWrite(SEL3_EN, HIGH);
//           sw3 = "ALL OFF";
//          // return;
//         }  
//         break;
//       default:
//         //ERROR
//         break;
//     }
//     if(sw[6] =='1')
//       modifySW(swSelected,bits);
    
//     snprintf (outputText, 1000, "Switch 1 : %s<br>Switch 2 : %s<br>Switch 3 : %s<br>",sw1,sw2,sw3);   
//   }
// }

// void modifySW(int index, int bits[] ){
//   digitalWrite(PIN_MAP[index],bits[2]);
//   digitalWrite(PIN_MAP[index+1],bits[1]);
//   digitalWrite(PIN_MAP[index+2],bits[0]);
//   //digitalWrite(PIN_MAP[index], val);
// }
// int hexToInt(char val1, char val2){
//  char str [2];
//  str[0] = val1;
//  str[1] = val2;
 
//  return (int) strtol(str, 0, 16);
// }



//OLD WEBSITE...

//  char html[2500];
//    snprintf (html, 2500,
//      "<html>\
//        <head>\
//          <title>Control </title>\
//          <meta name = \"viewport\" content = \"width = device-width\">\
//          <style>\
//            body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
//            h1 { Color: #AA0000; }\
//          </style>\
//        </head>\
//        <body>\            
//            <form action=\"update\" method=\"get\" id=\"form\"> input1: <input type=\"text\" name=\"input1\">\
//            <input type=\"submit\" value=\"Submit\">\
//            <input type=\"radio\" id=\"S1\" name=\"radio\" value=\"0\">\
//            <label for=\"S1\">S0</label>\
//            </form>\
//            %s\         
//        </body>\
//       </html>",
//       outputText
//    );
  // snprintf (html, 2500,
  //     "<html>\
  //       <head>\
  //         <title>Control </title>\
  //         <meta name = \"viewport\" content = \"width = device-width\">\
  //         <style>\
  //           body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
  //           h1 { Color: #AA0000; }\
  //         </style>\
  //       </head>\
  //       <body>\            
  //           <form action=\"update\" method=\"get\" id=\"form\"> input1: <input type=\"text\" name=\"input1\">\
  //           <input type=\"submit\" value=\"Submit\">\
  //           </form>\
  //           %s\         
  //       </body>\
  //      </html>",
  //   outputText
  // );
