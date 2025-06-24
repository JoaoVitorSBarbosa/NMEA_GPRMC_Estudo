#ifndef GPS_CONTROLLER_H
#define GPS_CONTROLLER_H


#include "./defines.h"
#include "./types.h"

class GPSController {
   private:
    /* data */
   public:
    GPSController(/* args */);
    ~GPSController();
    bool parse_gprmc ( const char * nmea_sentence , gps_data_t* data );
};


#endif
