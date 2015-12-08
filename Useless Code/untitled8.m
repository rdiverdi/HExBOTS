L0 = 1;
L1 = 5;
L2 = 5;
SL = 3;
xp = sind(60)*SL;
yp = cosd(60)*SL;

%% Step Arrays
x = 4;
z = -1;

angles2 = zeros(47,3);
n = 1; % Place in the array
for y = 2.3:-.1:-2.3
    e = sqrt(x^2 + y^2) - L0; 
    f = sqrt(e^2 + z^2);

    u = atand(z/e);
    v = acosd((L1^2 - L2^2 + f^2)/(2*L1*f));
    w = acosd((L1^2 + L2^2 - f^2)/(2*L1*L2));

    tha = atand(y/x);
    phi = (u + v);
    psi = w;
    angles2(n,1) = tha;
    angles2(n,2) = phi;
    angles2(n,3) = psi;
    n = n + 1;
end
angles2;

angles1 = zeros(47,3);
m = 1; % Place in the array
for y = 2.3:-.1:-2.3
    ROTATE = [cosd(60),sind(60),0;-sind(60),cosd(60),0;0,0,1];
    init = [x;y;z];
    mid = ROTATE*init;
    final = mid+[xp;yp;0];
    x1 = final(1); y1 = final(2); z1 = final(3);
    e = sqrt(x1^2 + y1^2) - L0; 
    f = sqrt(e^2 + z1^2);
    u = atand(z/e);
    v = acosd((L1^2 - L2^2 + f^2)/(2*L1*f));
    w = acosd((L1^2 + L2^2 - f^2)/(2*L1*L2));

    tha = atand(y1/x1);
    phi = (u + v);
    psi = w;
    angles1(m,1) = tha;
    angles1(m,2) = phi;
    angles1(m,3) = psi;
    m = m + 1;
end
angles1;

%% Lift and Get Out of the Way Arrays
% z positions for the move
zlift = [-1:1/23:0];
zlower = [-1/23:-1/23:-1];
zmove = [];
num = 1;
for zint = 1:length(zlift)
    zmove(num) = zlift(zint);
    num=num+1;
end
for zint = 1:length(zlower)
    zmove(num) = zlower(zint);
    num=num+1;
end

% y positions
ymove = [-2.3:.1:2.3];

% x positions
xlift = [4:-3/23:1];
xlower = [1+3/23:3/23:4];
xmove = [];
num = 1;
for xint = 1:length(xlift)
    xmove(num) = xlift(xint);
    num=num+1;
end
for xint = 1:length(xlower)
    xmove(num) = xlower(xint);
    num=num+1;
end
xmove
angles1up = zeros(47,3);
a = 1; % Place in the array
for i = 1:47
    ROTATE = [cosd(60),sind(60),0;-sind(60),cosd(60),0;0,0,1];
    x = xmove(i); y = ymove(i); z = zmove(i);
    init = [x;y;z];
    mid = ROTATE*init;
    final = mid+[xp;yp;0];
    x1 = final(1); y1 = final(2); z1 = final(3);
    e = sqrt(x1^2 + y1^2) - L0; 
    f = sqrt(e^2 + z1^2);
    u = atand(z/e);
    v = acosd((L1^2 - L2^2 + f^2)/(2*L1*f));
    w = acosd((L1^2 + L2^2 - f^2)/(2*L1*L2));

    tha = atand(y1/x1);
    phi = (u + v);
    psi = w;
    angles1up(a,1) = tha;
    angles1up(a,2) = phi;
    angles1up(a,3) = psi;
    a = a + 1;
end
angles1up;

angles2up = zeros(47,3);
b = 1; % Place in the array
for i = 1:47
    x = xmove(i); y = ymove(i); z = zmove(i);
    e = sqrt(x^2 + y^2) - L0; 
    f = sqrt(e^2 + z^2);
    u = atand(z/e);
    v = acosd((L1^2 - L2^2 + f^2)/(2*L1*f));
    w = acosd((L1^2 + L2^2 - f^2)/(2*L1*L2));

    tha = atand(y/x);
    phi = (u + v);
    psi = w;
    angles2up(b,1) = tha;
    angles2up(b,2) = phi;
    angles2up(b,3) = psi;
    b = b + 1;
end
angles2up