#ifndef SPLATGENERATORSTRATEGY_H
#define SPLATGENERATORSTRATEGY_H


class SplatGeneratorStrategy
{
public:
    virtual ~SplatGeneratorStrategy() {}
    virtual void Generate() = 0;
};

class GenSimpleBrushStrategy : public SplatGeneratorStrategy
{
public:
    void Generate();
};

class GenWetOnDryBrush : public SplatGeneratorStrategy
{
public:
    void Generate();
};

class GenCruncyBrush : public SplatGeneratorStrategy
{
public:
    void Generate();
};

#endif // SPLATGENERATORSTRATEGY_H
