

import javax.swing.*;
import java.awt.*;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

class Point {
    float x;
    float y;

    public Point(float x, float y) {
        this.x = x;
        this.y = y;
    }
}

class Polygon {
    Point[] points;

    public Polygon(Point[] points) {
        this.points = points;
        for (int i = 0; i < points.length; i++) {
            Point a = points[i];
            Point b = points[(i + 1) % points.length];
            if (Float.compare(a.x, b.x) != 0 && Float.compare(a.y, b.y) != 0) {
                System.out.println("not orthogonal");
            }
        }
    }

    boolean pointOnOrthogonalLine(Point p, Point a, Point b) {
        if (Float.compare(a.x, b.x) == 0) {
            if (Float.compare(a.x, p.x) != 0 && Float.compare(b.x, p.x) != 0)
                return false;
            if (p.y <= Math.max(a.y, b.y) && p.y >= Math.min(a.y, b.y))
                return true;
        } else if (Float.compare(a.y, b.y) == 0) {
            if (Float.compare(a.y, p.y) != 0 && Float.compare(b.y, p.y) != 0)
                return false;
            if (a.x <= Math.max(a.x, b.x) && a.x >= Math.min(a.x, b.y))
                return false;
        }
        return false;
    }

    boolean pointTest(Point p) {
        if (points.length < 3)
            return false;
        int rayCount = 0;
        for (int i = 0; i < points.length; i++) {
            Point a = points[i];
            Point b = points[(i + 1) % points.length];
            if (pointOnOrthogonalLine(p, a, b)) {
                System.out.println("on poly");
                return false;
            }
            if (Float.compare(a.x, b.x) == 0) {
                if (p.x > a.x && p.x > b.x && p.y <= Math.max(a.y, b.y) && p.y > Math.min(a.y, b.y))
                    rayCount += 1;
            }
        }
        return (rayCount % 2 == 1);
    }
}

class Rectangle {
    Point min;
    Point max;

    public Rectangle(Point min, Point max) {
        this.min = min;
        this.max = max;
    }

    public Rectangle() {
        min = new Point(0, 0);
        max = new Point(0, 0);
    }

    public static Rectangle getAABB(Point[] points) {
        if (points.length == 0)
            return null;
        Point min = new Point(points[0].x, points[0].y);
        Point max = new Point(points[0].x, points[0].y);
        for (int i = 0; i < points.length; i++) {
            if (points[i].x < min.x)
                min.x = points[i].x;
            if (points[i].y < min.y)
                min.y = points[i].y;
            if (points[i].x > max.x)
                max.x = points[i].x;
            if (points[i].y > max.y)
                max.y = points[i].y;
        }
        return new Rectangle(min, max);
    }

    boolean pointTest(Point p) {
        if (p.x > min.x && p.y > min.y && p.x < max.x && p.y < max.y)
            return true;
        return false;
    }
}

class Node {
    Node left;
    Node right;
    float split;
    boolean xAxis;
    int id;
    static int idGen = 0;

    public Node() {
        left = null;
        right = null;
    }

    public Node(boolean x, float spl) {
        split = spl;
        xAxis = x;
    }

    public static int  getId(){
        return idGen++;
    }

    public static Node getNode(Point[] points, Rectangle rect, boolean xAxis) {

        if (points.length > 1) {
            Point splitPoint = (points.length % 2 == 0) ? points[points.length / 2 - 1] : points[points.length / 2];
            float split = xAxis ? splitPoint.x : splitPoint.y;
            RectangleNode rNode = new RectangleNode(rect, split, xAxis);
            Main.sort(xAxis, points);
            Rectangle lRect, rRect;
            if (xAxis) {
                lRect = new Rectangle(rect.min, new Point(split, rect.max.y));
                rRect = new Rectangle(new Point(split, rect.min.y), rect.max);
            } else {
                lRect = new Rectangle(rect.min, new Point(rect.max.x, split));
                rRect = new Rectangle(new Point(rect.min.x, split), rect.max);
            }
            Point[] lPts = new Point[points.length - (points.length / 2)];
            Point[] rPts = new Point[points.length - lPts.length];

            for (int i = 0; i < lPts.length; i++) {
                lPts[i] = points[i];
            }
            for (int i = 0; i < rPts.length; i++) {
                rPts[i] = points[i + lPts.length];
            }
            rNode.left = getNode(lPts, lRect, !xAxis);
            rNode.right = getNode(rPts, rRect, !xAxis);
            return rNode;
        } else if (points.length == 1) {
            return new PointNode(points[0], xAxis);
        } else
            return null;
    }
}

class PointNode extends Node {
    Point point;

    public PointNode(Point point, boolean x) {
        id = getId();
        this.point = point;
        super.xAxis = x;
        if (xAxis)
            super.split = point.x;
        else
            super.split = point.y;
    }
}

class RectangleNode extends Node {
    Rectangle rectangle;

    public RectangleNode(Rectangle rectangle, float spl, boolean x) {
        id = getId();
        super.xAxis = x;
        super.split = spl;
        this.rectangle = rectangle;
    }
}


public class Main extends Canvas {

    public static Node node = null;
    public static ArrayList<Point> included;
    public static Rectangle rect;
    public static Polygon poly;


