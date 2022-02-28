%%Distortion Algorithm
clear; clc;

[in, Fs] = audioread('bluesRiff_mono.wav');
t = (0:length(in)-1)/Fs;
t = t(:); %?

%%for sinwave input: uncomment next 4 lines & comment out other 't'
% Fs = 44100; Ts = 1/Fs;
% f = 3;
% t = (0: Ts: 1).'; %  .' ??
% in = sin(2*pi*t*f); %basic sin wave

% creating algorithm
% nBits = 2;
% ampValues = 2 ^ (nBits - 1);

holdVal = in(1);
downSample = 8;
bitCounter = downSample;
for n = 1:length(in)
    %out(n,1) = ceil(ampValues * in(n,1)) * (1/ampValues);
    if bitCounter == 0
        holdVal = in(n);
        bitCounter = downSample;
    end        
    out(n) = holdVal;
    bitCounter = bitCounter - 1;
end

% sound(in * 0.1, Fs); pause(); % hit any key in the command window to unpause code exection
sound(out * 0.1, Fs);
% audiowrite('8bit.wav', out, Fs); %save output audiofile

%Visuals
figure;
plot(t, in);

figure;
plot(t, out);
