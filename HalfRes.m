L0 = .4;
L1 = 4;
L2 = 5;
SL = 4;
xp = sind(60)*SL;
yp = cosd(60)*SL;

%% Step Arrays
x = 5;
xtop = 3;
z = -4;
YRANGE = 1.8:-(3.6/23):-1.8;

angles2 = zeros(24,3);
n = 1; % Place in the array
for y = YRANGE
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


angles1 = zeros(24,3);
m = 1; % Place in the array
for y = YRANGE
    ROTATE = [cosd(60),sind(60),0;-sind(60),cosd(60),0;0,0,1];
    init = [xtop;y;z];
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

angles3 = zeros(24,3);
o = 1; % Place in the array
for y = YRANGE
    ROTATE = [cosd(60),-sind(60),0;sind(60),cosd(60),0;0,0,1];
    init = [xtop;y;z];
    mid = ROTATE*init;
    final = mid+[xp;-yp;0];
    x1 = final(1); y1 = final(2); z1 = final(3);
    e = sqrt(x1^2 + y1^2) - L0; 
    f = sqrt(e^2 + z1^2);
    u = atand(z/e);
    v = acosd((L1^2 - L2^2 + f^2)/(2*L1*f));
    w = acosd((L1^2 + L2^2 - f^2)/(2*L1*L2));

    tha = atand(y1/x1);
    phi = (u + v);
    psi = w;
    angles3(o,1) = tha;
    angles3(o,2) = phi;
    angles3(o,3) = psi;
    o = o + 1;
end

%% Lift and Get Out of the Way Arrays
% z positions for the move
zlift = [-4:3/12:-1-3/12];
zlower = [-1-3/12:-3/12:-4];
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
% zmove
% y positions
ymove = -YRANGE;

% x positions
xlift = [6:-2/12:4+2/12];
xlower = [4+2/12:2/12:6];
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
% xmove = 2.*ones(1,24)

xlift2 = [4:-2/12:2+2/12];
xlower2 = [2+2/12:2/12:4];
xmove2 = [];
num = 1;
for xint = 1:length(xlift2)
    xmove2(num) = xlift2(xint);
    num=num+1;
end
for xint = 1:length(xlower2)
    xmove2(num) = xlower2(xint);
    num=num+1;
end
% xmove2 = 2.*ones(1,24)

angles1up = zeros(24,3);
a = 1; % Place in the array
for i = 1:24
    ROTATE = [cosd(60),sind(60),0;-sind(60),cosd(60),0;0,0,1];
    x = xmove2(i); 
    y = ymove(i); 
    z = zmove(i);
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
    if phi >= 90
        phi = 90;end
    angles1up(a,2) = phi;
    angles1up(a,3) = psi;
    a = a + 1;
end

angles2up = zeros(24,3);
b = 1; % Place in the array
for i = 1:24
    x = xmove(i);
    y = ymove(i); 
    z = zmove(i);
    e = sqrt(x^2 + y^2) - L0; 
    f = sqrt(e^2 + z^2);
    u = atand(z/e);
    v = acosd((L1^2 - L2^2 + f^2)/(2*L1*f));
    w = acosd((L1^2 + L2^2 - f^2)/(2*L1*L2));

    tha = atand(y/x);
    phi = (u + v);
    psi = w;
    angles2up(b,1) = tha;
    if phi >= 90
        phi = 90;end
    angles2up(b,2) = phi;
    angles2up(b,3) = psi;
    b = b + 1;
end

angles3up = zeros(24,3);
c = 1; % Place in the array
for i = 1:24
    ROTATE = [cosd(60),-sind(60),0;sind(60),cosd(60),0;0,0,1];
    x = xmove2(i); 
    y = ymove(i); 
    z = zmove(i);
    init = [x;y;z];
    mid = ROTATE*init;
    final = mid+[xp;-yp;0];
    x1 = final(1); y1 = final(2); z1 = final(3);
    e = sqrt(x1^2 + y1^2) - L0; 
    f = sqrt(e^2 + z1^2);
    u = atand(z/e);
    v = acosd((L1^2 - L2^2 + f^2)/(2*L1*f));
    w = acosd((L1^2 + L2^2 - f^2)/(2*L1*L2));

    tha = atand(y1/x1);
    phi = (u + v);
    psi = w;
    angles3up(c,1) = tha;
    if phi >= 90
        phi = 90;end
    angles3up(c,2) = phi;
    angles3up(c,3) = psi;
    c = c + 1;
end
% angles3
% angles2
% % These are for leg specific look up tables. We're using similarity and
% % mirroring. 
csvwrite('Walk2.txt',round((angles2.*2.2)+122))
csvwrite('Lift1.txt',round((angles1up.*2.2)+122))
csvwrite('Lift3.txt',round((angles3up.*2.2)+122))
csvwrite('Walk1.txt',round((angles1.*2.2)+122))
csvwrite('Walk3.txt',round((angles3.*2.2)+122))
csvwrite('Lift2.txt',round((angles2up.*2.2)+122))
csvwrite('Lift6.txt',round(angles1up(:,2:3)))
csvwrite('Walk6.txt',round(angles1(:,2:3)))
% 
% csvwrite('Top.txt',round((angles1(:,1)*2.2)+122));
% csvwrite('Back.txt',round((angles3(:,1)*2.2)+122));
% csvwrite('Mid.txt',round((angles2(:,1)*2.2)+122));
% csvwrite('SixPhi.txt',round(angles1(:,2)));
% csvwrite('SixPsi.txt',round(angles1(:,3)));
% csvwrite('Phi.txt',round((angles1(:,2)*2.2)+122));
% csvwrite('Psi.txt',round((angles1(:,3)*2.2)+122));
% csvwrite('SAPhi.txt',round((angles2(:,2)*2.2)+122));
% csvwrite('SAPsi.txt',round((angles2(:,3)*2.2)+122));








