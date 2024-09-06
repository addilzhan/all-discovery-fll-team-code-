#include <Wire.h>                                
#include <iarduino_I2C_pH.h>                   
iarduino_I2C_pH sensor(0x09);                   
                                              
void setup(){                                    
     Serial.begin(9600);                         
     sensor.begin(&Wire);                         
}                                                 
                                                  
void loop(){                                      
     Serial.print("Кислотность = " );             
     Serial.print(sensor.getPH() ,1);             
     Serial.print(" pH.\r\n"       );            
     delay(1000);                                 
}                     
