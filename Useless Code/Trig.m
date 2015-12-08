function Trig()
L0 = 0;
L1 = 5.5;
L2 = 4;

xinc = 9;
yinc = 9;
zinc = 4;
n = 1;
table = zeros(xinc, yinc, zinc, 3);
for xpos = 1:xinc
    for ypos = 1:yinc
        for zpos = 1:zinc
            tha = atan(ypos/xpos);
            L = sqrt(xpos*xpos + ypos*ypos);
            d = sqrt(xpos*xpos + ypos*ypos +zpos*zpos);
            gamma = atan(zpos/L);
            psi = acos((-d*d + L1*L1 + L2*L2)/(2*L1*L2));
            phi = asin(L2*sin(psi)/d)-gamma;

            square = sqrt((xpos-(L0*cos(tha)))^2 +...
                (ypos-(L0*sin(tha)))^2 + (zpos^2));
            if square <= (L1+L2)
                table(xpos, ypos, zpos,1) = tha*180/pi;
                table(xpos, ypos, zpos,2) = phi*180/pi;
                table(xpos, ypos, zpos,3) = psi*180/pi;
                n = n+1;
            else
                table(xpos, ypos, zpos,1) = 0;
                table(xpos, ypos, zpos,2) = 0;
                table(xpos, ypos, zpos,3) = 0;
                n = n+1;
            end
        end
    end

end
% table(5,8,1,:)
% Look Up Positions
% Standing
pos1=[5,8,3];pos2=[9,1,3];pos3=[5,8,3];
pos4=[5,8,3];pos5=[9,1,3];pos6=[5,8,3];
% Three Up
pos1=[5,8,1];pos2=[9,1,3];pos3=[5,8,1];
pos4=[5,1,3];pos5=[9,1,1];pos6=[5,1,3];

theta = 0:60:360;
x = cosd(theta);
y = sind(theta);
z = ones(1,7);
% z = z.*3;
% Leg 1
l1off = [cosd(60),sind(60),1];
[leg11,leg12,leg13] = legangle(pos1,l1off);
% Leg 2
l2off = [cosd(0),sind(0),1];
[leg21,leg22,leg23] = legangle(pos2,l2off);
% Leg 3
l3off = [cosd(300),sind(300),1];
[leg31,leg32,leg33] = legangle(pos3,l3off);
% Leg 4
l4off = [cosd(240),sind(240),1];
[leg41,leg42,leg43] = legangle(pos4,l4off);
% Leg 5
l5off = [cosd(180),sind(180),1];
[leg51,leg52,leg53] = legangle(pos5,l5off);
% Leg 2
l6off = [cosd(120),sind(120),1];
[leg61,leg62,leg63] = legangle(pos6,l6off);
% Leg Function?
function [one,two,thr] = legangle(pos,off)
    M1 = table(pos(1),pos(2),pos(3),:); % This is a decided position, it's not working
    t1 = M1(:,:,1,1);
    p1 = M1(:,:,1,2);
    s1 = M1(:,:,1,3);
    a = 180-s1-p1;
%     one = [(L0*cosd(t1))+off(1), L0*sind(t1)+off(2),off(3)];
%     two = [(L1*cosd(t1))+(L1*cosd(p1))+one(1), (L1*sind(t1))+one(2),...
%             (L1*sind(p1))+one(3)];
%     thr = [(L2*cosd(t1))+(L2*sind(a))+two(1),(L2*sind(t1))+two(2),...
%         (L2*cosd(a))+two(3)];
    one = [(L0*cosd(t1))+off(1),(L0*sind(t1))+off(2),off(3)];
    two = [(L1*cosd(p1))+one(1),one(2),(L1*sind(p1))+one(3)];
    thr = [(L2*sind(a))+two(1),two(2),(-L2*cosd(a))+two(3)];
end


%% Plotting
figure
hold on
% Plotting the body
plot3(x, y, z, 'b-', 'LineWidth', 3);
fx=-12:.1:12;
[X,Y] = meshgrid(fx);
for i = 1:length(X)
    for j = 1:length(Y)
        Z(i,j) = -2;
    end
