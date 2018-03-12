# 2017-07-12 by scharette
# Basic 2D IK example of AL5 + Python

# Obtain required libraries
import serial

from lib_al5_2D_IK import al5_2D_IK, al5_moveMotors

# Constants - Speed in µs/s, 4000 is roughly equal to 360°/s or 60 RPM
#           - A lower speed will most likely be more useful in real use, such as 100 µs/s (~9°/s)
CST_SPEED_MAX = 4000
CST_SPEED_DEFAULT = 100

# Create and open a serial port
sp = serial.Serial('/dev/ttyUSB0', 9600)

# Set default values
AL5_DefaultPos = 1500;
cont = True
defaultTargetX = 4
defaultTargetY = 4
defaultTargetZ = 90
defaultTargetG = 90
defaultTargetWA = 0
defaultTargetWR = 90
defaultTargetShoulder = 90
defaultTargetElbow = 90
targetX = defaultTargetX
targetY = defaultTargetY
targetZ = defaultTargetZ
targetG = defaultTargetG
targetWA = defaultTargetWA
targetWR = defaultTargetWR
index_X = 0
index_Y = 1
index_Z = 2
index_G = 3
index_WA = 4
index_WR = 5
targetXYZGWAWR = (targetX, targetY, targetZ, targetG, targetWA, targetWR)
targetQ = "y"
motors_SEWBZWrG = (90, 90, 90, 90, 90, 90)
speed_SEWBZWrG = (CST_SPEED_DEFAULT, CST_SPEED_DEFAULT, CST_SPEED_DEFAULT, CST_SPEED_DEFAULT, CST_SPEED_DEFAULT, CST_SPEED_DEFAULT)

# Set the arm to default centered position (careful of sudden movement)
print("Default position is " + str(AL5_DefaultPos) + ".")
for i in range(0,6):
	print(("#" + str(i) + " P" + str(AL5_DefaultPos) + "\r").encode())
	sp.write(("#" + str(i) + " P" + str(AL5_DefaultPos) + "\r").encode())

while cont:
	
	# Get X/Y position of end effector and perform IK on it
	print("")
	print("--- --- --- --- --- --- --- --- --- ---")
	print("< Set X/Y position of end effector >")
	print("")
	
	# Get X position
	targetInput = input("X position (last X = " + str(targetXYZGWAWR[index_X]) + ") ? ")
	if(targetInput == ""):
		targetX = defaultTargetX;
	else:
		targetX = int(targetInput);
	targetXYZGWAWR = (targetX, targetXYZGWAWR[1], targetXYZGWAWR[2], targetXYZGWAWR[3], targetXYZGWAWR[4], targetXYZGWAWR[5])
	
	# Get Y position
	targetInput = input("Y position (last Y = " + str(targetXYZGWAWR[index_Y]) + ") ? ")
	if(targetInput == ""):
		targetY = defaultTargetY;
	else:
		targetY = int(targetInput);
	targetXYZGWAWR = (targetXYZGWAWR[0], targetY, targetXYZGWAWR[2], targetXYZGWAWR[3], targetXYZGWAWR[4], targetXYZGWAWR[5])
	
	# Perform IK
	errorValue = al5_2D_IK(targetXYZGWAWR)
	if isinstance(errorValue, tuple):
		motors_SEWBZWrG = errorValue
	else:
		print(errorValue)
		motors_SEWBZWrG = (defaultTargetShoulder, defaultTargetElbow, defualtTargetWA, defaultTargetZ, defaultTargetG, defaultTargetWR)
	
	# Move motors
	errorValue = al5_moveMotors(motors_SEWBZWrG, sp)
	
	# Quit? (quit on "y", continue on any other input)
	targetQ = str(input("Quit ? (Y/N) "))
	if targetQ == "y":
		cont = False

# Set all motors to idle/unpowered (pulse = 0)
print("< Idling motors... >");
for i in range(0,6):
	print(("#" + str(i) + " P" + str(0) + "\r").encode())
	sp.write(("#" + str(i) + " P" + str(0) + "\r").encode())
print("< Done >")
