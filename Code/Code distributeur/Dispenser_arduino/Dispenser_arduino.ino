#include <Servo.h>
#include <Wire.h>
Servo servo1;
int pos, pos1, pos2, pos3;
void setup() {
  servo1.attach(2);
  pos3=0;
  servo1.write(13);
  Serial.begin(9600);  // initialisation du capteur
  pinMode(SCL,INPUT);     //pin du capteur
          

}

void loop() { // VALEURS DU SERVO ENTRE 40 ET 150 PAS PLUS NI MOINS!!! sinon ça casse
  short val=0;
  val=digitalRead(SCL);
  Serial.println((int)val);
  delay(1000);
  if (pos3!=5){          //boucle tant que 5 bloc ne sont pas distribués
    if (val==1){        // Quand le capteur ne détecte plus de bloc devant lui.
      servo1.write(150);
      delay(1000);
      servo1.write(13);
      delay(2000);
      pos3 +=1;         //pos 3 c'est le nombre de cube, ici le programme 
                        //s'arrete quand pos =5 , autrement dit quand on a bougé 5 cubes.
    }
  }


}
