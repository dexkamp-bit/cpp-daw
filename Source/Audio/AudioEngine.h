#pragma once

#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <memory>
#include "Transport.h"
#include "ProcessorGraph.h"

class AudioEngine : public juce::AudioIODeviceCallback
{
public:
    AudioEngine();
    ~AudioEngine() override;

    // AudioIODeviceCallback interface
    void audioDeviceIOCallback(const float** inputChannelData,
                               int numInputChannels,
                               float** outputChannelData,
                               int numOutputChannels,
                               int numSamples) override;
    
    void audioDeviceAboutToStart(juce::AudioIODevice* device) override;
    void audioDeviceStopped() override;

    // Engine control
    void initialise();
    void shutdown();
    void start();
    void stop();

    Transport& getTransport() { return *transport; }
    ProcessorGraph& getGraph() { return *graph; }

    juce::AudioDeviceManager& getDeviceManager() { return deviceManager; }

private:
    juce::AudioDeviceManager deviceManager;
    std::unique_ptr<Transport> transport;
    std::unique_ptr<ProcessorGraph> graph;
    
    bool isInitialised = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};
