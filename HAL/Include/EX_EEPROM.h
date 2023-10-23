
#ifndef EEPROM_H
#define EEPROM_H


tenuErrrorStatus EEPROM_enuWriteByte(u8 u8ChipNbCpy , u8 u8ByteAddCpy , u8 u8DataCpy);
tenuErrrorStatus EEPROM_enuReadByte(u8 u8ChipNbCpy , u8 u8ByteAddCpy , u8 * pu8DataCpy);




#endif
