
const int relayPin = 7;

void setup() {
 
  pinMode(relayPin, OUTPUT);
  
 
  Serial.begin(115200);
  
 
  digitalWrite(relayPin, HIGH);
}

void loop() {
  
  if (Serial.available()) {
   
    String command = Serial.readStringUntil('\n');
    
    
    command.trim(); 

    if (command == "ON") {
      digitalWrite(relayPin, LOW);  
      Serial.println("Relay ON");
    } else if (command == "OFF") {
      digitalWrite(relayPin, HIGH); 
      Serial.println("Relay OFF");
    }
  }
}
