#include <Arduino.h>
#include <WiFi.h>
#include "FreeRTOS.h"
#include "task.h"
#include "ID_UART.h"


char* ssid = "cdf_crac";
char* password = "cracadmin";
char* wifiIP = "192.168.0.1";  // Adresse IP du serveur
char* serverIP = "192.168.0.100";

int wifiPort = 8080;    // Port utilisé pour tester la connexion WiFi
int socketPort = 5050;  // Port utilisé pour le socket principal

WiFiClient wifiClient;    // Client pour tester la connexion WiFi (8080)
WiFiClient socketClient;  // Client pour le vrai socket (5050)
int i = 0;
String role;

uint8_t dataToSend[9] = {0,0,0,0,0,0,0,0,0};


uint8_t convert_short_2_byte(uint16_t short_2_transform_x,uint16_t short_2_transform_y, uint8_t* high_x, uint8_t* low_x, uint8_t* high_y, uint8_t* low_y){
  *high_x = (short_2_transform_x >> 8) & 0xFF; // Poids fort
  *low_x  = short_2_transform_x & 0xFF;        // Poids faible
  *high_y = (short_2_transform_y >> 8) & 0xFF; // Poids fort
  *low_y  = short_2_transform_y & 0xFF;        // Poids faible
}

void init_wifi(){
  // 🔹 Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  Serial.print(" Connexion au WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnecté au WiFi !");
  Serial.print("Adresse IP du BW16: ");
  Serial.println(WiFi.localIP());

  // 🔹 Tester la connexion sur le port 8080
  Serial.print("Connexion au serveur sur le port 8080... ");
  if (wifiClient.connect(wifiIP, wifiPort)) {
    Serial.println("Connexion réussie au port 8080 !");
      wifiClient.println("Test connexion WiFi OK");
  } else {
    Serial.println("Échec de connexion au port 8080.");
  }
}

void init_socket() {
  Serial.print("Connexion au serveur sur le port 5050... ");
  if (socketClient.connect(serverIP, socketPort)) {
    Serial.println("Connexion réussie au socket 5050 !");
    socketClient.println("Hello Server, je suis BW16 !");
  } else {
    Serial.println("Échec de connexion au socket 5050.");
  }
}

void read_socket(void*) {
  while (1) {
    if (socketClient.available()) {
      String response = socketClient.readString();

      if(response == "START_PAMIS" ) {
        if(role == "GROUPIE_ONE"){
          
        }
        if(role == "GROUPIE_TWO"){

        }
        if(role == "GROUPIE_THREE"){

        }
      }

      if(response == "GROUPIE_ONE"){
        role = response;
      }

      if(response == "GROUPIE_TWO"){
        role = response;
      }

      if(response == "GROUPIE_THREE"){
        role = response;
      }
      //Serial.println("Réponse du serveur : " + response);
    }
    vTaskDelay(pdMS_TO_TICKS(100));  // Pause de 100ms
  }
}

void send_socket(void*){
  while(1){
    if (socketClient.available()){

    }
    vTaskDelay(pdMS_TO_TICKS(100));  // Pause de 100ms
  }
}

void setup() {
  
  Serial.begin(115200);
   // Initialiser le port série 1 avec la vitesse en bauds (9600) et la configuration série
  Serial1.begin(9600);  // Baudrate de 9600 et configuration série 8N1 (8 bits, aucune parité, 1 bit d'arrêt)

  // init_wifi();
  // init_socket();
  // xTaskCreate(read_socket, "Socket", 4096, NULL, 2, 0);


}

void loop() {
  if(Serial.available()){
    char c = Serial.read();
        if (c == 's')
          {
            Serial.println("send");
            uint16_t x = 1000;
            uint16_t y = 1400;

            uint8_t high_x;
            uint8_t low_x;
            uint8_t high_y;
            uint8_t low_y;

            convert_short_2_byte(x, y, &high_x, &low_x, &high_y, &low_y);

            dataToSend[0] = POLAIRE;
            dataToSend[1] =  high_x;
            dataToSend[2] =  low_x;
            dataToSend[3] =  high_y;
            dataToSend[4] =  low_y;

            for(int i = 0; i < 9; i++){
              Serial.print("send");
              Serial.println(dataToSend[i]);
              Serial1.write(dataToSend[i]);
            }
          }
        }
    if(Serial1.available()){
      Serial.println(Serial1.read());
    }
}