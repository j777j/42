#include "Point.hpp"

static Fixed	abs( Fixed x ) {
	if ( x < 0 ) {
		return x * -1;
	}
	return x;
}

static Fixed	area( Point const a, Point const b, Point const c ) {
	return abs( ( a.getX() * ( b.getY() - c.getY() ) + b.getX() * ( c.getY() - a.getY() ) + c.getX() * ( a.getY() - b.getY() ) ) / 2 );
}

bool	bsp( Point const a, Point const b, Point const c, Point const point ) {

	Fixed	abcArea = area( a, b, c );
	Fixed	pabArea = area( point, a, b );
	Fixed	pbcArea = area( point, b, c );
	Fixed	pcaArea = area( point, c, a );

	if ( pabArea == 0 || pbcArea == 0 || pcaArea == 0 ) {
		return false;
	}
	return abcArea == pabArea + pbcArea + pcaArea;
}