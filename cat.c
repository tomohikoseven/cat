#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define BUFFER_SIZE 2048

static          void do_cat(    const char *path    );
static          void die(       const char *s       );
static          void usage(     int argc,
                                char *argv[]        );
static          void _cat(      int argc,
                                char *argv[]        );
static          void _readWrite(int fd,
                                const char *path    );
static          void _write(    unsigned char *buf,
                                int n,
                                const char *path    );

static inline   void _close(    int fd,
                                const char *path    );
static inline   int  _open(     const char *path,
                                int mode            );

static void
usage( int argc, char *argv[] )
{
    if( argc < 2 )
    {
        fprintf( stderr, "%s: file name not given\n", argv[0] );
        exit(1);
    }
}

static void
_cat( int argc, char *argv[] )
{
    int _i = 0;

    for( _i = 0; _i < argc; _i++ )
    {
        do_cat( argv[_i] );
    }
}

static inline int
_open(  const char  *path,
        int         mode    )
{
    int fd = 0;

    fd = open( path, O_RDONLY );

    if( fd < 0 )
    {
        die( path );
    }

    return fd;
}

static inline void
_close( int fd, const char *path )
{
    if( close( fd ) < 0 )
    {
        die( path );
    }
}

static void
_write( unsigned char *buf,
        int n,
        const char *path    )
{
    int _ret    = 0;

    _ret = write( STDOUT_FILENO, buf, n );
    if( _ret < 0 )
    {
        die( path );
    }
}

static void
_readWrite( int fd,
            const char *path )
{
    unsigned char buf[BUFFER_SIZE];
    int n   = 0;

    memset( buf, 0x00, sizeof( buf ) );

    for( ;n = read( fd, buf, sizeof( buf ) ); )
    {
        if( n == 0 )
        {
            break;
        }
        if( n < 0 )
        {
            die( path );
        }
        _write( buf, n, path );
    }
}

static void
do_cat( const char *path )
{
    int fd  = 0;

    fd = _open( path, O_RDONLY );

    _readWrite( fd, path );

    _close( fd, path );
}

static void
die( const char *s )
{
    perror( s );
    exit(1);
}

/*!
    @brief  main本体.
    @param  [in]    argc
    @param  [in]    *argv[]
    @return 成否を返す.
    @retval 0   正常終了.
    @retval 1   異常終了.
 */
int
main(   int     argc,
        char    *argv[] )
{

    usage( argc, argv );

    // cat 本体
    _cat( argc, argv );

    return 0;
}
