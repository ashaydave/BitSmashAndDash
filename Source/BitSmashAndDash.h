#ifndef ASHAY_BITSMASHER_H
#define ASHAY_BITSMASHER_H

/*
  ==============================================================================

    BitSmashAndDash.h
    Created: 16 Sep 2023 6:11:02pm
    Author:  ashay

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <math.h>

namespace Ashay
{
    class BitSmashAndDash
    {
    public:
        BitSmashAndDash();
        ~BitSmashAndDash();
        void process(juce::AudioBuffer<float>& buffer, float bitDepthParameter, float speedParameter, float highShelfCutoffParameter, float highShelfGainParameter, double sampleRate);
        void reset();

    private:
        float bitDepth, speed;
        float highShelfCutoff, highShelfGain;

        float step, phasor, quantizedValue;
        float v0, h0, wc, c;
        float inputFiltered;
    };
}


#endif