end
surf(X,Y,Z)
% Leg 1
plot3([l1off(1),leg11(1)],[l1off(2),leg11(2)],[l1off(3),leg11(3)],'r-');
plot3([leg11(1),leg12(1)],[leg11(2),leg12(2)],[leg11(3),leg12(3)],'g-');
plot3([leg12(1),leg13(1)],[leg12(2),leg13(2)],[leg12(3),leg13(3)],'m-');
% L11 = sqrt((leg11(1)-leg12(1))^2+(leg11(2)-leg12(2))^2+(leg11(3)-leg12(3))^2)
% L12 = sqrt((leg13(1)-leg12(1))^2+(leg13(2)-leg12(2))^2+(leg13(3)-leg12(3))^2)
% Leg 2
plot3([l2off(1),leg21(1)],[l2off(2),leg21(2)],[l2off(3),leg21(3)],'r-');
plot3([leg21(1),leg22(1)],[leg21(2),leg22(2)],[leg21(3),leg22(3)],'g-');
plot3([leg22(1),leg23(1)],[leg22(2),leg23(2)],[leg22(3),leg23(3)],'m-');
% L21 = sqrt((leg21(1)-leg22(1))^2+(leg21(2)-leg22(2))^2+(leg21(3)-leg22(3))^2)
% L22 = sqrt((leg23(1)-leg22(1))^2+(leg23(2)-leg22(2))^2+(leg23(3)-leg22(3))^2)
% Leg 3
% plot3([l3off(1),leg31(1)],[l3off(2),leg31(2)],[l3off(3),leg31(3)],'r-');
% plot3([leg31(1),leg32(1)],[leg31(2),-leg32(2)],[leg31(3),leg32(3)],'g-');
% plot3([leg32(1),leg33(1)],-[leg32(2),leg33(2)],[leg32(3),leg33(3)],'m-');
% L31 = sqrt((leg31(1)-leg32(1))^2+(leg31(2)-leg32(2))^2+(leg31(3)-leg32(3))^2)
% L32 = sqrt((leg33(1)-leg32(1))^2+(leg33(2)-leg32(2))^2+(leg33(3)-leg32(3))^2)
% Leg 4
% plot3([l4off(1),leg41(1)],[l4off(2),leg41(2)],[l4off(3),leg41(3)],'r-');
% plot3([leg41(1),-leg42(1)],[leg41(2),-leg42(2)],[leg41(3),leg42(3)],'g-');
% plot3(-[leg42(1),leg43(1)],-[leg42(2),leg43(2)],[leg42(3),leg43(3)],'m-');
% L41 = sqrt((leg41(1)-leg42(1))^2+(leg41(2)-leg42(2))^2+(leg41(3)-leg42(3))^2)
% L42 = sqrt((leg43(1)-leg42(1))^2+(leg43(2)-leg42(2))^2+(leg43(3)-leg42(3))^2)
% Leg 5
% plot3([l5off(1),leg51(1)],[l5off(2),leg51(2)],[l5off(3),leg51(3)],'r-');
% plot3([leg51(1),-leg52(1)],[leg51(2),leg52(2)],[leg51(3),leg52(3)],'g-');
% plot3(-[leg52(1),leg53(1)],[leg52(2),leg53(2)],[leg52(3),leg53(3)],'m-');
% L51 = sqrt((leg51(1)-leg52(1))^2+(leg51(2)-leg52(2))^2+(leg51(3)-leg52(3))^2)
% L52 = sqrt((leg53(1)-leg52(1))^2+(leg53(2)-leg52(2))^2+(leg53(3)-leg52(3))^2)
% Leg 6
% plot3([l6off(1),leg61(1)],[l6off(2),leg61(2)],[l6off(3),leg61(3)],'r-');
% plot3([leg61(1),-leg62(1)],[leg61(2),leg62(2)],[leg61(3),leg62(3)],'g-');
% plot3(-[leg62(1),leg63(1)],[leg62(2),leg63(2)],[leg62(3),leg63(3)],'m-');
% L61 = sqrt((leg61(1)-leg62(1))^2+(leg61(2)-leg62(2))^2+(leg61(3)-leg62(3))^2)
% L62 = sqrt((leg63(1)-leg62(1))^2+(leg63(2)-leg62(2))^2+(leg63(3)-leg62(3))^2)

% Axis Stuff
% axis square;
axis([-12 12 -12 12 -3 6]);

%% PLOTTING STUFF
% [tha;phi;psi]

% x1 = L1*cos(phi);
% y1 = L1*sin(tha);
% z1 = L1*sin(phi);
% x2 = L2*cos(3.14-phi-psi)+x1;
% y2 = L*sin(tha);
% z2 = -L2*sin(3.14-phi-psi)+z1;
% 
% figure
% hold on
% plot(0,0,'pg')
% plot(x1,z1,'pb-')
% plot3([0, x1,x2],[0,y1,y2],[0, z1,z2],'rp-')
% 
% sqrt((x2)^2+(z2)^2)

%% Notes and Thoughts
% Currently, the table will tell the leg how to move from 0,0,0 to a
% certain forward point. For going in reverse, we need to ask it to reset
% its values to "zero", move twice the distance along the ground while
% having the servos spin backwards. Then those will rezero and move up and
% forward. All the while, the opposite set of legs is moving the same at a
% time offset. 

% Also, Matlab indexes everything from 1, and the servo and positions need
% to all be from 0.

% One last thing, I think we should subtract 90 degrees from all the
% values, unless servoes like them more like this. I don't know...
end