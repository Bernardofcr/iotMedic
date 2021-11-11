
/**
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2021 mobizt
 *
*/

/** This example will show how to authenticate using 
 * the legacy token or database secret with the new APIs (using config and auth data).
*/
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Berctor_2G"
#define WIFI_PASSWORD "cerberus"

/* 2. If work with RTDB, define the RTDB URL and database secret */
#define DATABASE_URL "https://iotmeddata-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "D3YvhWrkuRyE7ZQ3IGY2qcfSiGRP5xEo1PZ0o6Ii"

/* 3. Define the Firebase Data object */
FirebaseData fbdo;

/* 4, Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* Define the FirebaseConfig data for config data */
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;

void setup()
{
  

    Serial.begin(115200);

    pinMode(LED_BUILTIN,OUTPUT);
    pinMode(A0,INPUT);
    pinMode(D1,INPUT);
    pinMode(D0,OUTPUT);
    pinMode(D2,OUTPUT);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the certificate file (optional) */
    //config.cert.file = "/cert.cer";
    //config.cert.file_storage = StorageType::FLASH;

    /* Assign the database URL and database secret(required) */
    config.database_url = DATABASE_URL;
    config.signer.tokens.legacy_token = DATABASE_SECRET;

    Firebase.reconnectWiFi(true);

    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);

    //Or use legacy authenticate method
    //Firebase.begin(DATABASE_URL, DATABASE_SECRET);
}

void loop()
{
    if (millis() - dataMillis > 5000)
    {
        dataMillis = millis();
        Firebase.setInt(fbdo, "presure", analogRead(A0));
        Firebase.setInt(fbdo, "help", !digitalRead(D1));
        Firebase.getInt(fbdo, "medicine");
        digitalWrite(LED_BUILTIN, !fbdo.intData());
        Firebase.getInt(fbdo, "dosage1");
        analogWrite(D0,fbdo.intData());
        Firebase.getInt(fbdo, "dosage2");
        analogWrite(D2,fbdo.intData());
    }
}
