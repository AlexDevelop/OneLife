#include "lineardb3.h"
#include "dbCommon.h"

#include <stdio.h>


int valueFunction( int inI ) {
    return inI + 1000;
    }


int main() {
    
    LINEARDB3 db;
    

    int result = LINEARDB3_open(
        &db,
        "sizeTest_ldb3.db",
        0,
        80000,
        4,
        4 );

    if( result != 0 ) {
        printf( "Error creating DB.\n" );
        return 1;
        }
    
    int numInserts = 268000000;
    
    unsigned char key[4];
    unsigned char value[4];
    

    for( int i=0; i<numInserts; i++ ) {
        if( i % 1000000 == 0 ) {
            printf( "Inserted %d (file size %d MiB)\n", i,
                    ( i * 4 ) / (1024 * 1024 ) );
            }
        
        intToValue( i, key );
        intToValue( valueFunction( i ), value );
        

        LINEARDB3_put( &db, key, value );
        }
    

    for( int i=0; i<numInserts; i++ ) {
        
        intToValue( i, key );
        
        LINEARDB3_get( &db, key, value );
        
        int v = valueToInt( value );
        
        if( v != valueFunction( i ) ) {
            printf( "Value mismatch:  expecting %d, got %d\n",
                    valueFunction( i ), v );
            }
        }
    


    
    LINEARDB3_close( &db );
    }