    public static Point[] getPoints(Scanner scanner) {
        int n = scanner.nextInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            points[i] = new Point(scanner.nextFloat(), scanner.nextFloat());
        }
        return points;
    }

    public static Polygon getPolygon(Scanner scanner) {
        int n = scanner.nextInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            points[i] = new Point(scanner.nextFloat(), scanner.nextFloat());
        }
        return new Polygon(points);
    }

    public static Rectangle getRectangle(Scanner scanner) {
        Point p1 = new Point(scanner.nextFloat(), scanner.nextFloat());
        Point p2 = new Point(scanner.nextFloat(), scanner.nextFloat());
        if (p1.x < p2.x)
            return new Rectangle(p1, p2);
        else
            return new Rectangle(p2, p1);
    }

    public static void sort(boolean xAxis, Point[] points) {
        boolean sorted = false;
        while (!sorted) {
            sorted = true;
            for (int i = 1; i < points.length; i++) {
                boolean swap = false;
                if (xAxis && points[i - 1].x > points[i].x)
                    swap = true;
                if (!xAxis && points[i - 1].y > points[i].y)
                    swap = true;
                if (swap) {
                    sorted = false;
                    Point tmp = points[i];
                    points[i] = points[i - 1];
                    points[i - 1] = tmp;
                }
            }
        }
    }

    public static void print(Node node, int level) {
        if (node == null)
            return;

        for (int i = 0; i < level; i++) {
            System.out.print("    ");
        }
        if (node instanceof PointNode) {
            PointNode pn = (PointNode) node;
            System.out.println("point" + pn.point.x + " " + pn.point.y + " split" + pn.split + " " + pn.xAxis);
        } else if (node instanceof RectangleNode) {
            RectangleNode r = (RectangleNode) node;
            System.out.println("rectangle" + r.rectangle.min.x + " " + r.rectangle.min.y + " " + r.rectangle.max.x + " " + r.rectangle.max.y + "split:" + r.split + " " + r.xAxis);
        }
        print(node.left, level + 1);
        print(node.right, level + 1);
    }

    public void paint(Graphics g) {
        Random r = new Random();
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, 1600, 900);
        paintTreeVert(node, g, r);
        paintIncludedVert(included, g);
        paintRectangle(rect);
        paintPolygon(poly);
    }

    public static int convertX(float f) {
        return (int) (f * 100);
    }

    public static int convertY(float f) {
        return 900-(int) (f * 100);
    }

    static void findPoints(Node node, Rectangle a, Polygon b, ArrayList<Point> list) {
        if (node == null)
            return;
        if (node instanceof PointNode) {
            Point p = ((PointNode) node).point;
            if (a.pointTest(p) && b.pointTest(p)) {
                list.add(p);
            }
        } else {
            findPoints(node.left, a, b, list);
            findPoints(node.right, a, b, list);
        }
    }

    void paintTreeVert(Node node, Graphics g, Random rr) {
        float scale = 100;
        if (node == null)
            return;
        g.setColor(Color.BLACK);
        if (node instanceof PointNode) {
            PointNode n = (PointNode) node;
            g.fillOval(convertX(n.point.x) - 5, convertY(n.point.y) - 5, 10, 10);
        }

        paintTreeVert(node.left, g, rr);
        paintTreeVert(node.right, g, rr);
    }

    void paintIncludedVert(ArrayList<Point> list, Graphics g) {
        g.setColor(Color.RED);
        for (int i = 0; i < list.size(); i++) {
            Point p = list.get(i);
            g.fillOval(convertX(p.x) - 5, convertY(p.y) - 5, 10, 10);
        }
    }

    void paintRectangle(Rectangle r) {
        getGraphics().drawRect(convertX(r.min.x), convertY(r.max.y), convertX(r.max.x) - convertX(r.min.x), convertY(r.min.y) - convertY(r.max.y));
    }

    void paintPolygon(Polygon poly) {
        int[] x = new int[poly.points.length];
        int[] y = new int[poly.points.length];
        for (int i = 0; i < poly.points.length; i++) {
            x[i] = convertX(poly.points[i].x);
            y[i] = convertY(poly.points[i].y);
        }
        getGraphics().drawPolygon(x,y,poly.points.length);
    }

    static void printNodesToFile(Node n, BufferedWriter writer) throws Exception{
        if (n == null)
            return;
        if (n instanceof RectangleNode){
            writer.write(""+n.id+" [ label = \"line\" ];\n" );
            printNodesToFile(n.left,writer);
            printNodesToFile(n.right,writer);
        }else if (n instanceof PointNode){
            writer.write(""+n.id+" [ label = \"("+((PointNode) n).point.x +", "+((PointNode) n).point.y+")\" ];\n");
        }
    }

    static void printNodeConnectionToFile(Node n,BufferedWriter writer) throws Exception{
        if (n == null)
            return;
        if (n instanceof RectangleNode){
            if (n.left != null && n.right != null){
                writer.write(n.id+" -> { "+n.left.id +" "+n.right.id+" };\n");
                printNodeConnectionToFile(n.left,writer);
                printNodeConnectionToFile(n.right,writer);
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Point[] pts = getPoints(scanner);
        rect = getRectangle(scanner);
        poly = getPolygon(scanner);
        scanner.close();
        node = Node.getNode(pts, rect, true);
        included = new ArrayList<Point>();
        findPoints(node, rect, poly, included);
        System.out.println(included.size());

        for (int i = 0;i < included.size();i++){
            Point p = included.get(i);
            System.out.println("point:"+p.x+","+p.y);
        }
        try {
            BufferedWriter bf = new BufferedWriter(new FileWriter("graph.dot"));
            bf.write("digraph BST {\n");
            printNodesToFile(node,bf);
            printNodeConnectionToFile(node,bf);
            bf.write("}");
            bf.close();
        }catch (Exception e){
            System.out.println("file write error");
        }

        JFrame frame = new JFrame("My Drawing");
        Canvas canvas = new Main();
        canvas.setSize(1600, 900);
        frame.add(canvas);
        frame.pack();
        frame.setVisible(true);
    }
}
