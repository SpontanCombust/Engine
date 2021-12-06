#pragma once

#include "../GameObjects/DrawableObject.hpp"
#include "../GameObjects/TransformableObject.hpp"

class Point2D : virtual public DrawableObject, virtual public TransformableObject
{
public:
	Point2D();
	Point2D( int x, int y );

	int get_x() const;
	int get_y() const;
	
	void set_x(int x);
	void set_y(int y);
	
	void draw() override;

	void translate( float transl_x, float transl_y ) override;
	void scale( float scale_x, float scale_y ) override;
	void rotate( float angle_deg ) override;
	
private:
	int x;
	int y;
};


typedef Point2D Size2D;