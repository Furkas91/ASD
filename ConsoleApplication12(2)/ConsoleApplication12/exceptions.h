#pragma once
#include <exception>;

using std::exception;

struct PointOutOfScreenException : public exception
{
	const char* what() const throw()
	{
		return "X and Y of point was out of screen";
	}
};

struct XOfPointOutOfScreenException : public exception
{
	const char* what() const throw()
	{
		return "X of point was out of screen";
	}
};

struct YOfPointOutOfScreenException : public exception
{
	const char* what() const throw()
	{
		return "Y of point was out of screen";
	}
};

struct ShapeOutOfScreenException : public exception
{
	const char* what() const throw()
	{
		return "Shape was out of screen";
	}
};

struct WrongShapeException : public exception
{
	const char* what() const throw()
	{
		return "Shape was wrong";
	}
};