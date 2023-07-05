#include "clFltr.h"

clFltr::clFltr()
{
    reset();

    mAlpha = 0;
    mValue = 0;
}

void clFltr::reset()
{
    mCleared = true;
}

float clFltr::getValue()
{
    return mValue;
}

void clFltr::setAlpha(float value)
{
    if (value < 0) {
        return;
    }

    if (value >= 1) {
        return;
    }

    mAlpha = value;
}

float clFltr::getAlpha()
{
    return mAlpha;
}

//--- clFltrLPF ------------------

float clFltrLPF::execute(float value)
{
    if (mCleared == true) {
        mCleared = false;
        mValue = value;
    }
    else {
        mValue = mValue * mAlpha + value * (1.0 - mAlpha);
    }

    return mValue;
}

//--- clFltrHPF ------------------

float clFltrHPF::execute(float value)
{
    if (mCleared == true) {
        mCleared = false;
        mValue = value;
    }
    else {
        mValue = mValue * mAlpha + value * (1.0 - mAlpha);
    }

    mValue = value - mValue;

    return mValue;
}

