class Historico
{
public:
    double reads = 0;
    double writes = 0;
    double hits = 0;
    double misses = 0;
    Historico() {}
    double calculateMissRate()
    {
        return misses / reads;
    }
    double calculateHitRate()
    {
        return hits / reads;
    }
};