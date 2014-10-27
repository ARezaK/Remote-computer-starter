char val;
void setup(){


  //enable serial data print 
  Serial.begin(9600); 

}


void loop() {

  
//Connect PINS 3 and 4 to the Power pins on motherboard, connect PINS 5 and 6 to Reset pins on motherboard, connect PINS 7 and 8 to Clear CMOS pins on motherboard, connect PIN 9 to the green power pin on a power supply
while(Serial.available() > 0) {
    val = Serial.read();
    if (val == 'N'){ //turn computer ON or OFF
       //changes both pins to output, writes low and then switches back to input. This is done because simply changing the pin to output occasionally causes the intended action to be performed
           pinMode(3, OUTPUT); 
           delay(500);
           digitalWrite(3, LOW); 
           delay(500);
           pinMode(3, INPUT);
           delay(100);
           pinMode(4, OUTPUT);
           delay(500);
           digitalWrite(4, LOW); 
           delay(500);
           pinMode(4, INPUT);
    }
    if (val == 'F'){  //reset computer
           pinMode(5, OUTPUT);
           delay(500);
           digitalWrite(5, LOW); 
           delay(500);
           pinMode(5, INPUT);
           delay(100);
           pinMode(6, OUTPUT);
           delay(500);
           digitalWrite(6, LOW); 
           delay(500);
           pinMode(6, INPUT);
  }
  if (val == 'C'){  //clear cmos
           pinMode(7, OUTPUT);
           delay(500);
           digitalWrite(7, LOW); 
           delay(500);
           pinMode(7, INPUT);
           delay(100);
           pinMode(8, OUTPUT);
           delay(500);
           digitalWrite(8, LOW); 
           delay(500);
           pinMode(8, INPUT);
  }
  if (val == 'P'){  //Turn on power supply
           pinMode(9, OUTPUT);
           delay(500);
           digitalWrite(9, LOW); 
  }
  if (val == 'S'){  //Turn off power supply
           pinMode(9, OUTPUT);
           delay(500);
           digitalWrite(9, HIGH); 
  }
 
}
}



