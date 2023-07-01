import serial
import time
import requests

serial_port = 'COM9' 
baud_rate = 9600

bot_token = '6125854644:AAHhO-RsXC91W8G7Uxh9NCxdj12MnEDD_qU'
chat_id = '-1001989081010'

ser = serial.Serial(serial_port, baud_rate, timeout=1)

while True:
    line = ser.readline().decode('utf-8').rstrip()

    if line:
        print(line) 
        if "Sensor Value:" in line:
            parts = line.split(":")
            if len(parts) >= 2:
                    message = line
                    sensor_value = int(float(parts[1].strip()))
                    if sensor_value < 1000:
                        ser.write(b'1')  # Turn on the motor
                        print("Motor ON!")
                        message = f"Air purification started!\n\nCurrent reading: {sensor_value}" 
                    else:
                        ser.write(b'0')  # Turn off the motor
                        print("Motor OFF!")
        
                    # # Send the gas sensor value to Telegram
                    telegram_url = f'https://api.telegram.org/bot{bot_token}/sendMessage'
                    params = {
                            'chat_id': chat_id,
                            'text': message
                    }
                    response = requests.get(telegram_url, params=params)

                    # Optional: Print the response from Telegram for debugging purposes

                    #print(response.json())

    # Delay before reading the next line
    time.sleep(1)
