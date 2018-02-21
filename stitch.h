#ifndef STITCH_H
#define STITCH_H


class Stitch
{
public:
    Stitch();
    void Calculate();
    float GetLength();
    void SetBytes(char byte0, char byte1, char byte2);

private:
    unsigned char bytes_[3];
    unsigned char padding_;
    int x_;
    int y_;
    float length_;
    unsigned int flags_;
};

#endif // STITCH_H
