#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

//Provide the token generation process info.
#include <addons/TokenHelper.h>

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "circuiTician"
#define WIFI_PASSWORD "Pneucis@202028"
#define led_wifi 15


//For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "vSgAna1TJnANgkleTIUgvfId2i6odsGn4sEtT8AT"

/* 3. Define the RTDB URL */
#define DATABASE_URL "orch-48b91-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app


//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

void setup()
{

  Serial.begin(115200);
  pinMode(led_wifi, OUTPUT);
  digitalWrite(led_wifi,0);

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
  digitalWrite(led_wifi,1);

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;



  //////////////////////////////////////////////////////////////////////////////////////////////
  //Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
  //otherwise the SSL connection will fail.
  //////////////////////////////////////////////////////////////////////////////////////////////

  Firebase.begin(DATABASE_URL, API_KEY);

  //Comment or pass false value when WiFi reconnection will control by your code or third party library
 // Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

}

void loop()
{
  //Flash string (PROGMEM and  (FPSTR), String, C/C++ string, const char, char array, string literal are supported
  //in all Firebase and FirebaseJson functions, unless F() macro is not supported.

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    Firebase.setInt(fbdo, "/test/PM", sendDataPrevMillis);
    //Serial.println(Firebase.getInt(fbdo, "/test/int"));
    Serial.printf("Get int... %s\n", Firebase.getInt(fbdo, "/test/int") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    

//    Serial.printf("Set bool... %s\n", Firebase.setBool(fbdo, "/test/bool", count % 2 == 0) ? "ok" : fbdo.errorReason().c_str());
//
//    Serial.printf("Get bool... %s\n", Firebase.getBool(fbdo, "/test/bool") ? fbdo.to<bool>() ? "true" : "false" : fbdo.errorReason().c_str());
//
//    bool bVal;
//    Serial.printf("Get bool ref... %s\n", Firebase.getBool(fbdo, "/test/bool", &bVal) ? bVal ? "true" : "false" : fbdo.errorReason().c_str());
//
//    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, "/test/int", count) ? "ok" : fbdo.errorReason().c_str());
//
//    Serial.printf("Get int... %s\n", Firebase.getInt(fbdo, "/test/int") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
//
//    int iVal = 0;
//    Serial.printf("Get int ref... %s\n", Firebase.getInt(fbdo, "/test/int", &iVal) ? String(iVal).c_str() : fbdo.errorReason().c_str());
//
//    Serial.printf("Set float... %s\n", Firebase.setFloat(fbdo, "/test/float", count + 10.2) ? "ok" : fbdo.errorReason().c_str());
//
//    Serial.printf("Get float... %s\n", Firebase.getFloat(fbdo, "/test/float") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
//
//    Serial.printf("Set double... %s\n", Firebase.setDouble(fbdo, "/test/double", count + 35.517549723765) ? "ok" : fbdo.errorReason().c_str());
//
//    Serial.printf("Get double... %s\n", Firebase.getDouble(fbdo, "/test/double") ? String(fbdo.to<double>()).c_str() : fbdo.errorReason().c_str());
//
//    Serial.printf("Set string... %s\n", Firebase.setString(fbdo, "/test/string", "Hello World!") ? "ok" : fbdo.errorReason().c_str());
//
//    Serial.printf("Get string... %s\n", Firebase.getString(fbdo, "/test/string") ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
//
//    Serial.println();
    

    count++;
  }
}
