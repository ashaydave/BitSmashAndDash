addpath(genpath('Test Signals'));

%% Test dirac signal
[dirac, fs] = audioread('diracTest.wav');

% Set buffer parameters
buff_length = 480;

% Initialize plugin
bitSmashAndDash = bitSmash();  

% Setting bit crusher parameters
bitSmashAndDash.bitDepth = 8; 
bitSmashAndDash.normalizedFreq = 1; 
bitSmashAndDash.highShelfCutoff = 15000;
bitSmashAndDash.highShelfGain = 0;

% Set variables for buffering and loop through the test signal
num_buffs = ceil(length(dirac) / buff_length);
dirac_out = zeros(size(dirac));

for b = 1:num_buffs
    start_ind = (b - 1) * buff_length + 1;
    end_ind = min(start_ind + buff_length - 1, length(dirac));
    buff = dirac(start_ind:end_ind, :); 
    processed_buff = process(bitSmashAndDash, buff);
    dirac_out(start_ind:end_ind, :) = processed_buff;
end

figure(1);
plot(dirac_out);
title('Bitcrushed Dirac Time-Domain');
xlabel('samples');
ylabel('amplitude');


win_length = buff_length;
overlap_length = floor(win_length/2);
nfft = max(256,2^nextpow2(win_length));
figure(2);
spectrogram(dirac_out, hamming(win_length), overlap_length, nfft);
title('Bitcrushed Dirac Frequency-Domain');

%% Test sine sweep signal
[ess, fs] = audioread('sineSweep.wav');

num_buffs = ceil(length(ess) / buff_length);
ess_out = zeros(size(ess));

figure(3);
subplot(2,1,1)
plot(ess);
title('ESS Time-Domain');
xlabel('samples');
ylabel('amplitude');

for b = 1:num_buffs
    start_ind = (b - 1) * buff_length + 1;
    end_ind = min(start_ind + buff_length - 1, length(ess));
    buff = ess(start_ind:end_ind, :);
    processed_buff = process(bitSmashAndDash, buff);
    ess_out(start_ind:end_ind, :) = processed_buff; 
end

subplot(2,1,2)
plot(ess_out);
title('Bitcrushed ESS Time-Domain');
xlabel('samples');
ylabel('amplitude');


win_length = buff_length;
overlap_length = floor(win_length/2);
nfft = max(256,2^nextpow2(win_length));
figure(4);
spectrogram(ess_out, hamming(win_length), overlap_length, nfft);
title('Bitcrushed ESS Frequency-Domain');
%% Test pink noise signal
[pink_noise, fs] = audioread('pinkNoise.wav');

num_buffs = ceil(length(pink_noise) / buff_length);
pink_noise_out = zeros(size(pink_noise));

figure(5);
subplot(2,1,1)
plot(pink_noise);
title('Pink Noise Time Domain');
xlabel('samples');
ylabel('amplitude');

for b = 1:num_buffs
    start_ind = (b - 1) * buff_length + 1;
    end_ind = min(start_ind + buff_length - 1, length(pink_noise));
    buff = pink_noise(start_ind:end_ind, :);
    processed_buff = process(bitSmashAndDash, buff);
    pink_noise_out(start_ind:end_ind, :) = processed_buff;
end

subplot(2,1,2)
plot(pink_noise_out);
title('Bitcrushed Pink Noise Time-Domain');
xlabel('samples');
ylabel('amplitude');


win_length = buff_length;
overlap_length = floor(win_length/2);
nfft = max(256,2^nextpow2(win_length));
figure(6);
spectrogram(pink_noise_out, hamming(win_length), overlap_length, nfft);
title('Bitcrushed Pink Noise Frequency-Domain');

%% Audio File

[guitar, fs] = audioread('Guitar.wav');
guitar = guitar(:,1) + guitar(:,2);

figure(7);
subplot(2,1,1)
plot(guitar);
title('Guitar WAV');
xlabel('samples');
ylabel('amplitude');
num_buffs = ceil(length(guitar) / buff_length);
guitar_out = zeros(size(guitar));

for b = 1:num_buffs
    start_ind = (b - 1) * buff_length + 1;
    end_ind = min(start_ind + buff_length - 1, length(guitar));
    buff = guitar(start_ind:end_ind, :);
    processed_buff = process(bitSmashAndDash, buff);
    guitar_out(start_ind:end_ind, :) = processed_buff;
end


subplot(2,1,2)
plot(guitar_out);
title('Bitcrushed Guitar WAV Time-Domain');
xlabel('samples');
ylabel('amplitude');

win_length = buff_length;
overlap_length = floor(win_length/2);
nfft = max(256,2^nextpow2(win_length));
figure(8);
spectrogram(guitar_out, hamming(win_length), overlap_length, nfft);
title('Bitcrushed Guitar WAV Frequency-Domain');

