#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi credentials
const char* ssid = "wifi-ssid";
const char* password = "wifi-password";

// Firebase configuration
#define FIREBASE_HOST "firebase-host-URL"
#define FIREBASE_API_KEY "Firebase API key"

// Firebase and Wi-Fi initialization
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600); // For debugging

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial1.println("Connecting to Wi-Fi...");
    }
    Serial1.println("Connected to Wi-Fi!");
    Serial1.print("IP Address: ");
    Serial1.println(WiFi.localIP());

    // Set Firebase configuration
    firebaseConfig.host = FIREBASE_HOST;
    firebaseConfig.api_key = FIREBASE_API_KEY;  // Use API key here

    firebaseAuth.user.email = "email@gmail.com";
    firebaseAuth.user.password = "password";

    // Initialize Firebase
    Firebase.begin(&firebaseConfig, &firebaseAuth);
    Firebase.reconnectWiFi(true);
}

void loop() {
    float carbonLevel = 10.0;  // Example value
    float airQuality = 10.0;   // Example value

    Serial.print("Carbon Level: ");
    Serial.print(carbonLevel);
    Serial.print(" ppm, Air Quality: ");
    Serial.print(airQuality);
    Serial.println("%");

    // Send data to Firebase
    if (Firebase.pushFloat(firebaseData, "/carbonLevel", carbonLevel) &&
        Firebase.pushFloat(firebaseData, "/airQuality", airQuality)) {
        Serial.println("Data sent to Firebase successfully!");
    } else {
        Serial.println("Failed to send data to Firebase.");
        Serial.println("Error: " + firebaseData.errorReason());
    }

    delay(1000);  // Adjust delay as needed
}
