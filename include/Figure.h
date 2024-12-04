#pragma once
#include <iostream>
#include "Point.h"

class Figure
{
public:
    virtual ~Figure() = default;

    virtual operator double() const = 0;
    virtual Point geometricalCenter() const = 0;

    virtual bool operator==(const Figure &other) const = 0;

    virtual void printInfo() const = 0;
};