classdef bitSmash < audioPlugin
    % Bit Crusher with High Shelf Control
    % Author: Ashay Dave
    % email: apd122@miami.edu
    
    % Define tunable properties -> PluginEditor & PluginProcessor
    properties
        bitDepth = 16;
        normalizedFreq = 0.5; % should be between 0 to 1.
        highShelfCutoff = 18000;
        highShelfGain = 0;
    end

    properties (Access = private)
        fs = 48000;
    end
    
    % Map tunable property to plugin parameter
    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('bitDepth',...
            'DisplayName','Bit Depth',...
            'Label', 'Bit(s)',...
            'Mapping',{'lin', 1, 16}), ...
            audioPluginParameter('normalizedFreq',...
            'DisplayName','Speed',...
            'Label', 'Hz',...
            'Mapping',{'lin', 0.10, 1.00}), ...
            audioPluginParameter('highShelfCutoff',...
            'DisplayName','High Shelf Cutoff',...
            'Label', 'Hz',...
            'Mapping',{'log', 30, 18000}), ...
            audioPluginParameter('highShelfGain',...
            'DisplayName','High Shelf Gain',...
            'Label', 'dB',...
            'Mapping',{'lin', -12, 12}));
    end
    
    % Define audio processing
    methods
        function output = process(plugin, input)
            step = 1/2^(plugin.bitDepth);
            phasor = 0;
            quantizedValue = 0;
            output = zeros(size(input,2));

            for channel = 1:size(input,2)
                for n = 1:length(input)
                phasor = phasor + plugin.normalizedFreq;
                    if (phasor >= 1.0)
                    phasor = phasor - 1.0;
                    quantizedValue = step * floor(input(n, channel)/step + 0.5 );
                    end
                output(n, channel) = quantizedValue; %sample and hold
                end
            end

            for channel = 1:size(input,2)

                % Apply high-shelf filter
                output(:, channel) = plugin.highShelving(output(:, channel));
             end
        end

        function set.highShelfCutoff(plugin, val)
            plugin.highShelfCutoff = val;
        end

        function set.highShelfGain(plugin, val)
            plugin.highShelfGain = val;
        end
        
        % High Shelf function
        function output = highShelving (plugin, input)
             V0 = 10^(plugin.highShelfGain/20);
             H0 = V0 - 1;
             Wc = 2*pi*plugin.highShelfCutoff/plugin.fs;
             output = zeros(size(input));
             if plugin.highShelfGain >= 0
                  c = (tan(pi*Wc/2)-1) / (tan(pi*Wc/2)+1); % boost
             else
                  c = (tan(pi*Wc/2)-V0) / (tan(pi*Wc/2)+V0); % cut
             end
                inputFiltered = 0;
             for i = 1:length(input)
                inputFilteredNew = input(i) - c*inputFiltered;
                outputFiltered = c * inputFilteredNew + inputFiltered;
                inputFiltered = inputFilteredNew;
                output(i) = 0.5 * H0 * (input(i) - outputFiltered) + input(i);
             end
        end
    end
end
