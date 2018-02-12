#ifndef STITCH_H
#define STITCH_H


class Stitch
{
public:
    Stitch();
    void CalculateLength();
    int GetLength();

private:
    char bytes_[3];
    char padding_;
    int x_;
    int y_;
    int length_;
    int flags_;
};

#endif // STITCH_H
