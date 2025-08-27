#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed {

public:

	Fixed( void );
	Fixed( int const n );
	Fixed( float const n );
	Fixed( Fixed const & src );
	~Fixed( void );

	Fixed &	operator=( Fixed const & rhs );

	bool	operator>( Fixed const & rhs ) const;
	bool	operator<( Fixed const & rhs ) const;
	bool	operator>=( Fixed const & rhs ) const;
	bool	operator<=( Fixed const & rhs ) const;
	bool	operator==( Fixed const & rhs ) const;
	bool	operator!=( Fixed const & rhs ) const;

	Fixed	operator+( Fixed const & rhs ) const;
	Fixed	operator-( Fixed const & rhs ) const;
	Fixed	operator*( Fixed const & rhs ) const;
	Fixed	operator/( Fixed const & rhs ) const;

	Fixed &	operator++( void );
	Fixed	operator++( int );
	Fixed &	operator--( void );
	Fixed	operator--( int );

	int		getRawBits( void ) const;
	void	setRawBits( int const raw );

	float	toFloat( void ) const;
	int		toInt( void ) const;

	static Fixed &			min( Fixed & a, Fixed & b );
	static Fixed const &	min( Fixed const & a, Fixed const & b );
	static Fixed &			max( Fixed & a, Fixed & b );
	static Fixed const &	max( Fixed const & a, Fixed const & b );

private:

	int					_value;
	static const int	_fractionalBits = 8;

};

std::ostream &	operator<<( std::ostream & o, Fixed const & rhs );

#endif