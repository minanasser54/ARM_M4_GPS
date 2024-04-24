import pandas as pd
import matplotlib.pyplot as plt
import serial

## Done Till Knowing How Data is Transmitted

def draw(z):
    y=[]
    x=[]
    
    df = pd.read_csv('example.csv')
    #print(df.get("lon"))
    plt.plot(df.get("lon"),df.get("lat"))
    plt.show()

ser = serial.Serial(port='COM4',parity="N",baudrate=9600,stopbits=1,timeout=120)  # open first serial port
print(ser.portstr+" is runing !!") 
ser.flushInput()
ser.flushOutput()

while True:
    data_raw = ser.readline(1)
    print(data_raw)
    

# print(msg)
# ser.close()


# def draw():
#     df = pd.read_csv('example.csv')
#     #print(df.get("lon"))
#     plt.plot(df.get("lon"),df.get("lat"))
#     plt.show()
