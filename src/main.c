#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* GetTimeStr( void ) {
    static char str[256];
    time_t t = time( NULL );
    struct tm * timeptr = localtime( &t );
    
    strftime( str, 256, "%F %T", timeptr );
    
    return str;
}

void PrintHelp( void ) {
    printf(  "Valid options:\n"
            "  -m [number]       Set size of memory allocation for scanning, in GiB (default 8)\n"
            "  -n [filename]     Set filename for logging (default ./particles.log)"
            "  -v                Set verbose mode\n" 
            "  -h                Show help\n" );
}

void LogHit( char* logName ) {
    char* t = GetTimeStr();
    FILE* hitLog = fopen( logName, "a" );

    fseek( hitLog, 0, SEEK_END );
    fwrite( t, 1, strlen( t ), hitLog );
    fwrite( "\n", 1, strlen( "\n" ), hitLog );
    fclose( hitLog );
}

int main( int argc, char** argv ) {
    unsigned long long int ramGb = 8;
    unsigned long long int ramSize;
    unsigned long long int * mem;
    unsigned long long int i, scancount = 1;
    unsigned long long int scanPattern = 1;
    unsigned long long int lastScanPattern = 0;
    char logName[256] = "./particles.log";
    int verbose = 0;
    clock_t scanStart;

    for ( i = 1; i < argc; i++ ) {
        if ( !strcmp( argv[i], "-h" ) ) {
            PrintHelp();
            exit( 0 );
        }
        if ( !strcmp( argv[i], "-v" ) ) {
            printf( "Verbose mode enabled\n" );
            verbose = 1;
            continue;
        }    
        if ( !strcmp( argv[i], "-m" ) ) {
            if ( argc < i + 1 ) {
                printf( "Missing argument for option -m" );
                PrintHelp();
                exit( 1 );
            }
            sscanf( argv[++i], "%llu", &ramGb );
            continue;
        }
        if ( !strcmp( argv[i], "-n" ) ) {
            if ( argc < i + 1 ) {
                printf( "Missing argument for option -m" );
                PrintHelp();
                exit( 1 );
            }
            sscanf( argv[++i], "%s", logName );
            continue;
        }
    }

    printf( "[%s] Initializing particle detector with %lliGiB of RAM\n", GetTimeStr(), ramGb );
    ramSize = 1024ll * 1024ll * 1024ll * ramGb;
    printf( "[%s] Logging to %s\n", GetTimeStr(), logName );

    mem = calloc( 1, ramSize );

    printf( "[%s] Beginning scanning\n", GetTimeStr() );

    while ( 1 ) {
        if ( verbose )
            printf( "[%s] Start scan %lli\n", GetTimeStr(), scancount++ );
        scanStart = clock();
        for ( i = 0; i < ( ramSize / sizeof( long long int ) ); i++ ) {
            if ( mem[i] != lastScanPattern ) {
                printf( "[%s] Ouch! I got hit by a particle!\n\t\t> expected lli#%lli to be %lli\n"
                                                             "\t\t>                     was %lli\n", GetTimeStr(), i, lastScanPattern, mem[i] );
                LogHit( logName );
            }
            mem[i] = scanPattern;
        }
        lastScanPattern = scanPattern++;
        if ( verbose )
            printf( "[%s] Scan finished (took %1.03f seconds)\n", GetTimeStr(), ( (float)( ( clock() - scanStart ) * 1000 / CLOCKS_PER_SEC ) ) / 1000.f );
    }
}