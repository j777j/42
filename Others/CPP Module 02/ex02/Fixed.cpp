#include "Fixed.hpp"

Fixed::Fixed( void ) : _value( 0 ) {
	return;
}

Fixed::Fixed( int const n ) {
	this->_value = n << _fractionalBits;
	return;
}

Fixed::Fixed( float const n ) {
	this->_value = roundf( n * ( 1 << _fractionalBits ) );
	return;
}

Fixed::Fixed( Fixed const & src ) {
	*this = src;
	return;
}

Fixed::~Fixed( void ) {
	return;
}

Fixed &	Fixed::operator=( Fixed const & rhs ) {
	if ( this != &rhs ) {
		this->_value = rhs.getRawBits();
	}
	return *this;
}

bool	Fixed::operator>( Fixed const & rhs ) const {
	return this->_value > rhs.getRawBits();
}

bool	Fixed::operator<( Fixed const & rhs ) const {
	return this->_value < rhs.getRawBits();
}

bool	Fixed::operator>=( Fixed const & rhs ) const {
	return this->_value >= rhs.getRawBits();
}

bool	Fixed::operator<=( Fixed const & rhs ) const {
	return this->_value <= rhs.getRawBits();
}

bool	Fixed::operator==( Fixed const & rhs ) const {
	return this->_value == rhs.getRawBits();
}

bool	Fixed::operator!=( Fixed const & rhs ) const {
	return this->_value != rhs.getRawBits();
}

Fixed	Fixed::operator+( Fixed const & rhs ) const {
	return Fixed( this->toFloat() + rhs.toFloat() );
}

Fixed	Fixed::operator-( Fixed const & rhs ) const {
	return Fixed( this->toFloat() - rhs.toFloat() );
}

Fixed	Fixed::operator*( Fixed const & rhs ) const {
	return Fixed( this->toFloat() * rhs.toFloat() );
}

Fixed	Fixed::operator/( Fixed const & rhs ) const {
	return Fixed( this->toFloat() / rhs.toFloat() );
}

Fixed &	Fixed::operator++( void ) {
	this->_value++;
	return *this;
}

Fixed	Fixed::operator++( int ) {
	Fixed	tmp( *this );
	operator++();
	return tmp;
}

Fixed &	Fixed::operator--( void ) {
	this->_value--;
	return *this;
}

Fixed	Fixed::operator--( int ) {
	Fixed	tmp( *this );
	operator--();
	return tmp;
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

Fixed &	Fixed::min( Fixed & a, Fixed & b ) {
	if ( a < b ) {
		return a;
	}
	return b;
}

Fixed const &	Fixed::min( Fixed const & a, Fixed const & b ) {
	if ( a < b ) {
		return a;
	}
	return b;
}

Fixed &	Fixed::max( Fixed & a, Fixed & b ) {
	if ( a > b ) {
		return a;
	}
	return b;
}

Fixed const &	Fixed::max( Fixed const & a, Fixed const & b ) {
	if ( a > b ) {
		return a;
	}
	return b;
}

std::ostream &	operator<<( std::ostream & o, Fixed const & rhs ) {
	o << rhs.toFloat();
	return o;
}