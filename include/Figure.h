#pragma once
#include "../include/Point.h"
class Figure
{
public:
    virtual ~Figure() = default;

    virtual void getPointsData() const = 0;

    virtual operator double() const = 0;

    virtual bool operator==(const Figure &other) const = 0;

    virtual Point getGeometricalCenter() const = 0;
};