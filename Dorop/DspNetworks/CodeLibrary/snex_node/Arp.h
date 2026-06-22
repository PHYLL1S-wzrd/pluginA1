template <int NV> struct StepGate
{
    SNEX_NODE(StepGate);

    float step0 = 1.0f;
    float step1 = 0.0f;
    float step2 = 1.0f;
    float step3 = 0.0f;

    int counter = 0;
    int index = 0;
    int rate = 2000;

    float getStep()
    {
        if (index == 0) return step0;
        if (index == 1) return step1;
        if (index == 2) return step2;
        return step3;
    }

    template <typename ProcessDataType> void process(ProcessDataType& data)
    {
        auto& d = data.template as<ProcessData<1>>();
        auto block = d.toAudioBlock();

        float* x = block.getChannelPointer(0);

        int n = data.getNumSamples();
        int i = 0;

        while (i < n)
        {
            if (counter++ > rate)
            {
                counter = 0;
                index = (index + 1) & 3;
            }

            float g = getStep();

            x[i] *= g;

            i++;
        }
    }

    template <int P> void setParameter(double v)
    {
        if (P == 0) rate = (int)(v * 1000.0f);
        if (P == 1) step0 = (float)v;
        if (P == 2) step1 = (float)v;
        if (P == 3) step2 = (float)v;
        if (P == 4) step3 = (float)v;
    }
};