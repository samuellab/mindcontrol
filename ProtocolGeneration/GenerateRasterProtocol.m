%% Notes
% Tip of head is (0, 0). 
% Tail is (99,0)
%
% 
% Pictorially:
%      (-10,0)  (0,0)  (10,0)
%             Head
%                ^ 
%              /  \
%             /    \
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             \    /
%              \  /
%               \/
%             Tail  
%        (-10,99)  (0,99)  (10,99)
%
%
%    y
%    ^
%    |     (axis)
%    |
%    ------------> x
%
% Note also, you can walk off the worm in y (but not in x).


clear all; close all;


%% Header informatoin
filename='crudeRasterScan.yml';
gridHeight=100;
gridWidth=5; %must be odd
description= sprintf('This protocol consists of a crude rasterscan. It divides the worms up into a %d by %d grid.', gridHeight, gridWidth);




%% Fundamental Sprite
xprim=2;
yprim=14;







%% Guts
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Fundamental unit
disp(description)
primitive=[0,0, xprim,0, xprim, yprim, 0,yprim]-[1,0,1,0,1,0,1,0];

mvLATERAL=[xprim,0, xprim,0 ,xprim,0, xprim,0];
mvHEADTAIL=[0,yprim, 0,yprim, 0,yprim, 0,yprim];

current=primitive-((gridWidth-1)/2-1)*mvLATERAL;
m=1;

for j=1:round(gridHeight/yprim)
    current
    protocol{m}=current;
    
    for k=1:(gridWidth-3)     
        m=m+1;
        current=current+mvLATERAL
        protocol{m}=current;
    end
    current=current-(gridWidth-3)*mvLATERAL; %reset lateral position
    current=current+mvHEADTAIL; %increment head position
    m=m+1;
end

figure;
for n=1:length(protocol)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end

writeProto(filename,description,gridWidth,gridHeight,protocol)
