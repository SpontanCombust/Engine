#pragma once

class Point2D
{
public:
	Point2D();
	Point2D( int x, int y );

	int get_x() const;
	int get_y() const;
	
	void set_x(int x);
	void set_y(int y);
	
	void draw() const;
	
private:
	int x;
	int y;
};


typedef Point2D Size2D;