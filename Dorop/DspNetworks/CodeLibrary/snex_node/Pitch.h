template <int NV> struct Pitch
{
    SNEX_NODE(Pitch);

    static const int WINDOW_SIZE = 2048;

    span<float, WINDOW_SIZE> buffer;

    int writePos = 0;
    float phase = 0.0f;

    float pitchSemitones = 7.0f;
    float pitchRatio = 1.0f;

    float readInterpolated(float pos)
    {
        int i1 = (int)pos;
        int i2 = (i1 + 1) % WINDOW_SIZE;

        float frac = pos - (float)i1;

        return buffer[i1] * (1.0f - frac)
             + buffer[i2] * frac;
    }

    void prepare(PrepareSpecs ps)
    {
        int i = 0;
        while (i < WINDOW_SIZE)
        {
            buffer[i] = 0.0f;
            i++;
        }

        writePos = 0;
        phase = 0.0f;

        pitchRatio = Math.pow(2.0f, pitchSemitones / 12.0f);
    }

    void reset()
    {
        int i = 0;
        while (i < WINDOW_SIZE)
        {
            buffer[i] = 0.0f;
            i++;
        }

        writePos = 0;
        phase = 0.0f;
    }

    template <typename ProcessDataType> void process(ProcessDataType& data)
    {
        auto block = data.toAudioBlock();
        float* x = block.getChannelPointer(0);

        int numSamples = data.getNumSamples();

        int i = 0;

        while (i < numSamples)
        {
            float input = x[i];

            buffer[writePos] = input;

            float readA = (float)writePos - phase;
            if (readA < 0.0f)
                readA += (float)WINDOW_SIZE;

            float readB = readA + (float)WINDOW_SIZE * 0.5f;
            if (readB >= (float)WINDOW_SIZE)
                readB -= (float)WINDOW_SIZE;

            float s1 = readInterpolated(readA);
            float s2 = readInterpolated(readB);

            float f = phase / (float)WINDOW_SIZE;

            float g1 = (f < 0.5f) ? (f * 2.0f) : (2.0f - f * 2.0f);
            float g2 = 1.0f - g1;

            x[i] = s1 * g1 + s2 * g2;

            writePos = (writePos + 1) % WINDOW_SIZE;

            phase += (pitchRatio - 1.0f);

            if (phase >= (float)WINDOW_SIZE)
                phase -= (float)WINDOW_SIZE;

            if (phase < 0.0f)
                phase += (float)WINDOW_SIZE;

            i++;
        }
    }

    template <int C> void processFrame(span<float, C>& data) {}

    void handleHiseEvent(HiseEvent& e) {}

    void setExternalData(const ExternalData& d, int index) {}

    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            pitchSemitones = (float)v;
            pitchRatio = Math.pow(2.0f, pitchSemitones / 12.0f);
        }
    }
};