/*
 * bit_math.h
 *
 * Created: 23/5/2023 7:34:29 AM
 * Updated: 17/8/2023 2:28:00 PM
*  Author: hossam Elwahsh - https://github.com/HossamElwahsh
 */


#ifndef bit_math_H_
#define bit_math_H_

#define SET_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER | ( 1UL << BIT_NUMBER ) )
#define CLR_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER & ~( 1UL << BIT_NUMBER ) )
#define TOGGLE_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER ^ ( 1UL << BIT_NUMBER ) )
#define GET_BIT( REGISTER, BIT_NUMBER )		( ( REGISTER & ( 1UL << BIT_NUMBER ) ) >> BIT_NUMBER ) /*  ( ( REGISTER >> BIT_NUMBER ) & 1UL ) */

#define BIT_IS_SET(REG,BIT) (REG & (1 << BIT))

#define BIT_IS_CLEAR(REG,BIT) (! (REG & (1<<BIT)))

#define WRITE_BIT(REGISTER,BIT_NUMBER, BIT_VAL) ((BIT_VAL) ? ((REGISTER) |= (1UL << (BIT_NUMBER))) : ((REGISTER) &= ~(1UL << (BIT_NUMBER))))

#endif /* bit_math_H_ */