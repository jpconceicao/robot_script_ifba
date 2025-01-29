#include <Arduino.h>

void processReceivedData(String data);

const int numMotors = 5;
int motorSetpoints[numMotors];

void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino ready to receive setpoints.");
}

void loop() 
{
    if (Serial.available()) 
    {
        String receivedData = Serial.readStringUntil('\n');
        processReceivedData(receivedData);
    }
}

void processReceivedData(String data) 
{
    int index = 0;
    char *token = strtok((char *)data.c_str(), ",");
    
    while (token != NULL && index < numMotors) 
    {
        motorSetpoints[index] = atoi(token);
        token = strtok(NULL, ",");
        index++;
    }
    
    if (index == numMotors) 
    {
        Serial.print("Received setpoints: ");
        for (int i = 0; i < numMotors; i++) 
        {
            Serial.print(motorSetpoints[i]);
            if (i < numMotors - 1) Serial.print(", ");
        }
        Serial.println();
        Serial.println("Setpoints successfully stored.");
    } 
    else 
    {
        Serial.println("Error: Incorrect number of setpoints received.");
    }
}
