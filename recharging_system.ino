#include <Keypad.h> // library for keypad
#include <LiquidCrystal.h>// library for LCD
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         48           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
LiquidCrystal lcd(A1, A0, 36, 38, 40,42);// Arduino pins for LCD
const byte ROWS = 4; //initializing the rows of keypad
const byte COLS = 4;//initializing the columns of keypad
char keys [ROWS] [COLS] = { // giving values to each key of the keypad
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '=', 'D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //Arduino pins for rows of keypad
byte colPins[COLS] = {5,4,3,2}; // Arduino pins for columns of keypad
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); /* function for mapping the values on the keys*/
String num1; // variables to display the keypad integer input
String bal;
String name1;
void setup()
{
  //pinMode(A2,INPUT);
  Serial.begin(9600);
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card
  //Serial.println(F("Write personal data on a MIFARE PICC "));
  lcd.begin(16,2); // initializing the LCD
  lcd.setCursor(3,0); // setting the place for displaying the first data line
  lcd.print("RECHARGING"); //data to be displayed
  lcd.setCursor(5,1);//setting the place for displaying the second data line
  lcd.print("SYSTEM");// data to be displayed
  delay(2000);// time for which the data will be displayed on LCD
  lcd.clear();// clearing the LCD
  lcd.setCursor(0,0);// setting the place for displaying the second data line
  lcd.print("PLACE YOUR CARD");//data to be displayed
  delay(1500);// time for which the data will be displayed on LCD
  name1=mfrc522.uid.uidByte[0];
  if(name1=="83"){
    lcd.clear();// clearing the LCD
    lcd.setCursor(0,0);// setting the place for displaying the second data line
    lcd.print("- Hello  Kavin -");
    lcd.setCursor(0,1);// setting the place for displaying the second data line
    lcd.print("----------------");
  }
  if(name1=="153"){
    lcd.clear();// clearing the LCD
    lcd.setCursor(0,0);// setting the place for displaying the second data line
    lcd.print("-- Hello Bala --");
    lcd.setCursor(0,1);// setting the place for displaying the second data line
    lcd.print("----------------");
  }
  if(name1=="115"){
    lcd.clear();// clearing the LCD
    lcd.setCursor(0,0);// setting the place for displaying the second data line
    lcd.print("- Hello Deepak -");
    lcd.setCursor(0,1);// setting the place for displaying the second data line
    lcd.print("----------------");
  }
  if(name1=="211"){
    lcd.clear();// clearing the LCD
    lcd.setCursor(0,0);// setting the place for displaying the second data line
    lcd.print("- Hello  Surya -");
    lcd.setCursor(0,1);// setting the place for displaying the second data line
    lcd.print("----------------");
  }
  delay(2000);// time for which the data will be displayed on LCD
  lcd.clear();// clearing the LCD
  lcd.setCursor(0,0);
  lcd.print("A. BALANCE");
  lcd.setCursor(0,1);
  lcd.print("B. RECHARGE");
  }
