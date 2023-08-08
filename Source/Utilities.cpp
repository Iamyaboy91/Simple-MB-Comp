/*
  ==============================================================================

    Utilities.cpp
    Created: 2 Aug 2023 2:57:27pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#include "Utilities.h"

juce::String getValString(const juce::RangedAudioParameter& param,
                          bool getLow, juce::String suffix)
{
    juce::String str;
    
    auto val = getLow ? param.getNormalisableRange().start :
                        param.getNormalisableRange().end;
    
    bool useK = truncateKiloValue(val);
    
    if ( useK )
        str << "K";
    
    str << suffix;
    
    return str;
}

void drawModuleBackground(juce::Graphics &g,
                          juce::Rectangle<int> bounds)
{
    using namespace juce;
    g.setColour(Colours::blueviolet);
    g.fillAll();
    
    auto localBounds = bounds;
    
    bounds.reduce(3,3);
    g.setColour(Colours::black);
    g.fillRoundedRectangle(bounds.toFloat(), 3);
    
    g.drawRect(localBounds);
    
}
