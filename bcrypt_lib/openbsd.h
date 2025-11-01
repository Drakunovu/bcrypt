#ifndef ARC4RANDOM_H_INCLUDED
#define ARC4RANDOM_H_INCLUDED

#include <cstddef>
#include <random>

inline
void arc4random_buf(void *buf, size_t nbytes)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dist(0, 255);

    unsigned char* p = static_cast<unsigned char*>(buf);
    for( size_t n = 0; n < nbytes; ++n) {
        p[n] = static_cast<unsigned char>(dist(gen));
    }
}

inline
void arc4random_init(void)
{

}

#endif // ARC4RANDOM_H_INCLUDED