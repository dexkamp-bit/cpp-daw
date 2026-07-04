#include "MainComponent.h"

MainComponent::MainComponent()
{
    audioEngine = std::make_unique<AudioEngine>();
    setSize(1920, 1080);
}

MainComponent::~MainComponent()
{
    audioEngine = nullptr;
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff1e1e1e));
    
    g.setColour(juce::Colours::white);
    g.setFont(24.0f);
    g.drawText("Fluid DAW v0.1.0", getLocalBounds(), juce::Justification::centred, true);
    
    g.setFont(14.0f);
    g.drawText("Audio Engine: Ready\nMilestone 1: Scaffold Complete", 
               getLocalBounds().reduced(20).withY(100), 
               juce::Justification::centredLeft, true);
}

void MainComponent::resized()
{
    // Layout will be implemented as UI components are added
}
