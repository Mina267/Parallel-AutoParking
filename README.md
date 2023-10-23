## 🚗 Auto Parking System 🚗
🚙 Car Start Searching for a parking spot by two side ultrasonic sensors, the front sensor detect the required ‎width and start calculating distance (D=V⁄T) ‎

🚙 When the Side back ultrasonic sensor also reads the car width and forward gets the required distance for ‎parking the car starts parking protocol.‎

🚙 Parking Protocol Steps:‎

    🏁First step: Move Forward of car length distance (Motor CW).‎
    🚖Second step: Change the direction of the front wheels by Servo motor 45°C and backward move CCW.‎
    🚘Third step: Servo 90° and motor CCW.‎
    🚘 Fourth step: Servo 135° and motor CCW.‎
    🚨 Fifth step: Servo 90° and car adjust. Its position is by using two backward ultrasonic sensors. If it is so close ‎to the back car (Object).‎
    
🚧 From the First Step to the third step, if two backward ultrasonics detect a barrier that makes the car ‎cannot parking, the car waits for time if this barrier is not removed. Car reverse parking steps from step ‎three to first but motor CW

🔭 Then start searching for a new parking spot.‎

☎️ All system status print in LCD and send ☎️ messages with UART to identify system status.‎


##  👷Implementations:‎
‎✅ ‎Implement MCAL layer (a timer, DIO, UART …)‎‎

✅ ‎Implement HAL layer Drivers (Motor, LCD, ultrasonic, Servo,…..)‎

‎✅ ‎Implement an Ultrasonics read App read from four Ultrasonics with the ‎same Input capture Unit.‎‎

‎✅ Service of UART Sends and Receives string and frame through UART ‎‎(using Queues and Stacks).‎

‎✅ Implement a Temperature filter for the temp sensor.‎

‎✅ ‎Control Motor Speed and Servo position by PWM

✅ ‎Implement service layer for UART‎d.‎

‎✅ Make a Schedule for Tasks.‎

‎✅ ‎Service of UART that Send string through UART (using Queue).‎ ‎
