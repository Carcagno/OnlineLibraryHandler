#pragma once

#include "IUser.h"

class Administrator : public IUser {
protected:

public:
	//CTOR
	Administrator(const std::string& AdministratorName);

	//DTOR
	~Administrator() override = default;

	//SETTERS

	//GETTERS
	
	//MISC
	void cleanUserForDelete() override;
	void addUser();

 };