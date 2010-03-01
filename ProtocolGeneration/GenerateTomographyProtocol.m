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
filename='2DTomography.yml';
gridHeight=100;
gridWidth=7; %must be odd
description= sprintf('This protocol consists of a crude rasterscan. It divides the worms up into a %d by %d grid.', gridHeight, gridWidth);




%% Fundamental Sprite
xprim=gridWidth; %% do the anterior/posterior band first
yprim=10;


%% Guts
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Fundamental unit
disp(description)
primitive=[(-(xprim-1)/2 -1) ,0, ((xprim-1)/2 + 1),0, ((xprim-1)/2 +1 ), yprim, (-(xprim-1)/2-1),yprim];

mvHEADTAIL=[0,yprim, 0,yprim, 0,yprim, 0,yprim];

current=primitive %-((gridWidth-1)/2)*mvLATERAL;
m=1;
%%Do anterior posterior
for j=1:round(gridHeight/yprim)
    current
    protocol{m}=current;
        current=min(current+mvHEADTAIL,gridHeight-1); %increment head position
    m=m+1;
end



%% Fundamental Sprite
%% Now do the left right part.
yprim=99;
xprim=2;


mvLATERAL=[1,0, 1,0, 1,0, 1,0];

primitive=[-(gridWidth-1)/2-1,0, -(gridWidth-1)/2-1+xprim,0, -(gridWidth-1)/2-1+xprim, yprim, -(gridWidth-1)/2-1,yprim];
current=primitive;
%%Do left/right 
for j=1:round(gridHeight/yprim)
    current
    protocol{m}=current;
    
    for k=1:(gridWidth-1)     
        m=m+1;
        current=current+mvLATERAL
        protocol{m}=current;
    end
    current=current-(gridWidth-2)*mvLATERAL; %reset lateral position
    
    current=current+mvHEADTAIL; %increment head position
    m=m+1;
end




figure;
for n=1:length(protocol)
   
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end

writeProto(filename,description,gridWidth,gridHeight,protocol)
