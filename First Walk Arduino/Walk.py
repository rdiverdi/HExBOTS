import math
from numpy import *

L0 = .4;
L1 = 4;
L2 = 5;
SL = 4;
xp = math.sin(math.radians(60))*SL;
yp = math.cos(math.radians(60))*SL;

## Functions
def frange(start, stop, step):
	i = start
	ans = []
	for j in range(0,24):
		ans.append(i)
		i += step
	return ans
	
def halfrange(start, stop, step):
	i = start
	ans = []
	for j in range(0,12):
		ans.append(i)
		i += step
	return ans

def positions(x,y,z,xs,ys,rotation): # call x,y,z in terms of i as needed
	angles = []
	init = matrix([[x],[y],[z]])
	mid = rotation*init;
	mid = mid.T
	final = mid+[xs,ys,0];
	x1 = final[0,0]; y1 = final[0,1]; z1 = final[0,2];
	e = sqrt(x1**2 + y1**2) - L0; 
	f = sqrt(e**2 + z1**2);
	u = math.degrees(math.atan(z/e));
	v = math.degrees(math.acos(((L1**2) - (L2**2) + (f**2))/(2*L1*f)));
	w = math.degrees(math.acos(((L1**2) + (L2**2) - (f**2))/(2*L1*L2)));
	

	tha = math.degrees(math.atan(y/x));
	phi = (u + v);
	if phi >= 90:
		phi = 90;
	psi = w;
	angles.append(tha);
	angles.append(phi);
	angles.append(psi);
	return angles

## Numerical and Placement Set Up	
x = 6;
z = -3;
Yrange = frange(1.8,-1.8,-(3.6/23))
Rotate1 = matrix([[math.cos(math.radians(60)),math.sin(math.radians(60)),0],
[-math.sin(math.radians(60)),math.cos(math.radians(60)),0],[0,0,1]])
Rotate2 = matrix([[1,0,0],[0,1,0],[0,0,1]])
Rotate3 = matrix([[math.cos(math.radians(60)),-math.sin(math.radians(60)),0],
[math.sin(math.radians(60)),math.cos(math.radians(60)),0],[0,0,1]])	

zlift = halfrange(-3.0,-1.0-(2.0/12.0),2.0/12.0)
zlower = halfrange(-1.0+(2.0/12.0),-3.0,2.0/12.0)
zmove = [];
for zint in range(0,len(zlift)):
    zmove.append(zlift[zint]);
for zint in range(0,len(zlower)):
    zmove.append(zlower[zint]);
    
ymove = frange(-1.8,1.8,(3.6/23))

xlift = halfrange(6.0,4.0+(2.0/12.0),-2.0/12.0)
xlower = halfrange(4.0+(2.0/12.0),6.0,2.0/12.0)
xmove = [];
for xint in range(0,len(xlift)):
    xmove.append(xlift[xint])
for xint in range(0,len(xlower)):
    xmove.append(xlower[xint]);
    
#############################################################################
# THIS GIVES YOU THE ACTUAL LOCATIONS. EVERYTHING ABOVE IS SET UP.

for i in range(0,len(Yrange)):
	angles1 = positions(x,Yrange[i],z,xp,yp,Rotate1)
	angles2 = positions(x,Yrange[i],z,0,0,Rotate2)
	angles3 = positions(x,Yrange[i],z,xp,-yp,Rotate3)
	
	angles1up = positions(xmove[i],ymove[i],zmove[i],xp,yp,Rotate1)
	angles2up = positions(xmove[i],ymove[i],zmove[i],0,0,Rotate2)
	angles3up = positions(xmove[i],ymove[i],zmove[i],xp,-yp,Rotate3)
	print angles1up
	print angles2up
	print angles3up
	
	# At this point (within the for loop), we would need to send these arrays to
	# the Arduino. Each array has three pieces, a theta, a phi, and an psi. 
	# Everything is an degrees/Servo angles. The Arduino code is going to need to 
	# be modified slightly because I do a bit of calculation at the end of the MATLAB
	# code that puts all of this into PWM. All it is is round((angle*2.2)+122). 
	# I'm gonna go modify a new Arduino script for that now...

	# Interesting


