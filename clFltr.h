#pragma once

class clFltr
{
public:
    clFltr();

    virtual float execute(float value) = 0;

    void reset();

    void setAlpha(float value);
    float getAlpha();
    float getValue();

protected:
    bool  mCleared;
    float mAlpha;
    float mValue;
};

class clFltrLPF : public clFltr
{
public:
    float execute(float value);
};

class clFltrHPF : public clFltr
{
public:
    float execute(float value);
};

