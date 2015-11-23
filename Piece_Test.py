import math
from numpy import *

L0 = .4;
L1 = 4;
L2 = 5;
SL = 4;
xp = math.sin(math.radians(60))*SL;
yp = math.cos(math.radians(60))*SL;

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
		
x = 6;
z = -3;
Yrange = frange(1.8,-1.8,-3.6/23)


# m = 1; # Place in the array
# Rotate = matrix([[math.cos(math.radians(60)),math.sin(math.radians(60)),0],
# [-math.sin(math.radians(60)),math.cos(math.radians(60)),0],[0,0,1]])
# for i in Yrange: i.e., this needs to be called within a for loop
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
	v = math.degrees(math.acos((L1**2 - L2**2 + f**2)/(2*L1*f)));
	w = math.degrees(math.acos((L1**2 + L2**2 - f**2)/(2*L1*L2)));

	tha = math.degrees(math.atan(y/x));
	phi = (u + v);
	if phi >= 90:
		phi = 90;
	psi = w;
	angles.append(tha);
	angles.append(phi);
	angles.append(psi);
	return angles

Rotate1 = matrix([[math.cos(math.radians(60)),math.sin(math.radians(60)),0],
[-math.sin(math.radians(60)),math.cos(math.radians(60)),0],[0,0,1]])	
Rotate2 = matrix([[0,0,0],[0,0,0],[0,0,0]])
for i in range(0,len(Yrange)):
	positions(x,Yrange[i],z,xp,yp,Rotate1)
	

zlift = halfrange(-3.0,-1.0-(2.0/12.0),2.0/12.0)
zlower = halfrange(-1.0+(2.0/12.0),2.0/12.0,-3.0)
zmove = [];
for zint in range(0,len(zlift)):
    zmove.append(zlift[zint]);
for zint in range(0,len(zlower)):
    zmove.append(zlower[zint]);
    
ymove = frange(-1.8,1.8,(3.6/23))

xlift = halfrange(6.0,4.0+(2.0/12.0),-2.0/12.0)
xlower = halfrange(4.0+(2.0/12.0),2.0/12.0,6.0)
xmove = [];
for xint in range (1,len(xlift)):
    xmove.append(xlift([xint]);
for xint in range(1,len(xlower)):
    xmove.append(xlower[xint]);
	
	
	