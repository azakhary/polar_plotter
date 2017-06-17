package com.azakhary.cnc;

/**
 * Created by avetiszakharyan on 11/29/16.
 */
public class PolarPlotter {

    private double turnTableRotation = 0;

    private double toneArmRotation = 0;

    private double R = 10;

    private Point currentPoint;


    public PolarPlotter() {
        currentPoint = Point.get(0, 0);
    }

    public void moveTo(float xTo, float yTo) {

        Point originalA = Point.copy(currentPoint);
        Point currA = Point.copy(originalA);

        Point originalB = Point.get(xTo, yTo).transform(turnTableRotation);
        Point currB = Point.copy(originalB);

        double lenB = originalB.len();
        double bTargetX = (lenB * lenB) / (2 * R);
        double bTargetY = lenB * Math.sqrt(1 - (bTargetX*bTargetX));
        Point targetB = Point.get(bTargetX, bTargetY);
        double deltaAngle = targetB.getAngle();
        double currAngle = currentPoint.getAngle();

        double angleStep = 1;

        for(double i = currAngle; i < currAngle+deltaAngle; i+=angleStep) {
            moveTurntableBy(angleStep);
            currentPoint.transform(angleStep);

            // now when this is down update A and B
            currA.transform(angleStep);
            currB.transform(angleStep);

            double alpha = getAlphaFromAB(currA, currB); // This is the NEW angle of tonearm calculated from A & B
            double deltaTonearm = alpha - toneArmRotation;
            moveArmBy(deltaTonearm);
            toneArmRotation += deltaTonearm;
        }

    }

    public void moveArmBy(double a) {

    }

    public void moveTurntableBy(double a) {

    }

    public double getAlphaFromAB(Point currA, Point currB) {
        double underPart = Math.sqrt((currA.x - currB.x) * (currA.x - currB.x) + (currA.y - currB.y) * (currA.y - currB.y));
        Point normal = Point.get((currA.y - currB.y)/underPart, (currB.x - currA.x)/underPart);

        double d = normal.dot(currA); //mm I guess?

        double cosAlpha = d/R + Math.cos(normal.getAngle());
        double alpha = normal.getAngle() - Math.acos(cosAlpha); // This is the angle of tonearm

        return alpha;
    }
}
