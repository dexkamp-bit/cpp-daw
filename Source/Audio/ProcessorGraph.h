#pragma once

#include <juce_core/juce_core.h>
#include <vector>
#include <memory>

class ProcessorGraph
{
public:
    ProcessorGraph();
    ~ProcessorGraph();

    void setSampleRate(double sr) { sampleRate = sr; }
    double getSampleRate() const { return sampleRate; }

    void setBlockSize(int blockSize) { this->blockSize = blockSize; }
    int getBlockSize() const { return blockSize; }

    // Audio processing (placeholder for now)
    void process(const float** inputChannelData,
                 int numInputChannels,
                 float** outputChannelData,
                 int numOutputChannels,
                 int numSamples);

private:
    double sampleRate = 44100.0;
    int blockSize = 256;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProcessorGraph)
};
