#pragma once

class Point2D
{
public:
	Point2D();
	Point2D( unsigned int x, unsigned int y );

	unsigned int get_x() const;
	unsigned int get_y() const;
	
	void set_x(unsigned int x);
	void set_y(unsigned int y);
	
	void draw() const;
	
private:
	unsigned int x;
	unsigned int y;
};