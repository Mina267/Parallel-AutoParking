
#ifndef UTILS_H_
#define UTILS_H_

#define WRITE_BIT(REG, BIT, VALUE)		REG = (((REG) & (~(1 << (BIT)))) | ((VALUE) << (BIT)))
#define TOG_BIT(REG, BIT)				REG = ((REG) ^ (1 << BIT))
#define SET_BIT(REG, BIT)				REG = ((REG) | (1 << (BIT)))
#define CLR_BIT(REG, BIT)				REG =  ((REG) & (~(1 << (BIT))))
#define READ_BIT(REG, BIT)				(((REG) >> (BIT)) & (1))
#define CLR_REG(REG)					(REG = REG ^ REG)
#define TOGLE_REG(REG)					(REG = REG ^ 0xFF)


#endif /* UTILS_H_ */