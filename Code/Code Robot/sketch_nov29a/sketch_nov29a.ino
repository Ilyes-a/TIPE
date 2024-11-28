#include <paj7620.h>
#include <paj7620.h>
#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#define GES_REACTION_TIME       500             //LIBRAIRIES
#define GES_ENTRY_TIME          800             // DEFINITIONS DES VARIABLES/ SERVO
#define GES_QUIT_TIME           1000
Servo servo1;
Servo servo2;    
Servo servo3;
Servo servo4;
Servo servo5;
int servoPos1, servoPos2, servoPos3, servoPos4, servoPos5;
int X;

SoftwareSerial bluetooth(8, 9); 
char instruction;


void setup()
{
    servoPos1 = 90;       // PARTIE SERVO POSITION INITIAL SETUP
    servoPos2 = 80;
    servoPos3 = 90;
    servoPos4 = 64;
    servoPos5 = 90;
    X = 0;
    servo1.attach(2);
    servo2.attach(3); 
    servo3.attach(4); 
    servo4.attach(5);
    servo5.attach(6);
    servo1.write(servoPos1);
    servo2.write(servoPos2);
    servo3.write(servoPos3);
    servo4.write(servoPos4);           // attacher les servos
    servo5.write(servoPos5);
    uint8_t error = 0;

    bluetooth.begin(9600);       // begin bluetooth
 
    Serial.begin(9600);
    Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");
 
    error = paj7620Init();          //NE PAS TOUCHER SETUP DU GESTURE
    if (error) 
    {
        Serial.print("INIT ERROR,CODE:");
        Serial.println(error);
    }
    else
    {
        Serial.println("INIT OK");
    }
    Serial.println("Please input your gestures:\n");
}
 
void loop()
{
  
    uint8_t data = 0, data1 = 0, error;
    error = paj7620ReadReg(0x43, 1, &data);             
    if (!error) 
    {
        switch (data)                                  
        {
            case GES_RIGHT_FLAG:
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if(data == GES_FORWARD_FLAG) 
                {
                    Serial.println("Forward");  
                    delay(GES_QUIT_TIME);        // DETECTE QUAND CA AVANCE
                }
                else if(data == GES_BACKWARD_FLAG) 
                {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);        // DETECTE QUAND CA RECULE
                }
                else
                {
                    Serial.println("Right");    // DETECTE QUAND DROITE
                    if (X==0){
                      servoPos1 = 0;
                      servo1.write(servoPos1);
                      delay(500);
                      servoPos2 = 45;
                      servo2.write(servoPos2);
                      delay(500);
                      servoPos3 = 160;
                      servo3.write(servoPos3);
                      delay(500);
                      servo5.write(30);
                      X+=1;
                    }
                    
                    
                    
                }          
                break;
            case GES_LEFT_FLAG: 
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if(data == GES_FORWARD_FLAG) 
                {
                    Serial.println("Forward");
                    delay(GES_QUIT_TIME);
                }
                else if(data == GES_BACKWARD_FLAG) 
                {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);
                }
                else
                {
                    Serial.println("Left");    // DETECTE QUAND GAUCHE
                    if (X==0){
                      servoPos1 = 180;
                      servoPos2 = 45;
                      servoPos3 = 155;
                      servoPos4 = 64;
                      servoPos5 = 59;     
                      servo1.write(servoPos1);
                      delay(500);
                      servo5.write(servoPos5);
                      delay(1000);
                      servo2.write(servoPos2);
                      delay(500);
                      servo3.write(servoPos3);
                      servo4.write(servoPos4);
                      X+=1;
                      
                    }
                
                    
                    
                    
                }          
                break;
            case GES_UP_FLAG:
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if(data == GES_FORWARD_FLAG) 
                {
                    Serial.println("Forward");
                    delay(GES_QUIT_TIME);
                }
                else if(data == GES_BACKWARD_FLAG) 
                {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);
                }
                else
                {
                    Serial.println("Up");           // QUAND MONTE
                    servoPos1 = 90;
                    servoPos2 = 80;
                    servoPos3 = 90;
                    servoPos4 = 64;
                    servoPos5 = 75; 
                    
                    servo5.write(servoPos5);  
                    delay(1000);
                    servo2.write(servoPos2);
                    delay(300);
                    servo3.write(servoPos3);
                    servo4.write(servoPos4);
                    delay(500);
                    servo1.write(servoPos1);
                    X=0;
                    

                }          
                break;
            case GES_DOWN_FLAG:
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if(data == GES_FORWARD_FLAG) 
                {
                    Serial.println("Forward");
                    delay(GES_QUIT_TIME);
                }
                else if(data == GES_BACKWARD_FLAG) 
                {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);
                }
                else
                {
                    Serial.println("Down");
                }          
                break;
            case GES_FORWARD_FLAG:
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
                break;
            case GES_BACKWARD_FLAG:       
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
                break;
            case GES_CLOCKWISE_FLAG:
                Serial.println("Clockwise");
                break;
            case GES_COUNT_CLOCKWISE_FLAG:
                Serial.println("anti-clockwise");
                break;  
            default:
                paj7620ReadReg(0x44, 1, &data1);
                if (data1 == GES_WAVE_FLAG) 
                {
                    Serial.println("wave");
                }
                break;
        }
    }
    delay(100);




    if (bluetooth.available()) {
      instruction = bluetooth.read();            // PARTIE BLLUETOOTH
      Serial.println(instruction);

    } 
    if (instruction == 'R') {                   // QUAND LAPPLI ENVOIE R
      if (X==0){
        
        servoPos1 = 0;
        servo1.write(servoPos1);
        delay(500);
        servoPos2 = 45;
        servo2.write(servoPos2);
        delay(500);
        servoPos3 = 160;
        servo3.write(servoPos3);
        delay(500);
        servo5.write(30);
        instruction = 'rien';
        X+=1;
      }

      
      
    }
    if (instruction == 'L'){          // QUAND LAPPLI ENVOIE L
      if (X==0){
        
        servoPos1 = 180;
        servoPos2 = 40;
        servoPos3 = 155;
        servoPos4 = 64;
        servoPos5 = 57;     
        servo1.write(servoPos1);
        delay(500);
        servo5.write(servoPos5);
        delay(1000);
        servo2.write(servoPos2);
        delay(500);
        servo3.write(servoPos3);
        servo4.write(servoPos4);
        delay(500);
        X+=1;
                      
      }
      
      
    }
    if (instruction == 'U'){                 //QUAND LAPPLI ENVOIE U
      servoPos1 = 90;
      servoPos2 = 80;
      servoPos3 = 90;
      servoPos4 = 64;
      servoPos5 = 75; 
                    
      servo5.write(servoPos5);  
      delay(1000);
      servo2.write(servoPos2);
      delay(300);
      servo3.write(servoPos3);
      servo4.write(servoPos4);
      delay(500);
      servo1.write(servoPos1);
      X=0;
    }
    
}
