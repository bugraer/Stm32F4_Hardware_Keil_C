int sensorPin = A0;                //Sensörü bağlayacağımız pin Su Seviyesi / Yağmur Sensörü
int esikDegeri = 100;              
int buzzerPin = 8;                 
int veri;                         

int esikDegeri1 = 400;               // MQ-2  -MQ-2-MQ-2-MQ-2-MQ-2-MQ-2
int deger;                       

int sensorPin1 = 9;                  //DHT11-DHT11-DHT11-DHT11-DHT11-DHT11-DHT11
int veri1; 

char blue;                           //hc06-hc06-hc06-hc06

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  pinMode(13,OUTPUT);

 cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15624;
 
  TCCR1B |= (1 << WGM12);

  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  sei();

}
ISR(TIMER1_COMPA_vect){
  digitalWrite(13,1);
Serial.println("Sulama");
for(int a=0;a<5000;a++)
digitalWrite(13,0);
}
void loop() {
  
  if (Serial.available()>0){
  veri=Serial.read();
  if(veri=='1'){
digitalWrite(13,1);
Serial.println("Sulama");
}

if (veri=='0'){
digitalWrite(13,0);
Serial.println("Sulama" );
}
}


  veri = analogRead(sensorPin);   
  deger = analogRead(A0);           
  veri1 = digitalRead(sensorPin1);  
  
  if(veri > esikDegeri){           
    digitalWrite(buzzerPin, HIGH); 
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
  else{                            
    digitalWrite(buzzerPin, LOW);
  }
 
  if(deger > esikDegeri1){      
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
  else{                       
    digitalWrite(buzzerPin, LOW);
  }

  if(veri1 == true){            
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
  else{                      
    digitalWrite(buzzerPin, LOW);
  }
}