void loop(){
  char key1 = myKeypad.getKey();
  if (key1 != NO_KEY && key1 == 'A'){ 
    lcd.clear();
    lcd.setCursor(0,0); // setting the place for the data to be displayed
    lcd.print("BALANCE:");// data to be displayed
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
      bal = bal + char(buffer1[i]); // storing the value of key pressed in bal
      lcd.setCursor(0, 1); // decaling the place where the first entry will be displayed
      lcd.print(bal); // printing the first number entered
      Serial.write(buffer1[i]);
    }
  }
  bal="";
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0); // decaling the place where the first entry will be displayed
  lcd.print("**** Have a ****"); // printing the first number entered
  lcd.setCursor(0, 1); // decaling the place where the first entry will be displayed
  lcd.print("*** Nice Day ***"); // printing the first number entered
  Serial.print(" ");
  //----------------------------------------
  Serial.println(F("\n**End Reading**\n"));
  delay(3000); //change value if you want to read cards faster
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  /*
  lcd.setCursor(0,0);
  lcd.print("C - CONTINUE");
  lcd.setCursor(0,1);
  lcd.print("D - REFRESH");*/
  setup();
  }

  
  if (key1 != NO_KEY && key1 == 'B'){
    
    lcd.clear();
    lcd.setCursor(0,0); // setting the place for the data to be displayed
    lcd.print("ENTER THE AMOUNT");// data to be displayed 
  }
  if (key1 != NO_KEY && (key1=='1'||key1=='2'||key1=='3'||key1=='4'||key1=='5'||key1=='6'||key1=='7'||key1=='8'||key1=='9'||key1=='0'))// check which key is pressed by checking its integer value
  {
      num1 = num1 + key1; // storing the value of key pressed in num1
      lcd.setCursor(0, 1); // decaling the place where the first entry will be displayed
      lcd.print(num1); // printing the first number entered
      Serial.println(num1);
  }
  if (key1 != NO_KEY && key1 == 'B'){
    num1="";
    lcd.setCursor(0, 1); // decaling the place where the first entry will be displayed
    lcd.print(num1); // printing the first number entered
  }
  if (key1 != NO_KEY && key1 == 'C'){
    lcd.clear();
    lcd.setCursor(0, 0); // decaling the place where the first entry will be displayed
    lcd.print("Recharging:"); // printing the first number entered
    lcd.setCursor(0, 1); // decaling the place where the first entry will be displayed
    lcd.print("Rs."); // printing the first number entered 
    lcd.setCursor(4, 1); // decaling the place where the first entry will be displayed
    lcd.print(num1); // printing the first number entered 
    delay(3000);
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
  lcd.clear();
  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  { 
    if (buffer1[i] != 32)
    {
      bal = bal + char(buffer1[i]); // storing the value of key pressed in bal
      lcd.setCursor(0, 1); // decaling the place where the first entry will be displayed
      lcd.print(bal); // printing the first number entered
      Serial.write(buffer1[i]);
    }
  }
  bal="";
  delay(2000);
  //lcd.clear();
  Serial.print(" ");
  //----------------------------------------
  Serial.println(F("\n**End Reading**\n"));
  delay(1000); //change value if you want to read cards faster
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  /*
  lcd.setCursor(0,0);
  lcd.print("C - CONTINUE");
  lcd.setCursor(0,1);
  lcd.print("D - REFRESH");*/
  //setup();
  }
  else if (key1 != NO_KEY && key1 == 'D'){
    lcd.clear();
    setup();// calling the setup function to start the code again
  }/*
  else if (key1 != NO_KEY && key1 == 'C'){
  lcd.clear();// clearing the LCD
  lcd.setCursor(0,0);
  lcd.print("1.BALANCE");
  lcd.setCursor(0,1);
  lcd.print("2.RECHARGE");
  }
  8/
  /*
  if (key != NO_KEY && key == '1'){ 
    lcd.clear();
    lcd.setCursor(0,0); // setting the place for the data to be displayed
    lcd.print("BALANCE");// data to be displayed
    Serial.println("BALANCE");
  }
  if (key != NO_KEY && key == 'C'){
    lcd.clear();
    setup();// calling the setup function to start the code again
  }
    
  if (key1 != NO_KEY && (key1=='1'||key1=='2'||key1=='3'||key1=='4'||key1=='5'||key1=='6'||key1=='7'||key1=='8'||key1=='9'||key1=='0'))// check which key is pressed by checking its integer value
  {
    if (present != true)
    {
      num1 = num1 + key1; // storing the value of key pressed in num1
      float numLength = num1.length();
      lcd.setCursor(0, 1); // decaling the place where the first entry will be displayed
      lcd.print(num1); // printing the first number entered
      Serial.println(num1);
    }
  }
    else if (key1 != NO_KEY && key1 == '='){ 
    lcd.clear();
    lcd.setCursor(1,0); // setting the place for the data to be displayed
    lcd.print("TAP YOUR CARD");// data to be displayed
    Serial.println("TAP YOUR CARD");
  }
  // condition for clearing the LCD or starting the Arduino code again
  */
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
}
