template <int NV> struct pitch_shifter
{
    SNEX_NODE(pitch_shifter);

    void prepare(PrepareSpecs specs)
    {
    }

    void reset()
    {
    }

    template <typename ProcessDataType> void process(ProcessDataType& data)
    {
    }

    template <int C> void processFrame(span<float, C>& data)
    {
    }

    void handleHiseEvent(HiseEvent& e)
    {
    }

    void setExternalData(const ExternalData& d, int index)
    {
    }

    template <int P> void setParameter(double v)
    {
    }
};