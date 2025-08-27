#include "Fixed.hpp"

Fixed::Fixed( void ) : _value( 0 ) {
	std::cout << "Default constructor called" << std::endl;
	return;
}

Fixed::Fixed( int const n ) {
	std::cout << "Int constructor called" << std::endl;
	this->_value = n << _fractionalBits;
	return;
}

Fixed::Fixed( float const n ) {
	std::cout << "Float constructor called" << std::endl;
	this->_value = roundf( n * ( 1 << _fractionalBits ) );
	return;
}

Fixed::Fixed( Fixed const & src ) {
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
	return;
}

Fixed::~Fixed( void ) {
	std::cout << "Destructor called" << std::endl;
	return;
}

Fixed &	Fixed::operator=( Fixed const & rhs ) {
	std::cout << "Copy assignment operator called" << std::endl;
	if ( this != &rhs ) {
		this->_value = rhs.getRawBits();
	}
	return *this;
}

int		Fixed::getRawBits( void ) const {
	return this->_value;
}

void	Fixed::setRawBits( int const raw ) {
	this->_value = raw;
	return;
}

float	Fixed::toFloat( void ) const {
	return (float)this->_value / ( 1 << _fractionalBits );
}

int		Fixed::toInt( void ) const {
	return this->_value >> _fractionalBits;
}

std::ostream &	operator<<( std::ostream & o, Fixed const & rhs ) {
	o << rhs.toFloat();
	return o;
}