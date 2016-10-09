#ifndef OKUMURAHATAPATHLOSSMAP_H
#define OKUMURAHATAPATHLOSSMAP_H

class OkumuraHataPathlossMap
{
public:
    static OkumuraHataPathlossMap & createInstance()
    {
        static OkumuraHataPathlossMap instance;
        return instance;
    }

private:
    OkumuraHataPathlossMap() {}
    OkumuraHataPathlossMap(const OkumuraHataPathlossMap &) {}



};

#endif // OKUMURAHATAPATHLOSSMAP_H
