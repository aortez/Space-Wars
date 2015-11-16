#include <qglobal.h>
#include <limits.h>
#include "stdlib.h"
#include "rand.h"

double rngp( void )
{
    const double r = qrand() / static_cast<double>( RAND_MAX );
    return r;
}

double rngb( void )
{
    return ( rngp() - 0.5 ) * 2;
}

double rngrange( double begin, double end )
{
    // generate [0,1], scale into range, then shift into begin offset
    const double range = end - begin;
    const double r = rngp() * range + begin;
    return r;
}
