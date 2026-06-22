template <int NV> struct WarmWidth
{
    SNEX_NODE(WarmWidth);

    float drive = 1.2f;
    float width = 0.5f;

    template <typename ProcessDataType> void process(ProcessDataType& data)
    {
        auto block = data.toAudioBlock();

        float* L = block.getChannelPointer(0);
        float* R = block.getChannelPointer(1);

        int i = 0;
        int n = data.getNumSamples();

        while (i < n)
        {
            float l = L[i];
            float r = R[i];

            // soft saturation (NO Math.*)
            l = l / (1.0f + (l < 0 ? -l : l));
            r = r / (1.0f + (r < 0 ? -r : r));

            l *= drive;
            r *= drive;

            float mid = (l + r) * 0.5f;
            float side = (l - r) * 0.5f;

            side *= width;

            L[i] = mid + side;
            R[i] = mid - side;

            i++;
        }
    }

    template <int P> void setParameter(double v)
    {
        if (P == 0) drive = (float)v;
        if (P == 1) width = (float)v;
    }
};