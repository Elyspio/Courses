%% t 1-t %% 

clc 
close all
clearvars


min = 0;
max = 5;
nb_points = 500 - 1;
t = min:(max-min)/nb_points:max;

hold on

for i=1: length(t)
   
   tt = t(i);
   x = tt;
   y = 1 - tt;
   plot(x,y, 'r.')
   drawnow
end
hold off

%% sin(3t) sin(4t) %%



clc 
close all
clearvars


min = 0;
max = 6.3;
nb_points = 5000 - 1;
t = min:(max-min)/nb_points:max;

hold on

for i=1: length(t)
   
   tt = t(i);
   x = sin(3*tt);
   y = sin(4*tt);
   plot(x,y, 'r.')
   drawnow
end
hold off

%%


%% cos(t)**3 sin(t)**3 %%



clc 
close all
clearvars


min = -5;
max = 5;
nb_points = 1000 - 1;
t = min:(max-min)/nb_points:max;

hold on

for i=1: length(t)
   
   tt = t(i);
   x = cos(tt) * cos(tt) * cos(tt);
   y = sin(tt) * sin(tt) * sin(tt);
   plot(x,y, 'r.')
   drawnow
end
hold off

%%


%% cos(t) t/2 + sin(t)%%



clc 
close all
clearvars


min = 0;
max = 2*pi;
nb_points = 500 - 1;
t = min:(max-min)/nb_points:max;

hold on

for i=1: length(t)
   
   tt = t(i);
   x = cos(tt);
   y = tt / 2 + sin(tt);
   plot(x,y, 'r.')
   drawnow
end
hold off

%%

%% cos(t) sin(t)² / (2 + sin(t)%%

clc 
close all
clearvars


min = 0;
max = 12;
nb_points = 500 - 1;
t = min:(max-min)/nb_points:max;

hold on

for i=1: length(t)
   
   tt = t(i);
   x = cos(tt);
   y = sin(tt) * sin(tt) / (2 + sin(tt));
   plot(x,y, 'r.')
   drawnow
end
hold off

%%

