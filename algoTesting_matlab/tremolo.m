%Tremolo Algorithm
clear; clc;

[in, Fs] = audioread('bluesRiff_mono.wav');
t = (0:length(in)-1)/Fs;
t = t(:);

% Parameters
f = 6;          % Frequency
depth = 100;    % affects Amplitidue 'a' 
a = depth/200;  
offset = 1 - a; % vertical adjustment

% Audio Set and Played
lfo = a*sin(2*pi*f*t) + offset;
out = in .* lfo;
sound(out * 0.1, Fs);

% Visuals
figure;
plot(t, in);

figure;
plot(t, out);

%plot(in);