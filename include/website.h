// HTML String für Website

#include <Arduino.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>


const char* ssid = "mockSSID";
const char* password = "mockPassWord";
const char* PARAM_STRING = "inputString";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
String inputMessage;

AsyncWebServer server(80);

// To be called
void setupWebserver();
void checkIfTimeSetHasChanged();
bool compareTime();

// Helper
String getLocalTimeAsString();
String readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
String processor(const String& var);
void notFound(AsyncWebServerRequest *request) ;

// EIgentlicher Website Inhalt:
const char index_html[] PROGMEM = R"rawliteral(
							<!DOCTYPE HTML><html><head>
  							<title>Fanni Frieda Fine Stall Steuerung</title>
  							<meta name="viewport" content="width=device-width, initial-scale=1">
  							<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;} 
				 			.button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; 
				 			text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;} 
				 			</style></head> 
  							<script>
							function submitMessage() {
							alert("Uhrzeit geaendert");
							setTimeout(function(){ document.location.reload(false); }, 500);   
							}
							</script></head><body>
							<h1>H&#252;hnerstall Steuerung</h1>
							<form action="/get" target="hidden-form">
							Uhrzeit Stalloeffnung: (aktuell: %inputString%): <input type="time" name="inputString">
							<input type="submit" value="OK" onclick="submitMessage()">
							</form><br>
							<iframe style="display:none" name="hidden-form"></iframe>
							</body></html>)rawliteral";



