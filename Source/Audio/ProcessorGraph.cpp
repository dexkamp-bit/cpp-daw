#include "ProcessorGraph.h"

ProcessorGraph::ProcessorGraph()
{
}

ProcessorGraph::~ProcessorGraph()
{
}

void ProcessorGraph::process(const float** inputChannelData,
                             int numInputChannels,
                             float** outputChannelData,
                             int numOutputChannels,
                             int numSamples)
{
    // For now, pass audio through directly (silence)
    // This will be expanded in Milestone 2 to handle tracks, plugins, mixing, etc.
    
    for (int ch = 0; ch < numOutputChannels; ++ch)
    {
        juce::FloatVectorOperations::clear(outputChannelData[ch], numSamples);
    }
}
