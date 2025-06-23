typedef struct gps_data_t{ 
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
    String toString() const {
        return "Latitude: " +
        (String)latitude + "\n"
        "longitude: " +
        (String)longitude + "\n"
        "Velocidade: " +
        (String)speed + "\n"
        "Validade: " +
        (is_valid ? "VALIDO" : "INVALIDO") + "\n";

    }
};