% Returns a row vector containing four points on a rectangle defined by two
% points.
function arr = rect(x1,y1,x2,y2);
arr = [x1, y1, x2,y1, x2,y2, x1,y2]