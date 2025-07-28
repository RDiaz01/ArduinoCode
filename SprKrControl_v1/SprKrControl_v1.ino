#include <Adafruit_AHT10.h> //temperature sensor
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

#define ZONE_1 32
#define ZONE_2 33
#define ZONE_3 25
#define ZONE_4 26
#define ZONE_5 27
#define ZONE_6 14
#define ZONE_7 13
#define ZONE_8 16


Adafruit_AHT10 aht;
RTC_DS3231 rtc;
DateTime now;

int ZONES_PINS [] = {32,33,25,26,27,14,13,16};
struct Event {
  int hr;
  int minut;
  bool Zone [8];
};

Event event[9] = {{10,33,{true,false,false,false,false,false,false,false}},
                  {10,34,{false,true,false,false,false,false,false,false}},
                  {10,35,{false,false,true,false,false,false,false,false}},
                  {10,36,{false,false,false,true,false,false,false,false}},
                  {10,37,{false,false,false,false,true,false,false,false}},
                  {10,38,{false,false,false,false,false,true,false,false}},
                  {10,39,{false,false,false,false,false,false,true,false}},
                  {10,40,{false,false,false,false,false,false,false,true}},
                  {10,41,{false,false,false,false,false,false,false,false}}
                  };


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int ind = 0;
void setup () {
  Serial.begin(115200);
  pinMode(ZONES_PINS[0], OUTPUT);
  pinMode(ZONES_PINS[1], OUTPUT);
  pinMode(ZONES_PINS[2], OUTPUT);
  pinMode(ZONES_PINS[3], OUTPUT);
  pinMode(ZONES_PINS[4], OUTPUT);
  pinMode(ZONES_PINS[5], OUTPUT);
  pinMode(ZONES_PINS[6], OUTPUT);
  pinMode(ZONES_PINS[7], OUTPUT);

  digitalWrite(ZONE_6, LOW);


  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! aht.begin()) {
    Serial.println("Could not find AHT10? Check wiring");
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
   rtc.adjust(DateTime(2014, 1, 21, 10, 32, 54));
}

void loop () {
    now = rtc.now();

//    Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(" (");
//    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//    Serial.print(") ");
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute());
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
    Serial.println();

    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
//    Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
//    Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

    if((event[ind].hr == now.hour()) && (event[ind].minut == now.minute())){
      Serial.println("Running event!");
      runEvent(ind);
      if(ind >=8){
        ind=0;
      }else{
        ind++;
      }
    }



//    Serial.print("Temperature: ");
//    Serial.print(rtc.getTemperature());
//    Serial.println(" C");
//    digitalWrite(zones[ind], LOW);
//    delay(20);
    delay(500);
}

void runEvent(int i){
  int enable_zone = -1 ;
  for(int m=0; m<8; m++){
    if(event[i].Zone[m] == true){
//      Serial.print("Enable Zone Pin :");
//      Serial.println(enable_zone);
      enable_zone = m;
//      digitalWrite(ZONES_PINS[m], HIGH);
    }else if(event[i].Zone[m] == false){
      digitalWrite(ZONES_PINS[m], LOW);
//      Serial.println(enable_zone);
    }
  }
  // Serial.println(enable_zone);
 if( enable_zone >= 0)
   digitalWrite(ZONES_PINS[enable_zone], HIGH);
}
