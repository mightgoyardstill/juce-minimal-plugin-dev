#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

extern juce::JUCEApplicationBase* juce_CreateApplication();

struct StandaloneFilterApp : public juce::JUCEApplication
{
    struct Options
    {
    };

    StandaloneFilterApp (Options& options)
    {
    };

    ~StandaloneFilterApp() override
    {};

    const juce::String getApplicationName() override
    {
        return "StandaloneFilterApp";
    }

    const juce::String getApplicationVersion() override
    {
        return "1.0.0";
    }

    void initialise (const juce::String& commandLine) override
    {
        DBG("StandaloneFilterApp::initialise");
    }

    void shutdown() override
    {
        DBG("StandaloneFilterApp::shutdown");
    }
};