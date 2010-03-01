function []=plotProtocol(currentStep,height,width)
clf;
axes;
 ylim([-width,width])
 xlim([0,height])

wormcolor=[240 240 240]./255;
illumColor=[51 255 102]./255;

worm=[-floor(width/2) 0   floor(width/2) 0  floor(width/2) height -floor(width/2) height];
hold on;
fill(worm(2:2:end),worm(1:2:end),wormcolor);

fill(currentStep(2:2:end),currentStep(1:2:end),illumColor)
text(0,0, 'Head')
text(height, 0, 'Tail')

end

