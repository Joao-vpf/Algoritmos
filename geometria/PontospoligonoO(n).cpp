struct Point {
    int x, y;
};

bool pointOnEdge(const Point& p,const Point& a, const Point& b) 
{
    if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x) || p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) 
	{
        // Point is outside bounding box of line segment
        return false;
    }
    // Calculate cross product to determine if point lies on line segment
    int cross = (p.y - a.y) * (b.x - a.x) - (p.x - a.x) * (b.y - a.y);
    if (cross != 0) 
	{
        return false;
    }
    // Check if point lies on line segment
    int dot = (p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y);
    if (dot < 0 || dot > (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)) 
	{
        return false;
    }
    return true;
}

bool isedge(const Point& p, const vector<Point>& poly)
{
    int n = poly.size();
    for (int i = 0; i < n; i++) 
	{
        if (pointOnEdge(p, poly[i], poly[(i + 1) % n])) 
		{
            return true;
        }
    }
    return false;
}

bool vertice(const Point& p, const vector<Point>& polygon)
{
	for(auto e : polygon)
	{
		if(p.x==e.x && p.y==e.y)
		{
			return true;
		}
	}
	return false;
}

// Function to check if a point is inside a polygon
bool isinsidepolygon(const Point& p, const vector<Point>& polygon) 
{
    int n = polygon.size();
    int count = 0;

	if(vertice(p, polygon)) return true;
	
    // Count the number of times the ray intersects with the polygon edges
    for (int i = 0; i < n; i++) 
    {
        int j = (i + 1) % n;
        if ((polygon[i].y > p.y) != (polygon[j].y > p.y)) 
        {
            double xIntersection = (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x;
            if (xIntersection > p.x) 
            {
                if (pointOnEdge(p, polygon[i], polygon[j])) 
                {
                    return true;
                }
                count++;
            }
        }
	}
    // If the number of intersections is odd, the point is inside the polygon
    return (count % 2 == 1);
}
