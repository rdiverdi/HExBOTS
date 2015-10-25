L0 = 0;
L1 = 5.5;
L2 = 4;

xinc = 8;
yinc = 8;
zinc = 3;
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
            end
        end
    end

end

table
% n
% PLOTTING STUFF
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