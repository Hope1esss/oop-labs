#pragma once
#include "../include/Point.h"

template <Scalar T>
class Figure
{
    virtual ~Figure() = default;

    virtual void getPointsData() const = 0;

    virtual operator double() const = 0;

    virtual bool operator==(const Figure &other) const = 0;

    virtual Point<T> getGeometricalCenter() const = 0;
};