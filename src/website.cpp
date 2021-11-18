#include "website.h"






void setupWebserver() 
{
  
  
  // Initialize SPIFFS
  #ifdef ESP32
    if(!SPIFFS.begin(true)){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #else
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  //Serial.println();
  //Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Webpage mit Input Feld
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    
    // GET inputString value on <ESP_IP>/get?inputString=<inputMessage>
    if (request->hasParam(PARAM_STRING)) {
      inputMessage = request->getParam(PARAM_STRING)->value();
      writeFile(SPIFFS, "/inputString.txt", inputMessage.c_str());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);

    
    request->send(200, "text/text", inputMessage);

  });
  server.onNotFound(notFound);
  server.begin();

  //configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
}

void checkIfTimeSetHasChanged()
{
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    
    // GET inputString value on <ESP_IP>/get?inputString=<inputMessage>
    if (request->hasParam(PARAM_STRING)) {
      inputMessage = request->getParam(PARAM_STRING)->value();
      writeFile(SPIFFS, "/inputString.txt", inputMessage.c_str());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);

    
    request->send(200, "text/text", inputMessage);

  });
}



bool compareTime()
{
    time_t currentTime = getLocalTimeAsTime();
    String timeSetString = inputMessage;
    time_t timeSet = getTimeFromString(inputMessage);
    Serial.println("time: "+ currentTime);
    Serial.println("Set: " + timeSet);
  
    // difftime gibt Unterschied in Sekunden zurück
    // Oeffnung im 10 min Intervall
    if(abs(difftime(timeSet, currentTime)) < (10*60) )
    {
        return true;
    }
    else
    {
        return false;
    }
  
}

time_t getTimeFromString(String time)
{
    const char *time_details = c_str(time);
    struct tm tm;
    strptime(time_details, "%H:%M:", &tm);
    time_t t = mktime(&tm);
    return t;
}

time_t getLocalTimeAsTime()
{
    struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    
    return "";
  }
  time_t t = mktime(&timeinfo);
  return t;
}

String getLocalTimeAsString()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    
    return " ";
  }
  
  char buffer[5];
  strftime(buffer,80,"%H:%M", &timeinfo);
  
  String uhrzeit = buffer;
  Serial.println(uhrzeit);
  return uhrzeit;

}

String readFile(fs::FS &fs, const char * path)
{
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message)
{
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
}

// 
String processor(const String& var)
{
  //Serial.println(var);
  if(var == "inputString"){
    return readFile(SPIFFS, "/inputString.txt");
  }
  return String();
}

void notFound(AsyncWebServerRequest *request) 
{
  request->send(404, "text/plain", "Not found");
}