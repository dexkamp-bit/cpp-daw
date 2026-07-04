#include "Transport.h"

Transport::Transport()
{
}

Transport::~Transport()
{
}

void Transport::start()
{
    playing.store(true);
    paused.store(false);
}

void Transport::stop()
{
    playing.store(false);
    paused.store(false);
    playheadPosition.store(0);
}

void Transport::pause()
{
    if (playing.load())
    {
        paused.store(true);
        playing.store(false);
    }
}

void Transport::setLoopEnabled(bool shouldLoop)
{
    loopEnabled.store(shouldLoop);
}

double Transport::getPlayheadPositionInSeconds() const
{
    return static_cast<double>(playheadPosition.load()) / sampleRate;
}

void Transport::process(int numSamples)
{
    if (playing.load())
    {
        playheadPosition.fetch_add(numSamples);
    }
}
