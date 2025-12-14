# Arduino Line-Following Robot with Obstacle Avoidance

This project is an Arduino-powered robot that follows a line using three line-tracking sensors and avoids obstacles using an ultrasonic distance sensor mounted on a servo. When an obstacle is detected, the robot scans left and right, chooses the clearer path, and continues navigating.

This project was built as a hands-on robotics exercise combining motor control, sensors, and basic autonomous decision-making.

---

## Features

- Line following using three analog line tracker sensors (left, middle, right)
- Smooth swing turns for better line tracking
- Obstacle detection using an ultrasonic sensor
- Servo-based distance scanning to choose the best turn direction
- Motor control using an H-bridge motor driver
- Serial debugging output for sensor values and decisions

---

## Hardware Used

- Arduino (Uno or compatible)
- Motor driver (H-bridge, e.g. TB6612FNG or similar)
- 2 DC motors with wheels
- 3× line tracking sensors (analog)
- Ultrasonic sensor (HC-SR04)
- Servo motor
- Robot chassis
- Battery pack
- Jumper wires

---

## Pin Configuration

### Motor Driver
| Pin | Function |
|----|---------|
| 3  | Standby (STBY) |
| 5  | Motor A PWM |
| 6  | Motor B PWM |
| 7  | Motor A Direction |
| 8  | Motor B Direction |

### Line Sensors
| Sensor | Pin |
|------|-----|
| Left  | A2 |
| Middle | A1 |
| Right | A0 |

### Ultrasonic Sensor
| Pin | Function |
|----|---------|
| 13 | Trigger |
| 12 | Echo |

### Servo
| Pin | Function |
|----|---------|
| 10 | Servo Signal |

---

## How It Works

### Line Following
- The robot constantly reads the three line sensors.
- If the left sensor detects the line, the robot swing-turns left.
- If the right sensor detects the line, it swing-turns right.
- If the middle sensor detects the line, it moves forward.
- If the line is lost, the robot uses the last detected direction to recover.

### Obstacle Avoidance
- The ultrasonic sensor checks for obstacles ahead.
- If an object is closer than ~10 cm:
  - The robot stops
  - The servo rotates the sensor left and right
  - The robot compares distances
  - It turns toward the direction with more space
  - The robot recenters the servo and continues

---

## Adjustable Parameters

You can tune these values in the code to improve performance:

```cpp
int threshold = 450;     // Line detection threshold
int swingSpeed = 70;
int turnSpeed = 40;
int forwardSpeed = 40;
float swingReduction = 0.15;

```
## Known Limitations

Turning angles and distances are time-based (no encoders)

Line threshold may need calibration depending on surface and lighting

Obstacle avoidance is basic and not map-based


## Future Improvements

Add wheel encoders for precise turning

Implement PID control for smoother line following

Improve obstacle avoidance logic

Clean up state handling in the main loop

## Outcomes
Won first place in the end of year competition against 3 other teams. 

## Team Members
Amin Charepoo
Victor Li
