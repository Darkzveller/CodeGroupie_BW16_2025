#include <WiFi.h>

char* ssid = "cdf_crac";
const char* password = "cracadmin";
const char* wifiIP = "192.168.0.1";  // Adresse IP du serveur
const char* serverIP = "192.168.0.103";

const int wifiPort = 8080;  // Port utilisé pour tester la connexion WiFi
const int socketPort = 5050;    // Port utilisé pour le socket principal

WiFiClient wifiClient;  // Client pour tester la connexion WiFi (8080)
WiFiClient socketClient;     // Client pour le vrai socket (5050)

void setup() {
    Serial.begin(115200);
    
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

    // 🔹 Connexion au socket sur le port 5050
    Serial.print("Connexion au serveur sur le port 5050... ");
    if (socketClient.connect(serverIP, socketPort)) {
        Serial.println("Connexion réussie au socket 5050 !");
        socketClient.println("Hello Server, je suis BW16 !");
    } else {
        Serial.println("Échec de connexion au socket 5050.");
    }
}

void loop() {
    // 🔹 Lire les messages du serveur (socket 5050)
    if (socketClient.available()) {
        String response = socketClient.readString();
        Serial.println("Réponse du serveur : " + response);
    }

    delay(1000);  // Pause pour éviter de surcharger
}