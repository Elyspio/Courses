clc
clear all
close all
t = 0:0.01:1
P1 = [0, 0];
P2 = [1, 0];
P3 = [1, 1];
P4 = [0, 1];
hold on;
plot(P1, 'o');
plot(P2, 'o');
plot(P3, 'o');
plot(P4, 'o');
window(P1, P2, P3, P4);
M = bezier4(P1, P2, P3, P4, t)
plot(M(:,1), M(:,2))

