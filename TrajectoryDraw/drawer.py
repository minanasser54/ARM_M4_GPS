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
        lon_values.append(round(ToRad(ToDeg((float(data_raw[i])/10000))),6))
        lat_values.append(round(ToRad(ToDeg((float(data_raw[i + 1])/10000))),6))

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
# 30052704,
# 31153288,
# 30052898,
# 31153290,
# 30052898,
# 31153298,

# def GO_WAIT():
#     if ser.in_waiting > 0:
#         line = ser.readline().decode().strip()  # Read and decode the data
#         print(line)
#         if not line:
#             draw(data_raw) # Exit loop if empty line is received
#         data_raw.append(line) 

# while True:
#     user_input = input("Enter a character to send (or 'q' to quit): ")
#     if user_input.lower() == 'q':
#         break  # Exit the loop if 'q' is entered
#     if ser.writable():
#         ser.write(user_input.encode())  # Send the user input if writable
#         GO_WAIT()
    
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

    

# print(msg)
# ser.close()


# def draw():
#     df = pd.read_csv('example.csv')
#     #print(df.get("lon"))
#     plt.plot(df.get("lon"),df.get("lat"))
#     plt.show()
