/*
  ==============================================================================

    Utilities.h
    Created: 2 Aug 2023 2:57:27pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace std;

template<
typename Attachment,
typename APVTS,
typename Params,
typename ParamName,
typename SliderType
>

void makeAttachment(unique_ptr<Attachment>& attachment, APVTS& apvts, const Params& params, const ParamName& name, SliderType& slider)
{
    attachment = make_unique<Attachment>(apvts,
                                         params.at(name),
                                         slider);
}

template<
typename APVTS,
typename Params,
typename Name
>
juce::RangedAudioParameter& getParam(APVTS& apvts, const Params& params, const Name& name){
    auto param = apvts.getParameter(params.at(name));
    jassert(param != nullptr);
    return *param;
}

juce::String getValString(const juce::RangedAudioParameter& param,
                          bool getLow, juce::String suffix);
template<typename T>
bool truncateKiloValue(T& value)
{
   if(value > static_cast<T>(999))
   {
       value /= static_cast<T>(1000);
       return true;
   }
    return false;
}
template<
typename Labels,
typename ParamType,
typename SuffixType
>
void addLabelPairs(Labels& labels, const ParamType& param, const SuffixType& suffix){
    labels.clear();
    labels.add({0.f, getValString(param, true, suffix)});
    labels.add({1.f, getValString(param, false, suffix)});
}
void drawModuleBackground(juce::Graphics &g,
                          juce::Rectangle<int> bounds);
