const byte numChars = 64;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int stage = 0;



void setup() {
 pinMode(LED_BUILTIN, OUTPUT);
 myservo.attach(9);  // attaches the servo on pin 9 to the servo object  
 myservo.write(0);    
 Serial.begin(9600);
 Serial.println("Please enter the password: ");
 Serial.println("Do not touch other parts of this computer. Only use this terminal");
}

void loop() {
 recvWithEndMarker();
 showNewData();
}

void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 // if (Serial.available() > 0) {
           while (Serial.available() > 0 && newData == false) {
 rc = Serial.read();

 if (rc != endMarker) {
 receivedChars[ndx] = rc;
 ndx++;
 if (ndx >= numChars) {
 ndx = numChars - 1;
 }
 }
 else {
 receivedChars[ndx] = '\0'; // terminate the string
 ndx = 0;
 newData = true;
 }
 }
}

void showNewData() {
 if (newData == true) {
 //Serial.print("This just in ... ");
 Serial.println(receivedChars);
 if ((strcmp(receivedChars, "CRUMBS SWEETS") == 0) && (stage == 0)) {
  Serial.println("Unlocking...");
  myservo.write(180);  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  //Serial.println("Enter 'Lock' to relock the box");
  Serial.println("You've found your way to a candy house! Find the clues hidden on the wall to figure out who lives here.");
  Serial.println("Please leave the clues on the wall. Yell down the clues to your teammates.");
  Serial.println("");
  Serial.println("Climber 1: L33 E13 F25 N15 A21");
  Serial.println("Climber 2: J27 E12 G39 A19 D30");
  Serial.println("Enter the words that these rocks spell separated by a space: ");
  stage++;
  //Serial.println("New stage");
  //Serial.println(stage);
 }
 else if ((strcmp(receivedChars, "CANDY WITCH") == 0) && (stage == 1)) {
  Serial.println("Congratulations Climbers 1 and 2!");
  Serial.println("");
  Serial.println("The witch is very nice and hospitable to you, but you're growing suspicious of her. Figure out what her plan is.");
  Serial.println("");
  Serial.println("Climber 3: I20 D2 C14 E33 M12");
  Serial.println("Climber 4: D34 H8 D20 F35 I18");
  Serial.println("Enter the words that these rocks spell separated by a space: ");
  stage++;
  //Serial.println("New stage");
  //Serial.println(stage);
 }
 else if ((strcmp(receivedChars, "CAGES OVENS") == 0) && (stage == 2)) {
  Serial.println("Congratulations Climbers 3 and 4!");
  Serial.println("");
  Serial.println("Oh no! She's going to fatten you up and eat you! Quick, find a way to get out!");
  Serial.println("");
  Serial.println("Climber 5: G28 B10 H22 G7 J28");
  Serial.println("Enter the word that these rocks spell: ");
  stage++;
  //Serial.println("New stage");
  //Serial.println(stage);
 }
 else if ((strcmp(receivedChars, "MOORE") == 0) && (stage == 3)) {
  Serial.println("Congratulations Climber 5!");
  Serial.println("");
  Serial.println("You've successfully escaped! Now you can go back to your home (aka the place you just solved for)");
  Serial.println("139");
  Serial.println("");
  Serial.println("Jk, change of plans, you're headed to Tom's instead");
 }
 else if (strcmp(receivedChars, "Lock") == 0) {
  Serial.println("Locking...");
  myservo.write(0); 
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  Serial.println("Please enter the password: ");
  stage = 0;
 }
 else
 {
  Serial.println("Wrong password. Please try again: ");
 }
 newData = false;
 }
}
