// attendance + Enroll + Delete + EmptyDatabase

#include <SPI.h>
#include <Ethernet.h>

uint8_t id;


// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

 IPAddress server(192,168,1,20);  // Server numeric IP


// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 177);

EthernetClient client;

 String addr1= "GET /prepaid_e_bill/set.php?id=";
String addr3 ;
String addr5 = " HTTP/1.1";


// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 8;     // the number of the pushbutton pin
const int buttonPin2 = 9;     // the number of the pushbutton pin

const int ledPin = 7;     // the number of the led pin
const int relayPin = 6;     // the number of the relay pin


// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
String op="";
int counts = 0;
int u_id = 1;
int watt = 0;

void setup() {
  Serial.begin(9600);


 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("\n\nWellcome TO Botmaster..."); 

pinMode(ledPin, OUTPUT);
pinMode(relayPin, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1 , INPUT);
              digitalWrite(ledPin, LOW);
              digitalWrite(relayPin, HIGH);
              delay(500);
              digitalWrite(relayPin, LOW);
              delay(500);
              digitalWrite(relayPin, HIGH);
                    
  Ethernet.begin(mac, ip);    //************** C -******************

    delay(500);
  Serial.println("connecting...");
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    
    Serial.println("Status: 200 \n\n\n");
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  
} // end of setup

 
void loop() {

    buttonState1 = digitalRead(buttonPin1);
  
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState1 == HIGH) {
      // turn LED on:
      
      Serial.print("\n\n ON: ");
    } else {
      // turn LED off:
      if(op!="0"){
        
      
          digitalWrite(ledPin, LOW);
                Serial.print("\n\n AUTO MODE: ");
                Serial.print(counts);
                counts++;
                if(counts> 100){
                  digitalWrite(ledPin, HIGH);
                  counts=0;
                  digitalWrite(ledPin, LOW);
                  delay(100);
                  watt++;
                  if(watt==2){
                     pushData(u_id);
                     delay(10);
                     watt=0;  
  
                  }
                }
                delay(100);
        }
    }
  
// if there are incoming bytes available
  // from the server, read them and print them:
  op="";
   if (client.available()) {
      do{
     char c = client.read();
     op += c;
     Serial.print(c);  // to see the value 
  //   digitalWrite(ledPin, atoi(c));      // atoi is a function to convert ascii to integer

     }while(client.available());
      Serial.print("\n\n FinalSTR: ");
      Serial.print(op);
      delay(1);
      if(op=="0"){
         digitalWrite(relayPin, LOW);
          digitalWrite(ledPin, HIGH);
          Serial.print("Balance is zero!");
      }else{
          digitalWrite(relayPin, HIGH);
          digitalWrite(ledPin, LOW);        
      }
   }

} //end of loop


void pushData(int x){

      client.stop();

  if (client.connect(server, 80)) {
 //   Serial.println("connected");
    // Make a HTTP request:
    addr1 = "GET /prepaid_e_bill/set.php?id=";
    addr3 = x;
    addr1 += addr3;
//    addr1 += addr5;
    client.println(addr1);
    client.println("Host: 192.168.1.20:80");
    client.println("Connection: close");
    client.println();

    
 //   Serial.println(addr1);
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
//     Serial.println(addr1);
 
/********************************************************************/
}







