%% Bitcrusher Algorithm
clear; clc;

[in, Fs] = audioread('bluesRiff_mono_48000.wav');
t = (0:length(in)-1)/Fs;
t = t(:);     %?
disp(Fs);

%% for sinwave input: uncomment next 4 lines & comment out other 't'
% Fs = 44100; Ts = 1/Fs;
% f = 3;
% t = (0: Ts: 1).';     %  .' ??
% in = sin(2*pi*t*f); %basic sin wave

%% Resolution
% nBits = 5; %6 seems to be a good value mixed with a downsampling of 8 (only downsampling value i have tested w/ this combo)
% ampValues = 2 ^ (nBits - 1);
% for n = 1:length(in)
%     in(n,1) = ceil(ampValues * in(n,1)) * (1/ampValues); %
% end

%% Downsampling
holdVal = in(1);
downSample = 8; %range 1-10 sounds ok, 1 is clean audio
bitCounter = downSample;
for n = 1:length(in)
    if bitCounter <= 0
        holdVal = in(n);
        bitCounter = downSample;
    end
    out(n) = holdVal;
    bitCounter = bitCounter - 1;
end

%% Audio
% sound(in * 0.1, Fs); pause(); % hit any key in the command window to unpause code exection
sound(out * 0.1, Fs);
% audiowrite('8bit.wav', out, Fs); %save output audiofile

%% Visuals
figure;
plot(t, in);

figure;
plot(t, out);
