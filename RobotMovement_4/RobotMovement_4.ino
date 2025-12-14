// Standby pin is used to turn on and off the motor driver
const int STBY = 3;
// PWM Channel A and B are used to control the speed of the motors
const int PWMA = 5;
const int PWMB = 6;
// Input Channels A and B are used to control the direction of the motors
const int AIN1 = 7;
const int BIN1 = 8;

// Line Tracker Sensor Pins
const int LTleftSensor = A2;
const int LTmiddleSensor = A1;
const int LTrightSensor = A0;
// Left motor truth table
// Here are some handy tables to show the various modes of operation.
// STBY         AIN1            Description
// LOW      Not Applicable      Motor is off
// HIGH         LOW             Motor is on and turning backwards
// HIGH         HIGH            Motor is on and turning forwards

// Right motor truth table
// Here are some handy tables to show the various modes of operation.
// STBY         BIN1            Description
// LOW      Not Applicable      Motor is off
// HIGH         LOW             Motor is on and turning backwards
// HIGH         HIGH            Motor is on and turning forwards

/**
 * @brief Moves the robot forward with the given speed
 *
 * @param carSpeed an integer representing the car's speed.
 * This value is capped at 255 and passing in a higher value will
 * cap at 255
 */
void forward(int carSpeed) {
    // Enable the motor driver
    digitalWrite(STBY, HIGH);
    // Set the direction of the motors
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, HIGH);

    // Write speed to 'A' and 'B' MotorGroups
    analogWrite(PWMA, carSpeed);
    analogWrite(PWMB, carSpeed);
}

/**
 * @brief Moves the robot backwards with the given speed
 *
 * @param carSpeed an integer representing the car's speed.
 * This value is capped at 255 and passing in a higher value will
 * cap at 255
 */
void back(int carSpeed) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    analogWrite(PWMA, carSpeed);
    analogWrite(PWMB, carSpeed);
}

/**
 * @brief Turns the robot left with the given speed
 *
 * @param carSpeed an integer representing the car's speed.
 * This value is capped at 255 and passing in a higher value will
 * cap at 255
 */
void turnLeft(int carSpeed) {
    Serial.println("Turning Left");
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, LOW);
    analogWrite(PWMA, carSpeed);
    analogWrite(PWMB, carSpeed);
}


/**
 * @brief Turns the robot right with the given speed
 *
 * @param carSpeed an integer representing the car's speed.
 * This value is capped at 255 and passing in a higher value will
 * cap at 255
 */
void turnRight(int carSpeed) {
    Serial.println("Turning Right");
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, HIGH);
    analogWrite(PWMA, carSpeed);
    analogWrite(PWMB, carSpeed);
}

void turndeg(int deg, char direction) {
    if (direction == 'R') {
        turnRight(80);
    } else if (direction == 'L') {
        turnLeft(80);
    } else {
        return; // Invalid direction
    }

    delay(deg*8.222);  // crude timing-based turn

    stop(); // <-- Add this so the robot stops after turning
}

void drive(int dist, char direction) {
    if (direction == 'F') {
        forward(80);
    } else if (direction == 'B') {
        back(80);
    } else {
        return; // Invalid direction
    }

    delay(dist*100);  // crude

    stop(); // <-- Add this so the robot stops after turning
}

/**
 * @brief Moves the robot in a swing turn to the left. A swing turn is when only one side of the robot's drivebase is powered.
 *
 * @param carSpeed an integer representing the car's speed.
 * This value is capped at 255 and passing in a higher value will
 * cap at 255
 */
void swingTurnRight(int carSpeed) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, HIGH);
    analogWrite(PWMA, 0.25 * carSpeed);
    analogWrite(PWMB, carSpeed);
}

/**
 * @brief Moves the robot in a swing turn to the right. A swing turn is when only one side of the robot's drivebase is powered.
 *
 * @param carSpeed an integer representing the car's speed.
 * This value is capped at 255 and passing in a higher value will
 * cap at 255
 */
void swingTurnLeft(int carSpeed) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, HIGH);
    analogWrite(PWMA, carSpeed);
    analogWrite(PWMB, 0.25 * carSpeed);
}

/**
 * @brief Stops the robot's drive motors.
 */
void stop() {
    digitalWrite(STBY, LOW);
}

void setup() {
    // Configure all of these pins as outputs
    pinMode(STBY, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(BIN1, OUTPUT);

    // Line sensor on the 4.0 is analog so no need to use pinMode

    // Start serial monitor
    Serial.begin(9600);
}

int threshold = 450;
char lastdir = 'F';

void loop() {
    // put your code here!

    // here, we're moving the bot forward at speed 250...
    //
    // stopping the bot...
    // wait for 5 seconds before running again
   //delay(1000);

    //turndeg(90, 'L');
    //drive(20, 'F');
    //delay(50);
    //turndeg(90,'R');
    // Start by printing the sensor values - tune them to your environment
    
    
    /**
    if ((analogRead(LTleftSensor) > threshold) && (analogRead(LTmiddleSensor) > threshold)) {
        turnLeft(40);
        delay(150);
        lastdir = 'L';
    } else if ((analogRead(LTrightSensor) > threshold) && (analogRead(LTmiddleSensor) > threshold)) {
        turnRight(40);
        delay(150);
        lastdir = 'R';
    } else*/
    if (analogRead(LTmiddleSensor) > threshold) {
        if ((analogRead(LTleftSensor) < threshold) && (analogRead(LTrightSensor) < threshold)) {
            forward(70);
            lastdir = 'F';
        } else if ((analogRead(LTleftSensor) > threshold) && (analogRead(LTrightSensor) < threshold)) {
            turnLeft(40);
            lastdir = 'L';
        } else if ((analogRead(LTrightSensor) > threshold) && (analogRead(LTleftSensor) < threshold)) {
            turnRight(40);
            lastdir = 'R';
        } else {
            if (lastdir == 'F'){
                forward(70);
            } else if (lastdir == 'L'){
                swingTurnLeft(80);
            } else if (lastdir == 'R'){
                swingTurnRight(80);
            }
        }

        //Serial.println(analogRead(LTleftSensor));
        //Serial.println(analogRead(LTleftSensor));
    } else if (analogRead(LTleftSensor) > threshold) {
        //Serial.println(analogRead(LTleftSensor));
        swingTurnLeft(40);
        lastdir = 'L';
    } else if (analogRead(LTrightSensor) > threshold) {
        //Serial.println(analogRead(LTleftSensor));
        swingTurnRight(40);
        lastdir = 'R';
    } else {
        Serial.println("No line detected");
        if (lastdir == 'F'){
            forward(70);
        } else if (lastdir == 'L'){
            swingTurnLeft(100);
        } else if (lastdir == 'R'){
            swingTurnRight(100);
        }
    }
}
