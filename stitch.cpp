#include "stitch.h"
#include <math.h>

Stitch::Stitch()
{

}

void Stitch::CalculateLength()
{
    length_ = sqrt((x_ * x_) + (y_ * y_));
}

int Stitch::GetLength()
{
    return length_;
}
