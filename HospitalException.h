#ifndef HOSPITALEXCEPTION_H
#define HOSPITALEXCEPTION_H
#include "Utils.h"
class HospitalException{
protected: char message[200];
public: HospitalException(const char* m="Hospital exception")

{Utils::copyArr(message,m,200);} 
virtual const char* what() const{return message;} 
virtual ~HospitalException(){} };
class FileNotFoundException: public HospitalException{ public: FileNotFoundException(const char* m="Required file could not be opened."):HospitalException(m){} };
class InsufficientFundsException: public HospitalException{ public: InsufficientFundsException(const char* m="Insufficient balance."):HospitalException(m){} };
class InvalidInputException: public HospitalException{ public: InvalidInputException(const char* m="Invalid input."):HospitalException(m){} };
class SlotUnavailableException: public HospitalException{ public: SlotUnavailableException(const char* m="Selected time slot is already booked."):HospitalException(m){} };
#endif
