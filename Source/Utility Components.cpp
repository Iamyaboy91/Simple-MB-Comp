/*
  ==============================================================================

    Utility Components.cpp
    Created: 2 Aug 2023 2:44:08pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#include "Utility Components.h"
//==============================================================================
Placeholder::Placeholder()
{
    juce::Random r;
    customColor = juce::Colour(r.nextInt(255),r.nextInt(255),r.nextInt(255));
}

void Placeholder::paint(juce::Graphics& g)
{
    g.fillAll(customColor);
}
//==============================================================================
RotarySlider::RotarySlider() :
juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalDrag,
             juce::Slider::TextEntryBoxPosition::NoTextBox)
{}
