#include "../lib/GPSController.h"

GPSController::GPSController() {}
GPSController::~GPSController() {}

// Exemplo de Sentenca $GPRMC : $GPRMC,132454.00,A,1252.33842,S,04803.96357,W,0.252 ,,080625,,,A*77
// $GPRMC,203522.00,A,5109.0262308,N,11401.8407342,W,0.004,133.4,130522,0.0,E,D*2B
//   0          1   2       3       4       5       6   7    8     9   10 11 12 13          

/*
    @param const char* nmea_sentence = string (buffer) dados para a conversão 
    @param gps_data_t* data = struct para armazenar as informações
    @return um booleano. false indica que não é um cógido GPRMC válido ou o checksum está incorreto
*/
bool GPSController::parse_gprmc(const char* nmea_sentence, gps_data_t* data){
    uint8_t cont = 0; 
    uint8_t structureCount = 0;
    uint8_t caractere = ' ';
    string structure = "";
    uint8_t checkSum = 0;
    bool checkSumIgnore = false;
    uint8_t receivedCheckSum = 0;
    bool checkSumCalculated = false;
    while (!checkSumCalculated) {
        caractere = (uint8_t)nmea_sentence[cont];
        if (caractere == '*') //Evita que o cheacksum recebido entre na contagem
            checkSumIgnore = true;
        
        if ((caractere != '$') and (caractere != '*')) { 
            if(!checkSumIgnore)
                checkSum ^= caractere;
        }
        
        if(caractere == ',' or caractere == '*' or caractere == '\000') {
            switch (structureCount) {
            case 0: {//Log header
                bool isGPRMC = structure == "$GPRMC";
                if (!isGPRMC) return false;
                break;
            }
            case 2: { //Position status (A = data valid, V = data invalid)
                data->is_valid = structure != "V";
                break;
            }
            case 3: {//Latitude (DDmm.mm)
                data->latitude = stof(structure);
                break;
            }
            case 5: {//Longitude (DDDmm.mm)
                data->longitude = stof(structure);
                break;
            }
            case 7: {//Speed over ground, knots
                float speedInKnots = stof(structure);
                data->speed = ISO_VALUES ? speedInKnots / 1.94384449 : speedInKnots;
                break;
            }
            case 13: { //CheckSum
                if(caractere == '\000') {
                    receivedCheckSum = std::stoi(structure, nullptr, 16);
                    checkSumCalculated = true;
                }
            }
                break;
            }
            structureCount++;
            structure = "";
        } else {
            if(caractere != '\000')
                structure += caractere;
        }
        cont++;
    }
    if (receivedCheckSum != checkSum) {
        data->is_valid = false;
        return false;
    }
    
    return true;
}