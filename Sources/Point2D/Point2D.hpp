class Point2D
{
public:
	unsigned get_x();
	unsigned get_y();
	
	void set_x(unsigned x);
	void set_y(unsigned y);
	
	void draw();
	
private:
	unsigned x;
	unsigned y;
};