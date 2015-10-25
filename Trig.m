psi = 0;   
phi = 0;
tha = 0;

L0 = 0;
L1 = 5.5;
L2 = 4;

% xpos = 3;
% ypos = 2;
% zpos = 1;

xinc = 8;
yinc = 8;
zinc = 3;
n = 1;
table = zeros(xinc, yinc, zinc, 3);
% for n = 1:cols
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
                    table(xpos, ypos, zpos,1) = tha;
                    table(xpos, ypos, zpos,2) = phi;
                    table(xpos, ypos, zpos,3) = psi;
                    n = n+1;
%                 else
%                     table(n,1) = 1234;
%                     table(n,2) = 1234;
%                     table(n,3) = 1234;
%                     n = n+1;
                end
            end
        end

    end
% end

table
n
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