#include <juce_extensions/juce_extensions.h>
#include "dev/GridInterpreter.h"

//==============================================================================
class Plugin : public plugin::AudioProcessor
{
public:
    //==============================================================================
    void prepareToPlay (double, int) override {}
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override {}
    //==============================================================================
    juce::MidiKeyboardState& getMidiState() { return midiState; }
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
private:
    //==============================================================================
    // Your private member variables go here...
    juce::MidiKeyboardState midiState;
};


//==============================================================================
class Editor : public plugin::AudioProcessorEditor
{
public:
    //==============================================================================
    Editor (Plugin& p) : AudioProcessorEditor (p), processorRef (p)
    {
        midiKeyboard.reset (new juce::MidiKeyboardComponent (processorRef.getMidiState(),
                                juce::MidiKeyboardComponent::horizontalKeyboard));

        auto layout = R"(
            grid-template-columns: 1fr 1fr 1fr 1fr;
            grid-template-rows: 25px 1fr 60px;
            grid-gap: 5px;
            grid-template-areas: 
                "settings settings tempo tempo"
                "attack decay sustain release"
                "keyboard keyboard keyboard keyboard"
            )";
        
        auto items = std::initializer_list<std::pair<juce::Component*, juce::String>> 
        { 
            { &settingsButton, "settings" },
            { &tempoSlider, "tempo" },
            { &attackSlider, "attack" },
            { &decaySlider, "decay" },
            { &sustainSlider, "sustain" },
            { &releaseSlider, "release" },
            { midiKeyboard.get(), "keyboard" }
        };

        interpreter.setLayout (layout, items);
        
        addAndMakeVisible ({ &settingsButton, &tempoSlider, &attackSlider, &decaySlider, 
                             &sustainSlider, &releaseSlider, midiKeyboard.get() });

        setUsingNativeTitleBar (true);
        setOpaque (false);
        setResizable (true, true);
        setSize (400, 240);
    }

    //==============================================================================
    void resized() override { interpreter.performLayout (getLocalBounds().reduced (5)); }

private:
    //==============================================================================
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Plugin& processorRef;
    GridInterpreter interpreter;

    std::unique_ptr<juce::MidiKeyboardComponent> midiKeyboard;
    juce::TextButton settingsButton { "Settings" };
    juce::Slider tempoSlider { juce::Slider::LinearBar, juce::Slider::NoTextBox };

    juce::Slider attackSlider  { juce::Slider::LinearBarVertical, juce::Slider::NoTextBox };
    juce::Slider decaySlider   { juce::Slider::LinearBarVertical, juce::Slider::NoTextBox };
    juce::Slider sustainSlider { juce::Slider::LinearBarVertical, juce::Slider::NoTextBox };
    juce::Slider releaseSlider { juce::Slider::LinearBarVertical, juce::Slider::NoTextBox };
};





//==============================================================================
// This is called by the plugin and creates a new instance of 
// the plugin's editor..
juce::AudioProcessorEditor* Plugin::createEditor()
{
    return new Editor (*this);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Plugin();
}

/* 
//==============================================================================
// This creates our standalone filter which is used to host the plugin..
#if JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP
 juce::JUCEApplicationBase* juce_CreateApplication() 
 {
    auto options = [] () -> StandaloneFilterApp::Options
    {
        StandaloneFilterApp::Options opts;
        return opts;
    }();

    return new StandaloneFilterApp (options);
 }
#endif
 */