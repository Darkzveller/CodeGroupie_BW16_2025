#include <WiFi.h>
#define TELEPHONE_YOUSSEF
// #define ROUTEUR_CRAC

#ifdef TELEPHONE_YOUSSEF
char* ssid = "Me voici";       // SSID du réseau WiFi
char* password = "youssef13";  // Mot de passe du réseau WiFi
#endif

#ifdef ROUTEUR_CRAC
char* ssid = "cdf_crac";
char* password = "cracadmin";
char* wifiIP = "192.168.0.1";  // Adresse IP du serveur
char* serverIP = "192.168.0.103";
#endif

int wifiPort = 8080;    // Port utilisé pour tester la connexion WiFi
int socketPort = 5050;  // Port utilisé pour le socket principal

WiFiClient wifiClient;    // Client pour tester la connexion WiFi (8080)
WiFiClient socketClient;  // Client pour le vrai socket (5050)
int i = 0;
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
#ifdef ROUTEUR_CRAC
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
#endif
}

void loop() {
#ifdef ROUTEUR_CRAC
  // 🔹 Lire les messages du serveur (socket 5050)
  if (socketClient.available()) {
    String response = socketClient.readString();
    Serial.println("Réponse du serveur : " + response);
  }
#endif
  Serial.print("i = ");
  Serial.println(i++);
  delay(500);  // Pause pour éviter de surcharger
}