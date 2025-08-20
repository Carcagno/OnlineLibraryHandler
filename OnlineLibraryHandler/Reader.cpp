#include "Reader.h"

Reader::Reader(const std::string& readerName, const char readerType) :
	IUser(readerName, readerType),
	m_borrowedBookCount{0} {

}