#include <qglobal.h>
#include <limits.h>
#include "stdlib.h"
#include "rand.h"

double rng( void )
{
    const double r = qrand() / static_cast<double>( RAND_MAX );
    return r;
}

double randcollider( void ) {
    return static_cast< double >( qrand() ) / RAND_MAX * 0.01;
}
