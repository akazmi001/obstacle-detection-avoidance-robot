// Define Pins for Motors
const int motorLeftForward = 3;
const int motorLeftBackward = 4;
const int motorRightForward = 5;
const int motorRightBackward = 6;

// Define Pins for Ultrasonic Sensors
const int trigPinFront = 9;
const int echoPinFront = 10;
const int trigPinLeft = 11;
const int echoPinLeft = 12;

// Define Motor Speed
const int motorSpeed = 255; // Maximum speed (0-255)

// Define Distance Threshold (in cm)
const int distanceThreshold = 15; // When obstacle is closer than 15cm, avoid it

void setup() {
  // Initialize Motor Pins as Outputs
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);

  // Initialize Ultrasonic Sensor Pins
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);

  // Start Serial Monitor for Debugging
  Serial.begin(9600);
}

void loop() {
  // Get the distance from the ultrasonic sensors
  long durationFront, distanceFront;
  long durationLeft, distanceLeft;
  
  // Measure Front Distance
  distanceFront = getDistance(trigPinFront, echoPinFront);
  
  // Measure Left Distance
  distanceLeft = getDistance(trigPinLeft, echoPinLeft);

  // Print distances for debugging
  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  Serial.print(" cm, Left Distance: ");
  Serial.println(distanceLeft);

  // If obstacle is detected in front
  if (distanceFront < distanceThreshold) {
    // Check if there's an obstacle to the left
    if (distanceLeft > distanceThreshold) {
      // Move left if clear
      turnLeft();
      delay(1000);
    } else {
      // If left is blocked, move backward and turn right
      moveBackward();
      delay(1000);
      turnRight();
      delay(1000);
    }
  } else {
    // Continue moving forward if no obstacle in front
    moveForward();
  }
}

// Function to get the distance from the ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
  long duration;
  long distance;
  
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo time
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in cm
  distance = (duration / 2) / 29.1;
  
  return distance;
}

// Function to move robot forward
void moveForward() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

// Function to move robot backward
void moveBackward() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, HIGH);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, HIGH);
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

// Function to turn the robot left
void turnLeft() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

// Function to stop all motors
void stopMotors() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

