/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BitSmashAndDashAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BitSmashAndDashAudioProcessorEditor (BitSmashAndDashAudioProcessor&);
    ~BitSmashAndDashAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BitSmashAndDashAudioProcessor& audioProcessor;

    juce::Label bitDepthLabel, speedLabel, highShelfCutoffLabel, highShelfGainLabel;
    juce::Slider bitDepthSlider, speedSlider, highShelfCutoffSlider, highShelfGainSlider;

    juce::AudioParameterFloat* bitDepthSliderParameter;
    juce::AudioParameterFloat* speedSliderParameter;
    juce::AudioParameterFloat* highShelfCutoffSliderParameter;
    juce::AudioParameterFloat* highShelfGainSliderParameter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitSmashAndDashAudioProcessorEditor)
};
