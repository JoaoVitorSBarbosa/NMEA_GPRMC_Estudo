#include "../lib/includes.h"


GPSController* gpsCon = nullptr;


void setup() {
    gpsCon = new(std::nothrow) GPSController();
    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN,LOW);
}

void loop() {
    gps_data_t dado1_obj;
    gps_data_t dado2_obj;

    gps_data_t* dado1 = &dado1_obj;
    gps_data_t* dado2 = &dado2_obj; 
    bool val1 = false;
    bool val2 = false;
    if (gpsCon){
        val1 = gpsCon->parse_gprmc((const char*)NMEA_SETENCE1, dado1); //Retorna true
        val2 = gpsCon->parse_gprmc((const char*)NMEA_SETENCE2, dado2); //Retorna false
    }

    delay(2000);
    digitalWrite(LED_BUILTIN,!(val1 and val2));
}