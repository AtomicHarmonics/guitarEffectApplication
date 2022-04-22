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
out = in;
thresh = .5; % level of clipping: 0.08 - 0.7
for i = 1:(length(out))    
    if in(i) > thresh
        out(i) = thresh;
    elseif in(i) < -thresh
        out(i) = -thresh;
    end
    
%     out(i) = out(i) * (0.7/thresh); %to compensate for the quiteness,
% %     however can lead dividing by 0, or making it quieter if thresh < 0.7.
% %     The last part might not be a concern as we can make 0.7 the max
% %     thresh
end

sound(in * 0.1, Fs); pause(); % hit any key in the command window to unpause code exection
sound(out * 0.1, Fs);
%audiowrite('hardClipping.wav', out, Fs); %save output audiofile

%Visuals
figure;
plot(t, in);

figure;
plot(t, out);
