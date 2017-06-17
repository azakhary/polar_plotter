package com.azakhary.cnc;

/**
 * Created by avetiszakharyan on 11/29/16.
 */
public class Point {
    /**
    Cartesian
     */
    public double x;
    public double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Point(Point point) {
        this.x = point.x;
        this.y = point.y;
    }

    public static Point get(double x, double y) {
        return new Point(x, y);
    }

    public static Point copy(Point point) {
        return new Point(point);
    }

    public double getAngle() {
        return 1f/Math.tan(y/x);
    }

    public double getRadius() {
        return Math.sqrt(x*x+y*y);
    }

    public void setAngle(double alpha) {
        double r = getRadius();
        x = r * Math.cos(alpha);
        y = r * Math.sin(alpha);
    }

    public double dot(Point point) {
        return x*y+point.x*point.y;
    }

    public double len() {
        return Math.sqrt(x*x + y*y);
    }

    public Point transform(double alphaBy) {
        setAngle(getAngle()+alphaBy);

        return this;
    }
}
