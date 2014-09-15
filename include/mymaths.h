class Vector2
{
private:
	float x;
	float y;
public:
	Vector2();
	Vector2(float, float);
	void Set(float ax, float ay)
	{
		x = ax;
		y = ay;
	}
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
};

Vector2::Vector2(float ax, float ay)
{
	x = ax;
	y = ay;
}

class Point2D
{
private:
	float x;
	float y;
public:
	Point2D();
	Point2D(float, float);
	void Set(float ax, float ay)
	{
		x = ax;
		y = ay;
	}
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
};
Point2D::Point2D(float ax, float ay)
{
	x = ax;
	y = ay;
}

class Line2D
{
private:
	float X1;
	float Y1;
	float X2;
	float Y2;
public:
	void Set(float startx, float starty, float endx, float endy)
	{
		X1 = startx;
		Y1 = starty;
		X2 = endx;
		Y2 = endy;
	}
	Line2D();
	Line2D(Point2D, Point2D);
	void Set(Point2D a_point1, Point2D a_point2)
	{
		X1 = a_point1.GetX();
		Y1 = a_point1.GetY();
		X2 = a_point2.GetX();
		Y2 = a_point2.GetY();
	}
	float GetLength()
	{
		return (((X2 - X1) * (X2 - X1)) + ((Y2 - Y1) * (Y2 - Y1)));
	}
	float GetLengthX()
	{
		return (X2 - X1);
	}
	float GetLengthY()
	{
		return (Y2 - Y1);
	}
	Vector2 GetVector()
	{
		Vector2 v(GetLengthX(),GetLengthY());
		return v;
	}
};

Line2D::Line2D(Point2D a_point1, Point2D a_point2)
{
	X1 = a_point1.GetX();
	Y1 = a_point1.GetY();
	X2 = a_point2.GetX();
	Y2 = a_point2.GetY();
}


class Box2D
{
private:
	float X1;
	float Y1;
	float X2;
	float Y2;
public:
	Box2D(void);
	Box2D(Point2D, Point2D);
	Box2D(float, float, float, float);
	void Set(Point2D p1, Point2D p2)
	{
		X1 = p1.GetX();
		Y1 = p1.GetY();
		X2 = p2.GetX();
		Y2 = p2.GetY();
	}
	Point2D GetLeftBot()
	{
		Point2D p(X1,Y1);
		return p;
	}
	Point2D GetLeftTop()
	{
		Point2D p(X1, Y2);
		return p;
	}
	Point2D GetRightBot()
	{
		Point2D p(X2, Y1);
		return p;
	}
	Point2D GetRightTop()
	{
		Point2D p(X2, Y2);
		return p;
	}
	Line2D GetBotLine()
	{
		Line2D l(GetLeftBot(),GetRightBot());
		return l;
	}
	Line2D GetRightLine()
	{
		Line2D l(GetRightBot(), GetRightTop());
		return l;
	}
	Line2D GetTopLine()
	{
		Line2D l(GetRightTop(), GetLeftTop());
		return l;
	}
	Line2D GetLeftLine()
	{
		Line2D l(GetLeftTop(), GetLeftBot());
		return l;
	}
};

Box2D::Box2D(Point2D p1, Point2D p2)
{
	X1 = p1.GetX();
	Y1 = p1.GetY();
	X2 = p2.GetX();
	Y2 = p2.GetY();
}
Box2D::Box2D(float ax1, float ay1, float ax2, float ay2)
{
	X1 = ax1;
	Y1 = ay1;
	X2 = ax2;
	Y2 = ay2;
}

float Dot(Vector2 a, Vector2 b)
{
	return ((a.GetX() * b.GetX()) + (a.GetY() * b.GetY()));
}

bool CheckPointBox(Point2D p, Box2D b)
{
	if (p.GetX() > b.GetLeftBot().GetX() && p.GetX() < b.GetRightTop().GetX() && p.GetY() > b.GetLeftBot().GetY() && p.GetY() < b.GetRightTop().GetY())
		return true;
	return false;
}

bool CheckLineLine(Line2D l1, Line2D l2)
{
	return false;											//DO THIS NEXT FOR REUSABILITY
}

bool CheckBoxBox(Box2D b1, Box2D b2)
{
	if (CheckPointBox(b1.GetLeftBot(), b2) || CheckPointBox(b1.GetRightBot(), b2) || CheckPointBox(b1.GetRightTop(), b2) || CheckPointBox(b1.GetLeftTop(), b2))
		return true;
	return false;
}