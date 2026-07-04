#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
    transport = std::make_unique<Transport>();
    graph = std::make_unique<ProcessorGraph>();
}

AudioEngine::~AudioEngine()
{
    shutdown();
}

void AudioEngine::initialise()
{
    if (isInitialised) return;

    // Set up audio device manager with default device
    juce::String errorMessage = deviceManager.initialiseWithDefaultDevices(2, 2);
    
    if (errorMessage.isEmpty())
    {
        deviceManager.addAudioCallback(this);
        isInitialised = true;
        DBG("Audio Engine Initialised");
    }
    else
    {
        DBG("Audio Initialisation Error: " + errorMessage);
    }
}

void AudioEngine::shutdown()
{
    if (!isInitialised) return;
    
    stop();
    deviceManager.removeAudioCallback(this);
    deviceManager.closeAudioDevice();
    isInitialised = false;
    DBG("Audio Engine Shut Down");
}

void AudioEngine::start()
{
    transport->start();
}

void AudioEngine::stop()
{
    transport->stop();
}

void AudioEngine::audioDeviceIOCallback(const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples)
{
    // Update transport and get playhead position
    transport->process(numSamples);

    // Process audio graph
    graph->process(inputChannelData, numInputChannels,
                   outputChannelData, numOutputChannels,
                   numSamples);
}

void AudioEngine::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
    transport->setSampleRate(device->getCurrentSampleRate());
    graph->setSampleRate(device->getCurrentSampleRate());
    DBG("Audio Device Started: " + device->getName() + " @ " 
        + juce::String(device->getCurrentSampleRate()) + " Hz");
}

void AudioEngine::audioDeviceStopped()
{
    DBG("Audio Device Stopped");
}
