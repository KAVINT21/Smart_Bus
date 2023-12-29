# Smart_Bus
This was an IoT project which provides alternative solution for Conductor-Based Ticket System in Bus.

# Problem Statement:

In our day-to-day life we choose to travel using the government or private public transports like train, bus, etc.
Our project mainly focuses on solving 3 such problems while traveling in bus.
1.	Getting the correct change from the conductor would be one of the most hectic tasks when you are traveling in a government bus. Usually, the conductor would collect the money and delay if he doesn’t have the correct change. This would make us anxious throughout the journey in the bus.
2.	These days none of the buses halt at the correct position in front of the bus stop.
3.	Waiting at the bus stop without knowing that a bus would arrive at that time will also make us anxious.

# Objective:
	The Objective of this project is to give solution for the 3 problem statements given above using 3 electronic prototypes.

1.	Smart Bus:
The smart bus would contain a card tapping system and a sensor that calculates the distance travelled by the person in the bus. Based on the distance travelled, the amount would be detected from the card.
2.	Recharging System:
The recharging system would also contain a card tapping system that gets the data stored in the card (i.e.) the balance in the card. It should also have a recharging algorithm that would increase the amount in the card.
3.	Bus Stop:
The bus stop should have a mechanism to indicate that the bus has reached the bus stop.

# System Requirements:
     1.	SMART BUS:
	•	Arduino Uno R3 (Microcontroller)
	•	HC-SR04 Ultrasonic Sensor
	•	Tower Pro SG90 Micro Servo Motor
	•	Active Buzzer
	•	LCD 16x2
	•	Potentiometer
	•	RC522 RFID Card Reader
	•	IR Transmitter
	•	Jumper Cables
	•	Toy Bus
    2.	Recharging System:
	•	Arduino Mega 2560 (Microcontroller)
	•	LCD 16x2
	•	Potentiometer
	•	RC522 RFID Card Reader
	•	4x4 Matrix Keypad
	•	Jumper Cable
    3.	Bus Stop:
	•	Arduino Uno R3 (Microcontroller)
	•	Tower Pro SG90 Micro Servo Motor
	•	IR Receiver
	•	Blue LED
	•	Jumper Cable

Design:

    1.Smart Bus:

      ![image](https://github.com/KAVINT21/Smart_Bus/assets/95117554/4990e551-295a-46a1-af80-25c108045256)

      HC-SR04 Ultrasonic Sensor would be placed in front of the bus to calculate the distance travelled by the bus and the distance of any obstacle in front of the bus.
      LCD 16x2 placed on the top of the bus displays the distance travelled by the passenger and the balance in the card. The Potentiometer is used to change the contrast of the LCD.
      The Servo Motor would be placed beside the back tire. If the distance of any obstacle is less than 10cm, then the servo will block the rotation of the wheel. Thereby this would act as an automatic braking 
        system.
      Once any RFID card or tag is tapped on the RFID Card Reader placed on the top of the bus, the RFID reader collects the data stored in the RFID card in the form of Hexadecimals and converts it into 
        integers for further arithmetic algorithms to take place. When that process is completed, the data will again be converted to Hexadecimals and written back in the card.
      The Arduino Uno R3 placed on top of the bus has the entire C++ code stored in it and it controls all the data received and sent using the algorithm.
      The IR Transmitter is placed at the right side of the Bus so that it emits IR rays to be detected by the bus stop.

    2.Recharging System:

      ![image](https://github.com/KAVINT21/Smart_Bus/assets/95117554/1caffcd6-6e97-40ee-804c-96e9ebf2601e)
      
      The Arduino Mega 2560 is placed inside the cardboard and all the sensors are connected to it via the jumper cables.
      The 4x4 matrix keypad placed in the front is used to collect the operations to be handled by the user to check the balance and recharge the card.
      LCD 16x2 placed in front displays the balance of the card and any other operations carried by the user. The Potentiometer is used to change the contrast of the LCD.
      The RFID Card Reader is placed at the right side of the recharging system to carry out all the operations in the card.

    
    3.Bus Stop:
    
      The IR Receiver placed 20cm in front of the bus stop receives the signal from the IR transmitter of the bus and passes this info to Arduino Uno R3.
      When the Servo motor placed at the top of the bus stop gets the info that the bus is going to reach the bus stop it rotates 180o and blocks the vision of the ultrasonic sensor. This in turn activates the 
        automatic braking system and the bus stops correctly in front of the bus stop.
      When the Servo motor rotates, the blue LED gets lit indicating that the bus is going to reach the bus stop.




      
  

