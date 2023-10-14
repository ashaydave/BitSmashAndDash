/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitSmashAndDashAudioProcessorEditor::BitSmashAndDashAudioProcessorEditor (BitSmashAndDashAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 200);

    auto parameterTree = audioProcessor.getParameters();

    addAndMakeVisible(bitDepthLabel);
    bitDepthLabel.setText("Bit Depth", juce::dontSendNotification);
    bitDepthLabel.setColour(juce::Label::textColourId, juce::Colours::lightgoldenrodyellow);
    bitDepthLabel.setJustificationType(juce::Justification::centred);
    bitDepthLabel.setFont(juce::Font(14.0f, juce::Font::bold));

    addAndMakeVisible(bitDepthSlider);
    bitDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    bitDepthSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::lightgoldenrodyellow);
    bitDepthSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    bitDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 30);

    bitDepthSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
    bitDepthSlider.setRange(bitDepthSliderParameter->range.start, bitDepthSliderParameter->range.end, 0.1);

    bitDepthSlider.setValue(*bitDepthSliderParameter, juce::NotificationType::dontSendNotification);

    bitDepthSlider.onValueChange = [this]
    {
        *bitDepthSliderParameter = bitDepthSlider.getValue();
    };

    /*-------------*/

    addAndMakeVisible(speedLabel);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.setColour(juce::Label::textColourId, juce::Colours::lightgoldenrodyellow);
    speedLabel.setJustificationType(juce::Justification::centred);
    speedLabel.setFont(juce::Font(14.0f, juce::Font::bold));

    addAndMakeVisible(speedSlider);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    speedSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::lightgoldenrodyellow);
    speedSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 30);

    speedSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
    speedSlider.setRange(speedSliderParameter->range.start, speedSliderParameter->range.end, 0.01);

    speedSlider.setValue(*speedSliderParameter, juce::NotificationType::dontSendNotification);

    speedSlider.onValueChange = [this]
    {
        *speedSliderParameter = bitDepthSlider.getValue();
    };

    /*------------*/

    addAndMakeVisible(highShelfCutoffLabel);
    highShelfCutoffLabel.setText("HS Cutoff (Hz)", juce::dontSendNotification);
    highShelfCutoffLabel.setColour(juce::Label::textColourId, juce::Colours::lightgoldenrodyellow);
    highShelfCutoffLabel.setJustificationType(juce::Justification::centred);
    highShelfCutoffLabel.setFont(juce::Font(14.0f, juce::Font::bold));

    addAndMakeVisible(highShelfCutoffSlider);
    highShelfCutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    highShelfCutoffSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::lightgoldenrodyellow);
    highShelfCutoffSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    highShelfCutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);

    highShelfCutoffSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);
    highShelfCutoffSlider.setRange(highShelfCutoffSliderParameter->range.start, highShelfCutoffSliderParameter->range.end, 0.1);

    highShelfCutoffSlider.setValue(*highShelfCutoffSliderParameter, juce::NotificationType::dontSendNotification);

    highShelfCutoffSlider.onValueChange = [this]
    {
        *highShelfCutoffSliderParameter = highShelfCutoffSlider.getValue();
    };

    /*------------*/

    addAndMakeVisible(highShelfGainLabel);
    highShelfGainLabel.setText("HS Gain (dB)", juce::dontSendNotification);
    highShelfGainLabel.setColour(juce::Label::textColourId, juce::Colours::lightgoldenrodyellow);
    highShelfGainLabel.setJustificationType(juce::Justification::centred);
    highShelfGainLabel.setFont(juce::Font(14.0f, juce::Font::bold));

    addAndMakeVisible(highShelfGainSlider);
    highShelfGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    highShelfGainSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::lightgoldenrodyellow);
    highShelfGainSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    highShelfGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 30);

    highShelfGainSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(3);
    highShelfGainSlider.setRange(highShelfGainSliderParameter->range.start, highShelfGainSliderParameter->range.end, 1);

    highShelfGainSlider.setValue(*highShelfGainSliderParameter, juce::NotificationType::dontSendNotification);

    highShelfGainSlider.onValueChange = [this]
    {
        *highShelfGainSliderParameter = highShelfGainSlider.getValue();
    };
}

BitSmashAndDashAudioProcessorEditor::~BitSmashAndDashAudioProcessorEditor()
{
}

//==============================================================================
void BitSmashAndDashAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Bit Smash And Dash", getLocalBounds(), juce::Justification::bottomRight, 1);
}

void BitSmashAndDashAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();
    auto width = bounds.getWidth();
    auto height = bounds.getHeight();

    float labelWidth = 100.0f;
    float labelHeight = 20.0f;
    float sliderWidth = 100.0f;
    float sliderHeight = 100.0f;
    float xMargin = 10.0f;
    float yMargin = 10.0f;

    bitDepthLabel.setBounds(width / 2 - 2 * sliderWidth - xMargin, height / 2 - sliderHeight / 2 - labelHeight - yMargin, labelWidth, labelHeight);
    speedLabel.setBounds(width / 2 - sliderWidth - xMargin, height / 2 - sliderHeight / 2 - labelHeight - yMargin, labelWidth, labelHeight);
    highShelfCutoffLabel.setBounds(width / 2 - xMargin, height / 2 - sliderHeight / 2 - labelHeight - yMargin, labelWidth, labelHeight);
    highShelfGainLabel.setBounds(width / 2 + sliderWidth - xMargin, height / 2 - sliderHeight / 2 - labelHeight - yMargin, labelWidth, labelHeight);

    bitDepthSlider.setBounds(width / 2 - 2 * sliderWidth - xMargin, height / 2 - sliderHeight / 2 + yMargin, sliderWidth, sliderHeight);
    speedSlider.setBounds(width / 2 - sliderWidth - xMargin, height / 2 - sliderHeight / 2 + yMargin, sliderWidth, sliderHeight);
    highShelfCutoffSlider.setBounds(width / 2 - xMargin, height / 2 - sliderHeight / 2 + yMargin, sliderWidth, sliderHeight);
    highShelfGainSlider.setBounds(width / 2 + sliderWidth - xMargin, height / 2 - sliderHeight / 2 + yMargin, sliderWidth, sliderHeight);
}
