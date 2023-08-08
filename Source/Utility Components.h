/*
  ==============================================================================

    Utility Components.h
    Created: 2 Aug 2023 2:44:08pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

struct Placeholder: juce::Component
{
    Placeholder();
    void paint(juce::Graphics& g) override;
    juce::Colour customColor;
    
};
struct RotarySlider: juce::Slider{
    RotarySlider();
};
