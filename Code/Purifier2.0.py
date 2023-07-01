import time
import serial
import requests
import csv
import re

serial_port = 'COM9'
baud_rate = 9600

bot_token = '6125854644:AAHhO-RsXC91W8G7Uxh9NCxdj12MnEDD_qU'
chat_id = '-1001989081010'


def extract_numeric_value(line):
    match = re.search(r'\d+(\.\d+)?', line)
    if match:
        numeric_value = float(match.group())
        return numeric_value
    else:
        return line
    
def Run():
    msg = []    # For CSV
    msg2 = []   # For Telegram
    while True:
        line = ser.readline().decode('utf-8').strip()
        msg.append(extract_numeric_value(line)) 
        msg2.append(line)
        if len(msg) > 4:
            message = '\n'.join(msg2)
            
            print('------------------\n')
            with open('output3.csv', 'a', newline='') as csvfile:
                writer = csv.writer(csvfile)
                writer.writerow([msg,time.time()])

            msg,msg2 = [],[]

            telegram_url = f'https://api.telegram.org/bot{bot_token}/sendMessage'
            params = {
                        'chat_id': chat_id,
                        'text': message
                    }
            response = requests.get(telegram_url, params=params)
            
            break
        time.sleep(1)
        
Choice = int(input("How Many Time You want to run---> "))
while Choice!=0:
    ser = serial.Serial(serial_port, baud_rate, timeout=1)
    Run()
    Choice-=1
    ser.close()    