/*
  ==============================================================================

    CompressorBandControls.h
    Created: 2 Aug 2023 3:16:04pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>
#include "RotarySliderWithLabels.h"
using namespace std;

struct CompressorBandControls: juce::Component, juce::Button::Listener
{
    CompressorBandControls(juce::AudioProcessorValueTreeState& apvts);
    ~CompressorBandControls() override;
    void resized() override;
    void paint(juce::Graphics& g) override;
    
    void buttonClicked(juce::Button* button) override;
private:
    juce::AudioProcessorValueTreeState& apvts;
    
    RotarySliderWithLabels attackSlider, releaseSlider, thresholdSlider /*ratioSlider*/;
    RatioSlider ratioSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    unique_ptr<Attachment> attackSliderAttachment,
                           releaseSliderAttachment,
                           thresholdSliderAttachment,
                           ratioSliderAttachment;
    juce::ToggleButton bypassButton, soloButton, muteButton, lowBand, midBand, highBand;
    
    using BtnAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    unique_ptr<BtnAttachment> bypassButtonAttachment,
                              soloButtonAttachment,
                              muteButtonAttachment;
    juce::Component::SafePointer<CompressorBandControls> safePtr {this};
    
    juce::ToggleButton* activeBand = &lowBand;
    
    
    void updateAttachments();
    
    void updateSliderEnablements();
    void updateSoloMuteBypassToggleState(juce::Button& clickedButton);
    void updateActiveBandFillColours(juce::Button& clickedButton);
    
    void resetActiveBandColours();
    static void refreshBandButtonColours(juce::Button& band,
                                         juce::Button& colorSource);
    void updateBandSelectButtonStates();
    
};
