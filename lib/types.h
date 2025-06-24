#ifndef TYPES_H
#define TYPES_H

#include "includes.h"
struct gps_data_t{ 
    float latitude; 
    float longitude; 
    float speed; 
    bool is_valid;

    gps_data_t() : latitude(0.0), longitude(0.0), speed(0.0), is_valid(false) { //Construtor padrão
        
    }
    
    gps_data_t(
        float lat, 
        float lon, 
        float spd,
        bool valid
    ) 
        : latitude(lat), longitude(lon), speed(spd), is_valid(valid) {
    }
    
    // imprimir formatado
    const char* toString() const {
        std::string temp;
        temp = "Latitude: "; 
        temp += latitude; 
        temp += "\n";
        temp += "longitude: ";
        temp += longitude;
        temp += "\n";
        temp += "Velocidade: ";
        temp += speed;
        temp += "\n";
        temp += "Validade: ";
        temp += (is_valid ? "VALIDO" : "INVALIDO");
        temp += "\n";
        return temp.c_str();
    }
};


#endif