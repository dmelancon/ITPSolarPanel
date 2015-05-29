#include <Process.h>
#include <Wire.h>
String CouchIP = "http://128.122.6.165:5984";   //change this to the couchDB IP+port
String newJSON, newUUID;

void setup() {
  Serial.begin(9600);  // initialize serial communication
  while (!Serial);     // do nothing until the serial monitor is opened
  Serial.println("Starting bridge...\n");
  Bridge.begin();  // make contact with the linux processor
  Wire.begin(2);
  Wire.onReceive(receiveEvent);  
  delay(2000);  // wait 2 seconds
}

void loop() {
      checkJSON();
}


void receiveEvent(int howMany)
{
  
  while(Wire.available()>0) 
  {
    char c  = Wire.read();
    newJSON+=c; 
  }
}

//checks for complete JSON string and calls DB functions
void checkJSON(){
     char c = newJSON.charAt(newJSON.length()-1);
      if (c == '}'){
       Serial.println(newJSON);
        newUUID = reqUUID();
        callDB(newUUID, newJSON);
        newJSON = "";
      }
}

//returns new UUID from couchDB for each document
String reqUUID(){
    Process solarDB;
    solarDB.runShellCommand("curl -X GET "+ CouchIP +"/_uuids");
    while (solarDB.available() > 0) {
      //parse the response to get the UUID string
      String c = solarDB.readStringUntil('\"');
      c = solarDB.readStringUntil('\"');
      c = solarDB.readStringUntil('\"');
      String UUID = solarDB.readStringUntil('\"');
      return UUID;
    }
}

//PUT new document onto the DB
void callDB(String UUID, String JSON){
    Process solarDB;
    solarDB.runShellCommand("curl -X PUT " + CouchIP + "/solar/"+ UUID+ " -d  \'"+ JSON +"\'");  
    while (solarDB.available() > 0) {
      char c = solarDB.read();
      Serial.print(c);
    } 
}
