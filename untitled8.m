L0 = 1;
L1 = 5;
L2 = 5;
SL = 3;
xp = sind(60)*SL;
yp = cosd(60)*SL;

% x = sym('x');
% y = sym('y');
% z = sym('z');
x = 4;
y = 0;
z = -1;
%     xp = sind(60)*SL;
%     yp = cosd(60)*SL;


e = sqrt(x^2 + y^2) - L0; 
f = sqrt(e^2 + z^2);


u = atand(z/e);
v = acosd((L1^2 - L2^2 + f^2)/(2*L1*f));
w = acosd((L1^2 + L2^2 - f^2)/(2*L1*L2));

tha = atand(y/x);
phi = (u + v);
psi = w;
a = 180-phi-psi;
angles = [tha, phi, psi]
% one = [(L0*cosd(tha))+off(1),(L0*sind(tha))+off(2),off(3)];
% two = [(L1*cosd(phi)*cosd(tha))+one(1),one(2)*sind(tha),...
%         (L1*sind(phi))+one(3)];
% thr = [(L2*sind(a)*cosd(tha))+two(1),two(2)*sind(tha),...
%         (-L2*cosd(a))+two(3)];