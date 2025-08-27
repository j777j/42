#include "Point.hpp"

int	main( void ) {

	Point	a( 0.0f, 0.0f );
	Point	b( 10.0f, 0.0f );
	Point	c( 5.0f, 10.0f );

	Point	p1( 5.0f, 5.0f );
	Point	p2( 10.0f, 5.0f );
	Point	p3( 0.0f, 0.0f );
	Point	p4( 5.0f, 0.0f );

	std::cout << "Point p1 is " << ( bsp( a, b, c, p1 ) ? "inside" : "outside" ) << " the triangle" << std::endl;
	std::cout << "Point p2 is " << ( bsp( a, b, c, p2 ) ? "inside" : "outside" ) << " the triangle" << std::endl;
	std::cout << "Point p3 is " << ( bsp( a, b, c, p3 ) ? "inside" : "outside" ) << " the triangle" << std::endl;
	std::cout << "Point p4 is " << ( bsp( a, b, c, p4 ) ? "inside" : "outside" ) << " the triangle" << std::endl;

	return 0;
}