#pragma once

class Valid
{
public:
	Valid()
		: isValid(false)
	{
	}
	void set(bool v)
	{
		isValid = v;
	}
	operator bool() const
	{
		return isValid;
	}
	bool operator!()
	{
		return !isValid;
	}
private:
	bool isValid;
};