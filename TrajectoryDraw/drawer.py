import pandas as pd
import matplotlib.pyplot as plt
import serial
PI =  3.141592654
def ToDeg(Num):
	degree = Num/100
	minutes =Num-float(degree*100)
	return(degree+(minutes/60))
def ToRad(DegNum):
    return (DegNum*(PI/180))

def draw(data_raw):
    if len(data_raw) % 2 != 0:
        print("Invalid number of values. Each longitude should have a corresponding latitude.")
        return

    lon_values = []
    lat_values = []
    for i in range(0, len(data_raw), 2):
        lon_values.append(ToRad(round(ToDeg((float(data_raw[i])/10000)),5)))
        lat_values.append(ToRad(round(ToDeg((float(data_raw[i + 1])/10000)),5)))

    plt.plot(lon_values, lat_values, marker='o')
    plt.xlabel('Longitude')
    plt.ylabel('Latitude')
    plt.title('GPS Data')
    plt.show()

ser = serial.Serial(port='COM3',parity="N",baudrate=9600,stopbits=1,timeout=120)  # open first serial port
print(ser.portstr+" is runing !!") 
ser.flushInput()
ser.flushOutput()
data_raw=[]

while True:
    if ser.writable():
        #user_input = input("Enter a U to send : ")
        #ser.write(user_input.encode())  # Send 'U' if writable
        ser.write(b'U')
    while ser.in_waiting > 0:
        line = ser.readline().decode().strip()  # Read and decode the data
        print(line)
        if line == "saved" :
            draw(data_raw)
            print("drawed")
        elif not line:
            print("=========BREAKED")
            break
        else:
            data_raw.append(line)  # Append received line to data_raw list
        


ser.close()

    
