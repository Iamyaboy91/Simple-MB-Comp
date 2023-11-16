/*
  ==============================================================================

    LookAndFeel.h
    Created: 2 Aug 2023 12:47:33pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

#define USE_LIVE_CONSTANT true

#if USE_LIVE_CONSTANT
#define colorHelper(c) JUCE_LIVE_CONSTANT(c);
#else
#define colorHelper(c);
#endif


namespace ColorScheme 
{
inline juce::Colour getSliderBorderColor()
{
    return colorHelper(juce::Colour(0xff2f5219) );
}
inline juce::Colour getModuleColor()
{
    return colorHelper(juce::Colour(0xff272f04));
}
inline juce::Colour getTextHighLight()
{
    return colorHelper(juce::Colours::black);
}
inline juce::Colour getTextColor()
{
    return colorHelper(juce::Colours::darkgrey);
}
}

struct LookAndFeel : juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics&,
                           int x, int y, int width, int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider&) override;
    
    void drawToggleButton (juce::Graphics &g,
                           juce::ToggleButton & toggleButton,
                           bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown) override;
};
