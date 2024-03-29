/*
  ==============================================================================

    Utilities.cpp
    Created: 2 Aug 2023 2:57:27pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#include "Utilities.h"

#include "LookAndFeel.h"

juce::String getValString(const juce::RangedAudioParameter& param,
                          bool getLow, juce::String suffix)
{
    juce::String str;
    
    auto val = getLow ? param.getNormalisableRange().start :
                        param.getNormalisableRange().end;
    
    bool useK = truncateKiloValue(val);
    str << val;
    
    if ( useK )
        str << "K";
    
    str << suffix;
    
    return str;
}

juce::Rectangle<int> drawModuleBackground(juce::Graphics &g,
                          juce::Rectangle<int> bounds)
{
    using namespace juce;
    g.setColour(Colours::lightslategrey);
    g.fillAll();
    auto localBounds = bounds;
    bounds.reduce(3,3);
    g.setColour(Colours::lightgrey);
    g.fillRoundedRectangle(bounds.toFloat(), 3);
    
    g.drawRect(localBounds);
    return bounds;
}
