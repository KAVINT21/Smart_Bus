#include <Servo.h>// library for servo motor
#include <LiquidCrystal.h>// library for LCD
#include <SPI.h>// library for rfid
#include <MFRC522.h>// library for rfid
//#include "pitches.h" //add Equivalent frequency for musical note
//#include "themes.h" //add Note vale and duration 
Servo myservo;  // create servo object to control a servo

//Arduino pins for LCD
LiquidCrystal lcd(A1, A0, 5, 4, 3, 2);// Arduino pins for LCD

//Arduino pins for RFID
#define RST_PIN         8           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

//Arduino pins for Ultrasonic sensor
#define echoPin 6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 7 //attach pin D3 Arduino to pin Trig of HC-SR04

int pos = 0;    // variable to store the servo position

// define variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int object_distance; // variable for the distance measurement
int fare; // Cost of travelling
const int buzzer = A2;
String bal;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(buzzer, INPUT_PULLUP); //Button 1 with internal pull up
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card
  Serial.println(F("Read & Write personal data on a MIFARE PICC "));
  lcd.begin(16,2); // initializing the LCD
  //lcd.setCursor(0,0); // setting the place for displaying the first data line
  //lcd.print("Braking Test"); //data to be displayed
  pinMode (A3, OUTPUT); // Led pin OUTPUT
}

void loop() {
  digitalWrite(A3,HIGH);
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = 94 - (duration * 0.034 / 2); // Speed of sound wave divided by 2 (go and back)
  object_distance = duration * 0.034 / 2; // Distance of any object in front of Ultrasonic sensor
  fare=distance*2;
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  /*
  lcd.setCursor(2,0);
  lcd.print("Distance");
  lcd.setCursor(6,1);
  lcd.print(distance);
  delay(100); // keep the text on LCD 1 second
  lcd.clear();
  delay(10);*/
  if(object_distance >= 10){
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    break;
  }}
  if(object_distance <= 10){
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    /*
    tone(buzzer, 100); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec*/
    //Play_CrazyFrog();
    break;
  }}
                                                                                           
// Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  Serial.print(F("Balance: "));

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      bal=bal+char(buffer1[i]);
      Serial.write(buffer1[i]);
    }
  }
  Serial.print(" ");
  

  

  //----------------------------------------

  Serial.println(F("\n**End Reading**\n"));
  Serial.println(bal);
  Serial.println(bal.toInt()-fare);
  int rem_bal=bal.toInt()-fare;
  bal="";


   Serial.println("Writing to Data Block...");
   byte blockData [16] = {rem_bal};
   int blockNum = 4;  
   WriteDataToBlock(blockNum, blockData);
  lcd.setCursor(0,0);
  lcd.print("Balance");
  lcd.setCursor(0,1);
  lcd.print(rem_bal);

   Serial.print("\n");
   byte readBlockData[18];
   Serial.println("Reading from Data Block...");
   ReadDataFromBlock(blockNum, readBlockData);
   //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
   
   Serial.print("\n");
   Serial.print("Data in Block:");
   Serial.print(blockNum);
   Serial.print(" --> ");
   for (int j=0 ; j<16 ; j++)
   {
     Serial.write(readBlockData[j]);
   }
   Serial.print("\n");
  delay(2000); //change value if you want to read cards faster

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

MFRC522::StatusCode status;
MFRC522::MIFARE_Key key;  
byte bufferLen = 18;

void WriteDataToBlock(int blockNum, byte blockData[]) 
{
  /* Authenticating the desired data block for write access using Key A */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Authentication failed for Write: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Authentication success");
  }

  
  /* Write data to the block */
  status = mfrc522.MIFARE_Write(blockNum, blockData, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Writing to Block failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Data was written into Block successfully");
  }
  
}



void ReadDataFromBlock(int blockNum, byte readBlockData[]) 
{
  /* Authenticating the desired data block for Read access using Key A */
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     Serial.print("Authentication failed for Read: ");
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    Serial.println("Authentication success");
  }

  /* Reading data from the Block */
  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Block was read successfully");  
  }
  
}
