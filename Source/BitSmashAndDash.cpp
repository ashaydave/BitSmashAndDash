/*
  ==============================================================================

    BitSmashAndDash.cpp
    Created: 16 Sep 2023 6:10:52pm
    Author:  ashay

  ==============================================================================
*/

#include "BitSmashAndDash.h"


Ashay::BitSmashAndDash::BitSmashAndDash()
{
    bitDepth = 0;
    speed = 0;
    highShelfCutoff = 0;
    highShelfGain = 0;
    step = 0;
    phasor = 0;
    quantizedValue = 0;
    c = 0;
    v0 = 0;
    h0 = 0;
    wc = 0;
    inputFiltered = 0;
}

Ashay::BitSmashAndDash::~BitSmashAndDash()
{
}


void Ashay::BitSmashAndDash::process(juce::AudioBuffer<float>& buffer, float bitDepthParameter, float speedParameter, float highShelfCutoffParameter, float highShelfGainParameter, double sampleRate)
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();

    step = 1 / std::pow(2, bitDepthParameter);
    phasor = 0;
    v0 = std::pow(10, (highShelfGainParameter / 20.0f));
    h0 = v0 - 1;
    wc = 2 * juce::MathConstants<float>::pi * float(highShelfCutoffParameter) / float(sampleRate);
    if (highShelfGainParameter >= 0.0f)
    {
        c = (std::tan(juce::MathConstants<float>::pi * wc / 2.0f) - 1.0f) / (std::tan(juce::MathConstants<float>::pi * wc / 2.0f) + 1.0f); // boost
    }
    else if (highShelfGainParameter < 0.0f)
    {
        c = (std::tan(juce::MathConstants<float>::pi * wc / 2.0f) - v0) / (std::tan(juce::MathConstants<float>::pi * wc / 2.0f) + v0); // cut
    }


    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; sample++)
        {
            phasor = phasor + speedParameter;
            if (phasor >= 1.0f)
            {
                phasor -= 1.0f;
                quantizedValue = step * std::floor(*channelData / step + 0.5f);
            }
            *channelData = quantizedValue;

           
            inputFiltered = 0.0f;

            float inputSample = *channelData;
            float inputFilteredNew = inputSample - c * inputFiltered;
            float outputFiltered = c * inputFilteredNew + inputFiltered;
            inputFiltered = inputFilteredNew;
            *channelData = 0.5f * h0 * (inputSample - outputFiltered) + inputSample;
            channelData++;
        }
    }
}

void Ashay::BitSmashAndDash::reset()
{ 
}