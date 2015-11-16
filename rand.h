#pragma once

//! Computes a prng in the [0,1] range.
double rngp( void );

//! Computes a prng in the [-1,1] range.
double rngb( void );

//! Computes a prng in the [begin,end] range.
double rngrange( double begin, double end );
