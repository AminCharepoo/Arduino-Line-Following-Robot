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


// Sound Sensor
const int Echo = 12;
const int Trig = 13;

int getDistance() {
    // trigger an ultrasonic wave for 20 microseconds
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(20);
    digitalWrite(Trig, LOW);
    // calculation converting time until signal returned to distance
    float Fdistance = pulseIn(Echo, HIGH);
    Fdistance = Fdistance / 58;
    // returns an integer as the distance (in cm) sensed
    return (int)Fdistance;
}



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
    // Serial.println("Turning Right");
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

float swingReduction = 0.15;
void swingTurnRight(int carSpeed) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, HIGH);
    analogWrite(PWMA, swingReduction * carSpeed);
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
    analogWrite(PWMB, swingReduction * carSpeed);
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

    // Set the ultrasonic sensor pins
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);

    // Line sensor on the 4.0 is analog so no need to use pinMode

    // Start serial monitor
    Serial.begin(9600);
}

int testDivision = 2;
int test(int speed) {
    return (speed / testDivision);
}

int minValue(int a, int b) {
    if (a < b) { return a;}
    else { return b;}
}


int threshold = 450;
int left = 0;
int right = 0;
int middle = 0;

int swingSpeed = 70;
int turnSpeed = 40;
int forwardSpeed = 40;

char lastDet = 'F';
char secondLastDet = 'F';
int detectedCount = 0;

bool debugLine = false;
bool debugDistance = true;

leftDistance = 0;
rightDistance = 0;

void loop() {
    left = analogRead(LTleftSensor);
    right = analogRead(LTrightSensor);
    middle = analogRead(LTmiddleSensor);

    // if (left < threshold && right < threshold && middle < threshold) {
    //     forward(forwardSpeed);

    //     int distance = getDistance(); // Get the distance from the ultrasonic sensor
    //     if (debugDistance) {
    //         Serial.print("Distance: ");
    //         Serial.println(distance);
    //     }

    //     if (distance <= 10) {

    //     }
    // }

    
    // Serial.print("Left: ");
    // Serial.println(left);
    // Serial.print("Middle: ");
    // Serial.println(middle);
    // Serial.print("Right: ");
    // Serial.println(right);
    

    if (left > threshold) {
        if (debugLine) {Serial.println("Left Detected");}
        swingTurnLeft(swingSpeed);
        // turnLeft(turnSpeed);
        // if (lastDet != 'L') {
        //     detectedCount = 0;
        // }
        // detectedCount = detectedCount + 1;
        // detectedCount = minValue(detectedCount, 3);
        lastDet = 'L';
    }
    else if (right > threshold) {
        if (debugLine) {Serial.println("Right Detected");}
        swingTurnRight(swingSpeed);
        // turnRight(turnSpeed);
        // if (lastDet != 'R') {
        //     detectedCount = 0;
        // }
        // detectedCount += 1;
        // detectedCount = minValue(detectedCount, 3);
        lastDet = 'R';
        
    }
    else if (middle > threshold) {
        if (debugLine) {Serial.println("Middle only Detected");}
        forward(forwardSpeed);
        if (lastDet != 'F') {
            detectedCount = 0;
        }
        lastDet = 'F';
        detectedCount += 1;
        detectedCount = minValue(detectedCount, 3);
    }
    else {
        if (debugLine) {
        Serial.println("No line detected");
        Serial.print("Left: ");
        Serial.println(left);
        Serial.print("Middle: ");
        Serial.println(middle);
        Serial.print("Right: ");
        Serial.println(right);
        }
        

        if (lastDet == 'L') {
            if (debugLine) {Serial.println("Last detected: Left");}
            while (middle < threshold) {
                middle = analogRead(LTmiddleSensor);
                swingTurnLeft(swingSpeed);
            }
            if (debugLine) {Serial.println("Middle redetected!");}
        }
        else if (lastDet == 'R') {
            if (debugLine) {Serial.println("Last detected: Right");}
            while (middle < threshold) {
                middle = analogRead(LTmiddleSensor);
                swingTurnRight(swingSpeed);
            }
            if (debugLine) {Serial.println("Middle redetected!");}
        }
        else {
            while (middle < threshold) {
                middle = analogRead(LTmiddleSensor);
                back(forwardSpeed);
            }
            if (debugLine) {Serial.println("Middle redetected!");}
        }
    }

    
    delay(5);
}
