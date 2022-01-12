%%Overdrive Algorithm
clear; clc;

[in, Fs] = audioread('bluesRiff_mono.wav');
t = (0:length(in)-1)/Fs;
t = t(:); %?

% %for sinwave input: uncomment next 4 lines & comment out other 't'
% Fs = 44100; Ts = 1/Fs;
% f = 3;
% t = (0: Ts: 1).'; %  .' ??
% in = sin(2*pi*t*f); %basic sin wave

%%for white noise input: uncomment next 3 lines
% Fs = 44100;
% numOfSamples = Fs * 3; %3sec worth of samples
% in = 0.2 * randn(numOfSamples, 1); %random generated white noise

% creating algorithm
out = in;
a = 1; %level of clipping: 0-1
for i = 1:(length(out))
    %%%%%% Cubic soft clipping %%%%%%
    %out(i) = out(i) - a * (2/3)*out(i); %(1/3), ratio can be increased for more clipping
    
    %%%%%% Arctan soft clipping %%%%%%
    out(i) = (2/pi) * atan(out(i) * a); % change 'a' to '(2+a)'
end

sound(in * 0.1, Fs); pause(); 
sound(out * 0.1, Fs);

% audiowrite('Overdrive_softClipping.wav', out, Fs);

%Visuals
figure;
plot(t, in);

figure;
plot(t, out);
