# IoT-Based-Accident-Alert-System-Location-Tracker-Using-GPS

This project is an IoT-based accident alert system designed to track the location of vehicles using GPS. In the event of an accident, the system sends an alert notification with the vehicle's current location to predefined contacts or emergency services.

## Features:

- **Accident Detection**: Uses sensors (like accelerometers or gyroscopes) to detect an accident or collision.
- **GPS Tracking**: Provides the current location of the vehicle via GPS module.
- **Real-Time Alerts**: Sends alert notifications to predefined contacts with the vehicle’s location using GSM or Wi-Fi.
- **User Interface**: Can be integrated with a mobile app or web dashboard for real-time monitoring.

## Components Used:

- **Microcontroller**: ESP32
- **GPS Module**: Used for real-time location tracking.
- **GSM Module** (Optional): For sending SMS alerts in case Wi-Fi is unavailable.
- **Accelerometer/Gyroscope/Vibration Sensor**: To detect accidents by measuring sudden changes in motion. Vibration Sensor SW-420 was used.
- **Buzzer/LED**: For local alert signals in case of an accident.
- **Power Supply**: A 9V or 12V battery.

## How It Works:

1. **Initialization**: The microcontroller initializes the GPS and sensor modules.
2. **Accident Detection**: The accelerometer/gyroscope constantly monitors the motion. If an abnormal or high impact is detected, it triggers the system.
3. **GPS Location Tracking**: After detecting an accident, the GPS module retrieves the current location coordinates (latitude and longitude).
4. **Alert Notification**: The system sends an SMS or a web-based notification with the accident's location to emergency contacts.
5. **Tracking**: Continuous location tracking until the situation is resolved.

## Circuit Diagram:

![Circuit diagram](https://github.com/user-attachments/assets/4897d672-f9e8-4157-b5a6-3b4a57926205)

## Software & Libraries:

- **Arduino IDE** or any compatible platform for microcontroller programming.
- **Libraries**:
  - TinyGPS++ (for GPS communication)
  - SoftwareSerial (for GSM communication)
  - Any necessary sensor libraries (for accelerometer/gyroscope)

## Installation & Setup:

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/IoT-Based-Accident-Alert-System-Location-Tracker-Using-GPS.git
   ```
2. Open the project in Arduino IDE or any other platform.
3. Install required libraries using Arduino Library Manager.
4. Upload the code to your microcontroller.
5. Connect the components as per the circuit diagram.
6. Configure your GSM or Wi-Fi module with the necessary credentials.
7. Set the emergency contact numbers in the code for alert notifications.

## Usage:

- Once powered on, the system starts monitoring for accidents and location data in real-time.
- In the case of an accident, an alert is sent to the configured contacts with the exact GPS coordinates.
- Use the coordinates to track the vehicle’s location via Google Maps or any other tracking service.

## Future Enhancements:

- Integrate with a mobile app for easier monitoring and alerts.
- Add voice assistance or pre-recorded messages to alert emergency services.
- Improve accident detection algorithms to reduce false positives.

## License:

This project is open-source and available under the MIT License.
