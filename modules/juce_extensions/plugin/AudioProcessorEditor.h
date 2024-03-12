#pragma once
#include "AudioProcessor.h"

namespace plugin
{
    //==============================================================================
    class AudioProcessorEditor  : public juce::AudioProcessorEditor
    {
    public:
        //==============================================================================
        explicit AudioProcessorEditor (AudioProcessor&);
        ~AudioProcessorEditor() override;

        //==============================================================================
        void paint (juce::Graphics&) override;
        
        //==============================================================================
        void setUsingNativeTitleBar (bool useNativeTitleBar);
        void addAndMakeVisible(const std::initializer_list<Component*>& components);
    };

} // namespace plugin