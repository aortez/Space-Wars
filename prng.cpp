#include <qglobal.h>
#include <limits.h>
#include "stdlib.h"
#include "prng.h"

double rngp( void )
{
    const double r = qrand() / static_cast<double>( RAND_MAX );
    return r;
}

double rngb( void )
{
    return ( rngp() - 0.5 ) * 2;
}

double randcollider( void )
{
    return static_cast< double >( qrand() ) / RAND_MAX * 0.01;
}
