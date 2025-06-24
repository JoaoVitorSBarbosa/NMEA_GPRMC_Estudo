#include "../lib/GPSController.h"

GPSController::GPSController() {}
GPSController::~GPSController() {}

// Exemplo de Sentenca $GPRMC : $GPRMC,132454.00,A,1252.33842,S,04803.96357,W,0.252 ,,080625,,,A*77
// $GPRMC,203522.00,A,5109.0262308,N,11401.8407342,W,0.004,133.4,130522,0.0,E,D*2B
//   1          2   3       4       5       6       7   8    9     10   11 12 13 14          

bool GPSController::parse_gprmc(const char* nmea_sentence, gps_data_t* data){
    uint8_t cont = 0; 
    uint8_t structureCount = 0;
    char caractere = ' ';
    string structure = "";
    while (caractere != '\000') {
        caractere = nmea_sentence[cont];

        if(caractere == ',') {
            switch (structureCount) {
            case 0: {//Log header
                bool isGPRMC = structure == "$GPRMC";
                if (!isGPRMC) return false;
                break;
            }
            // case 1: //UTC of position
            //     break;
            case 2: { //Position status (A = data valid, V = data invalid)
                data->is_valid = structure == "A";
                break;
            }
            case 3: {//Latitude (DDmm.mm)
                data->latitude = stof(structure);
                break;
            }
            // case 4: //Latitude direction: (N = North, S = South)
            //     break;
            case 5: {//Longitude (DDDmm.mm)
                data->longitude = stof(structure);
                break;
            }
            // case 6://Longitude direction: (E = East, W = West)
            //     break;
            case 7: {//Speed over ground, knots
                float speedInKnots = stof(structure);
                data->speed = ISO_VALUES ? speedInKnots / 1.94384449 : speedInKnots;
                break;
            }
            // case 8://Track made good, degrees True
            //     break;
            // case 9://Date: dd/mm/yy
            //     break;
            // case 10://Magnetic variation, degrees (Always positive)
            //     break;
            // case 11:// Magnetic variation direction E/W Easterly variation (E) subtracts from True course.
            //     break;
            // case 12://Positioning system mode indicator,
            //     break;
            // case 13://Check sum
            //     break;
            // case 14://Sentence terminator
            //     break;
            // default:
            //     break;
            }
            structureCount++;
            structure = "";
        } else {
            structure += caractere;
        }
        cont++;
    }
    return true;
}