#include <algorithm>
#include <cmath>

using namespace std;

const long double EPS = 1e-5;
const int MAXPOINTS = 1005;

struct point {
    long double x, y;
} points[MAXPOINTS], hull[MAXPOINTS];
int npoints, nhull;

long double signedArea( const point & a, const point & b, const point & c ) {
    return a.x * b.y - b.x * a.y + b.x * c.y - c.x * b.y + c.x * a.y - a.x * c.y;
}

long double sqrdist( const point & a, const point & b ) {
    return ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
}

bool bySignedArea( const point & a, const point & b ) {
    long double sa = signedArea( points[0], a, b );

    return ( fabs( sa ) < EPS ) ?
        ( sqrdist( points[0], a ) < sqrdist( points[0], b ) )
        : ( sa  > 0 );
}

void findminpoint(  ) {
    long double minx = points[0].x, miny = points[0].y;
    int currentmin = 0;

    for( int i = 1; i < npoints; ++i ) {
        if( points[i].y < miny || ( points[i].y == miny && points[i].x < minx ) ) {
            minx = points[i].x;
            miny = points[i].y;
            currentmin = i;
        }
    }

    // exchange min point with point[0]
    swap( points[currentmin], points[0] );
}

void convexhull(  )
{
    findminpoint(  );
    sort( points + 1, points + npoints, bySignedArea );

    hull[0] = points[0];
    nhull = 1;

    for( int i = 1; i < npoints; ++i ) {
        // hier anpassen, wenn kollineare punkte mit aufgenommen werden sollen
        while( nhull > 1 && signedArea( hull[nhull - 2], hull[nhull - 1], points[i] ) < EPS ) {
            --nhull;
        }

        hull[nhull++] = points[i];
    }
}
