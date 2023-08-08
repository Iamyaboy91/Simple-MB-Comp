/*
  ==============================================================================

    GlobalControls.h
    Created: 2 Aug 2023 5:28:40pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>
#include "RotarySliderWithLabels.h"

using namespace std;

struct GlobalControls : juce::Component
{
    GlobalControls(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    using RSWL = RotarySliderWithLabels;
    unique_ptr<RSWL> inGainSlider, lowMidXoverSlider, midHighXoverSlider, outGainSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    unique_ptr<Attachment> lowMidXoverSliderAttachment,
                           midHighXoverSliderAttachment,
                           inGainSlidetrAttachment,
                           outGainSliderAttachment;
};
