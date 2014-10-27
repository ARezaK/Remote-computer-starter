//address= http://192.168.2.20:84 

#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x00, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 2, 20 }; // ip in lan 
byte gateway[] = { 192, 168, 2, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(6881); //server port

String readString; 

//////////////////////

void setup(){

  //Ethernet.begin(mac, ip, gateway, subnet);//start the ethernet connections
  Ethernet.begin(mac);//start the ethernet connections
  server.begin(); //Tells the server to begin listening for incoming connections.

  //enable serial data print 
  Serial.begin(4800); 
 
}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); //Read the next byte received from the server the client is connected to (after the last call to read()).

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string 
          readString += c; 
          //Serial.print(c); testing
        } 

        //if HTTP request has ended
        if (c == '\n') {

          //Serial.println(readString); //print to serial monitor for debugging 

          //now output HTML data header
             if(readString.indexOf('?') >=0) { //don't send new page
               client.println("HTTP/1.1 204 ERROR");
               client.println();
               client.println();  
             }
             else {
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE>Control your computer</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");

          client.println("<H1>Ameer</H1>");
          
          client.println("<a href=\"/?Q\" target=\"inlineframe\">Turn Computer ON or OFF</a>"); 
          client.println("<a href=\"/?X\" target=\"inlineframe\">Hard Reset Computer</a>"); 
          client.println("<a href=\"/?L\" target=\"inlineframe\">Clear CMOS</a>");
          client.println("<a href=\"/?R\" target=\"inlineframe\">Turn ON Second Power Supply</a>");
          client.println("<a href=\"/?B\" target=\"inlineframe\">Turn OFF Second Power Supply</a>");

         client.println("<IFRAME name=inlineframe style=\"display:none\" >");          
          client.println("</IFRAME>");

          client.println("</BODY>");
          client.println("</HTML>");
             }

          delay(1);
          //stopping client
          client.stop();

          ///////////////////// control arduino pin
          if(readString.indexOf("Q") >0)//checks for on
          {
           Serial.print('N'); 
          }
          if(readString.indexOf("X") >0)//checks for reset
          {
          Serial.print('F');   
          }
          if(readString.indexOf("L") >0)//Checks for clear CMOS
          {
          Serial.print('C');
          }
          if(readString.indexOf("R") >0)//Checks for Turn on second PS
          {
          Serial.print('P');
          }
          if(readString.indexOf("B") >0)//Checks for Turn off second PS
          {
          Serial.print('S');
          }
          //clearing string for next read
          readString="";

        }
      }
    }
  }
} 


