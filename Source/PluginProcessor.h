/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

/*DSP Roadmap
 1) Figure out how to split the audio into 3 bands DONE
 2) Create parameters to control where this split happens DONE
 3) Prove that splitting into 3 bands produces no audible
    artifacts DONE
 4) CCreate audio parameters for the 3 compressor bands.
    these need to live on each band incetance. DONE
 5) Add 2 remaining compressors DONE
 6) Add ability to mute /solo/bypass indivisual compressors DONE
 7) Add input output gain to offset changes in output level DONE
 8) Clean up anything that needs cleaning up DONE
 
 GUI Roadmap
 1) Global Contorols(x-over sliders, gain sliders) DONE
 2) Main Band Controls (attac release, threshold, ratio) DONE
 3) Add solo/mute/bypass buttons DONE
 4) Band select funtctionality DONE
 5) Band select buttons reflect the solo/mute/bypass state DONE
 6) Custom look and feel for sliders and toggle buttons DONE
 7) Spectrum Analyzer Overview DONE
 8) Data structure for spectrum analyzer DONE
 9) Fifo usage in pluginProcessor::processBlock DONE
 10) Implementatio of the analyzer rendering pre-computed paths DONE
 11) Drawing crossovers on top of the analyzer plot DONE
 12) Drawing gain reduction on top of the analyzer DONE
 13) Analyzer bypass
 14) Global Bypass button
 */
#include <JuceHeader.h>
#include "CompressorBand.h"
#include "SingleChannelSampleFifo.h"


using namespace std;

/**
*/
class SimpleMBCompAudioProcessor  : public juce::AudioProcessor {
                            #if JucePlugin_Enable_ARA
                              public juce::AudioProcessorARAExtension
                            #endif
public:
    //==============================================================================
    SimpleMBCompAudioProcessor();
    ~SimpleMBCompAudioProcessor() override;
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const juce::String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    using APVTS = juce::AudioProcessorValueTreeState;
    static APVTS::ParameterLayout createParameterLayout();
    
    APVTS apvts {*this, nullptr, "Parameters", createParameterLayout()};
    
    using BlockType = juce::AudioBuffer<float>;
    SingleChannelSampleFifo<BlockType> leftChannelFifo { Channel::Left };
    SingleChannelSampleFifo<BlockType> rightChannelFifo { Channel::Right };
    
    array<CompressorBand,3> compressors;
    CompressorBand& lowBandComp = compressors[0];
    CompressorBand& midBandComp = compressors[1];
    CompressorBand& highBandComp = compressors[2];
private:
    
    using Filter = juce::dsp::LinkwitzRileyFilter<float>;
//         fc0  fc1
    Filter LP1, AP2,
           HP1, LP2,
                HP2;
//    Filter invAP1, invAP2;
//    juce::AudioBuffer<float> invAPBuffer;
    
    juce::AudioParameterFloat* lowMidCrossover { nullptr };
    juce::AudioParameterFloat* midHighCrossover { nullptr };
    
    array<juce::AudioBuffer<float>, 3> filterBuffers;
    
    juce::dsp::Gain<float> inputGain, outputGain;
    juce::AudioParameterFloat* inputGainParam { nullptr };
    juce::AudioParameterFloat* outputGainParam { nullptr };
    
    template<typename T, typename U>
    void applyGain(T& buffer, U& gain){
        auto block = juce::dsp::AudioBlock<float>(buffer);
        auto ctx = juce::dsp::ProcessContextReplacing<float>(block);
        gain.process(ctx);
    }
    void updateState();
    
    void splitBands(const juce::AudioBuffer<float>& inputBuffer);
    
    juce::dsp::Oscillator<float> osc;
    juce::dsp::Gain<float> gain;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMBCompAudioProcessor);
};
