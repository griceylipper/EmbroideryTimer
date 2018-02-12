#include "stitch.h"
#include <math.h>

Stitch::Stitch()
{
    for (int i = 0; i < 3; ++i)
    {
        bytes_[i] = 0;
    }
    x_ = 0;
    y_ = 0;
    length_ = 0;
    flags_ = 0;
}

void Stitch::Calculate()
{

//          Bit No:
//          7       6       5       4       3       2       1       0
//Byte 1	y+1     y-1     y+9     y-9     x-9     x+9     x-1     x+1
//Byte 2	y+3     y-3     y+27	y-27	x-27	x+27	x-3     x+3
//Byte 3	jump	color   y+81	y-81	x-81    x+81    set     set;
//                  change

    x_ = ((bytes_[0] & (1 << 0)) ? 1 : 0)
         + ((bytes_[0] & (1 << 1)) ? -1 : 0)
         + ((bytes_[0] & (1 << 0)) ? 9 : 0)
         + ((bytes_[0] & (1 << 2)) ? -9 : 0)
         + ((bytes_[1] & (1 << 3)) ? 3 : 0)
         + ((bytes_[1] & (1 << 1)) ? -3 : 0)
         + ((bytes_[1] & (1 << 2)) ? +27 : 0)
         + ((bytes_[1] & (1 << 3)) ? -27 : 0)
         + ((bytes_[2] & (1 << 2)) ? +81 : 0)
         + ((bytes_[2] & (1 << 3)) ? -81 : 0);
    y_ = ((bytes_[0] & (1 << 4)) ? -9 : 0)
         + ((bytes_[0] & (1 << 5)) ? 9 : 0)
         + ((bytes_[0] & (1 << 6)) ? -1 : 0)
         + ((bytes_[0] & (1 << 7)) ? 1 : 0)
         + ((bytes_[1] & (1 << 4)) ? -27 : 0)
         + ((bytes_[1] & (1 << 5)) ? 27 : 0)
         + ((bytes_[1] & (1 << 6)) ? -3 : 0)
         + ((bytes_[1] & (1 << 7)) ? 3 : 0)
         + ((bytes_[2] & (1 << 4)) ? -81 : 0)
         + ((bytes_[2] & (1 << 5)) ? 81 : 0);
    length_ = sqrt((x_ * x_) + (y_ * y_));
}

int Stitch::GetLength()
{
    return length_;
}

void Stitch::SetBytes(char byte0, char byte1, char byte2)
{
    bytes_[0] = byte0;
    bytes_[1] = byte1;
    bytes_[2] = byte2;
}
