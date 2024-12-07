#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "GalaxyMJ";
const char* password = "Alorica2028**";

const int waterSensorPin = 4; 


WebServer server(80);

bool pumpState = false;     
bool isFull = false;       


void sendSignalToArduino(const char* message) {
  Serial.println(message);
}

String getHTMLPage() {
  
  String lockIcon = isFull ? "🔒" : "🔓";
  String statusText = isFull ? "Full" : "Not Full";
  

  String html = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>e-Faucet Dashboard</title><style>";
  html += "/* General Styles */ * { margin: 0; padding: 0; box-sizing: border-box; } body { font-family: Arial, sans-serif; background: linear-gradient(to right, #e3f2fd, #bbdefb); display: flex; flex-direction: column; min-height: 100vh; } .container { display: flex; flex-direction: row; height: 90vh; width: 100%; }";
  html += ".sidebar { width: 220px; background-color: #005c71; color: #ffffff; display: flex; flex-direction: column; align-items: center; padding-top: 20px; border-top-right-radius: 15px; border-bottom-right-radius: 15px; box-shadow: 3px 0 10px rgba(0, 0, 0, 0.2); }";
  html += ".sidebar h2 { font-size: 22px; margin-bottom: 60px; } .logout-btn { background-color: #006d78; color: #ffffff; padding: 12px 25px; border: none; border-radius: 10px; cursor: pointer; font-size: 16px; transition: background 0.3s; }";
  html += ".logout-btn:hover { background-color: #005c71; } .main-content { flex: 1; padding: 20px; text-align: center; } .main-content h1 { font-size: 28px; margin-bottom: 15px; } .status { color: #006d78; font-weight: bold; }";
  html += ".control-panel { display: flex; flex-wrap: wrap; justify-content: space-around; margin: 20px 0; padding: 20px; background-color: #ffffff; border-radius: 15px; box-shadow: 0px 4px 12px rgba(0, 0, 0, 0.1); }";
  html += ".toggle-faucet, .water-status { width: 100%; max-width: 300px; margin: 10px; background-color: #f8f9fa; border-radius: 15px; padding: 20px; box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.1); }";
  html += ".toggle-faucet h3, .water-status h3 { font-size: 20px; color: #005c71; margin-bottom: 10px; } .toggle-btn { color: #ffffff; font-size: 20px; padding: 12px 25px; border: none; border-radius: 10px; cursor: pointer; transition: background 0.3s; }";
  html += ".toggle-btn.on { background-color: #28a745; } .toggle-btn.off { background-color: #dc3545; } .water-status .status-icon { text-align: center; margin-top: 20px; } .lock-icon { font-size: 36px; color: #606060; }";
  html += ".demo-btn { background-color: #4a4ef7; color: #ffffff; padding: 12px 25px; border: none; border-radius: 10px; cursor: pointer; transition: background 0.3s; } .contact-btn { background-color: #005c71; color: #ffffff; padding: 10px 20px; border: none; border-radius: 10px; cursor: pointer; font-size: 16px; transition: background 0.3s; }";
  html += ".contact-btn:hover { background-color: #004c61; } footer { text-align: center; padding: 10px; background-color: #e0e0e0; width: 100%; position: fixed; bottom: 0; }";
  html += "@media (max-width: 768px) { .container { flex-direction: column; } .sidebar { width: 100%; border-radius: 0; box-shadow: none; } .main-content h1 { font-size: 24px; } .toggle-faucet, .water-status { width: 100%; } .demo-btn, .contact-btn { width: 100%; padding: 10px; font-size: 16px; } }";
  html += "@media (max-width: 480px) { .main-content h1 { font-size: 20px; } .sidebar h2 { font-size: 18px; } .logout-btn, .toggle-btn, .demo-btn, .contact-btn { font-size: 14px; padding: 8px 15px; } .toggle-faucet h3, .water-status h3 { font-size: 16px; } .lock-icon { font-size: 24px; } }";
  html += "</style></head><body><div class=\"container\"><div class=\"sidebar\"><h2>Admin Pane</h2><button class=\"logout-btn\" onclick=\"logout()\">LOGOUT</button></div><div class=\"main-content\">";


  html += "<h1>e-Faucet: Intelligent Bath Faucet <span class=\"status\">Online</span></h1><h2>Interaction</h2><div class=\"control-panel\">";
  html += "<div class=\"toggle-faucet\"><h3>Toggle Faucet<br><span>ON/OFF</span></h3><button class=\"toggle-btn on\" id=\"toggleFaucet\" onclick=\"toggleFaucet()\">ON</button></div>";
  html += "<div class=\"water-status\"><h3>Water Status</h3><div class=\"status-icon\"><span class=\"lock-icon\">" + lockIcon + "</span><p>" + statusText + "</p></div></div></div>";
  html += "<button class=\"demo-btn\" onclick=\"openDemo()\">Demonstration ➔</button></div></div><footer><p>Copyright ©2024 Group Robotics Project</p><br><button class=\"contact-btn\" onclick=\"openContact()\">Contact us!</button></footer>";

 
  html += "<script>function toggleFaucet() { var toggleBtn = document.getElementById(\"toggleFaucet\"); if (toggleBtn.classList.contains(\"on\")) { toggleBtn.classList.remove(\"on\"); toggleBtn.classList.add(\"off\"); toggleBtn.textContent = \"OFF\"; } else { toggleBtn.classList.remove(\"off\"); toggleBtn.classList.add(\"on\"); toggleBtn.textContent = \"ON\"; } fetch(\"/toggle\"); }";
  html += "function logout() { window.location.href = 'https://efaucet-login.netlify.app/'; } function openDemo() { window.location.href = 'https://www.youtube.com/shorts/lmIIYR5LBqw'; } function openContact() { window.location.href = 'https://nathandevelopments.netlify.app/'; }";
  
  
  if (isFull) {
    html += "alert('Hello: Water is Full!');";
  }

  html += "</script></body></html>";
  
  return html;
}

void handleRoot() {
  server.send(200, "text/html", getHTMLPage());
}

void handleToggle() {
  if (!isFull) { 
    pumpState = !pumpState;
    if (pumpState) {
      Serial.println("ON");  
    } else {
      Serial.println("OFF");  
    } 
  } else {
    Serial.println("Water is full, pump will remain off.");
  }
  server.send(200, "text/html", getHTMLPage());
}

void checkWaterStatus() {
  isFull = digitalRead(waterSensorPin) == HIGH;
  if (isFull) {
    sendSignalToArduino("Water Dectected, Water pump turned off!");
  }
}


void handleWaterStatus() {
  String jsonResponse = "{\"isFull\": " + String(isFull ? "true" : "false") + "}";
  server.send(200, "application/json", jsonResponse);
}


void setup() {
  Serial.begin(115200); 
  pinMode(waterSensorPin, INPUT);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
   server.on("/water-status", handleWaterStatus); 
  server.begin();
}


void loop() {
  server.handleClient();
  checkWaterStatus();
}
