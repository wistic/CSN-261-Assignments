
/**
* @file Prob2.java
* This Java file is a program used to demonstrate the utility of Segment Tree.
*
* @author Prathamesh Katkar
*
* @date 11/10/2019
*/

import java.io.*;
import java.lang.*;
import java.util.*;

/**
 * @brief This class represents a node of Segment Tree.
 * @date 11/10/2019
 */
class Node {
    public boolean isLeaf;
    public int min, max, sum;
    public int startIndex, endIndex;

    Node() {
    }

    Node(boolean isLeaf) {
        this.isLeaf = isLeaf;
    }
}

/**
 * This class represents tha Data Structure Segment Tree.
 * @date 11/10/2019
 */
class SegmentTree {
    public Node nodeArray[];
    public int no_of_nodes;

    SegmentTree() {
    }

    SegmentTree(int arr[], int n) {
        int temp = (int) (Math.ceil(Math.log(n) / Math.log(2)));
        int size = 2 * (int) (Math.pow(2, temp)) - 1;
        nodeArray = new Node[size];
        no_of_nodes = n;
        constructSegmentTree(arr, 0, n - 1, 0);
    }

    static int getMid(int start, int end) {
        return start + (end - start) / 2;
    }

    /**
     * This method constructSegmentTree() will be used to construct the
     *        Segment Tree from an array.
     * 
     * @param int arr[]
     * @param int start
     * @param int end
     * @param int index
     * @date 21/08/2019
     */
    Node constructSegmentTree(int arr[], int start, int end, int index) {
        if (start == end) {
            nodeArray[index] = new Node(true);
            nodeArray[index].max = nodeArray[index].min = nodeArray[index].sum = arr[start];
            nodeArray[index].startIndex = nodeArray[index].endIndex = start;
            return nodeArray[index];
        }
        int mid = getMid(start, end);
        nodeArray[index] = new Node(false);
        Node left = constructSegmentTree(arr, start, mid, 2 * index + 1);
        Node right = constructSegmentTree(arr, mid + 1, end, 2 * index + 2);
        nodeArray[index].sum = left.sum + right.sum;
        nodeArray[index].min = Math.min(left.min, right.min);
        nodeArray[index].max = Math.max(left.max, right.max);
        nodeArray[index].startIndex = start;
        nodeArray[index].endIndex = end;
        return nodeArray[index];
    }

    /**
     * This method findMin() will be used to find the minimum value between
     *        given indices using Segment Tree.
     * 
     * @param int start
     * @param int end
     * @param int index
     * @date 21/08/2019
     */
    int findMin(int start, int end, int index) {
        if ((nodeArray[index].startIndex >= start) && (nodeArray[index].endIndex <= end))
            return nodeArray[index].min;

        if ((end < nodeArray[index].startIndex) || (start > nodeArray[index].endIndex))
            return Integer.MAX_VALUE;

        return Math.min(findMin(start, end, 2 * index + 1), findMin(start, end, 2 * index + 2));
    }

    /**
     * This method findMax() will be used to find the maximum value between
     *        given indices using Segment Tree.
     * 
     * @param int start
     * @param int end
     * @param int index
     * @date 21/08/2019
     */
    int findMax(int start, int end, int index) {
        if ((nodeArray[index].startIndex >= start) && (nodeArray[index].endIndex <= end))
            return nodeArray[index].max;

        if ((end < nodeArray[index].startIndex) || (start > nodeArray[index].endIndex))
            return Integer.MIN_VALUE;

        return Math.max(findMax(start, end, 2 * index + 1), findMax(start, end, 2 * index + 2));
    }

    /**
     * This method findSum() will be used to find the sum of all value
     *        between given indices using Segment Tree.
     * 
     * @param int start
     * @param int end
     * @param int index
     * @date 21/08/2019
     */
    int findSum(int start, int end, int index) {
        if ((nodeArray[index].startIndex >= start) && (nodeArray[index].endIndex <= end))
            return nodeArray[index].sum;

        if ((end < nodeArray[index].startIndex) || (start > nodeArray[index].endIndex))
            return 0;

        return findSum(start, end, 2 * index + 1) + findSum(start, end, 2 * index + 2);
    }

    /**
     * This method updateTree() will be used to update the values between
     *        given indices using Segment Tree.
     * 
     * @param int start
     * @param int end
     * @param int index
     * @date 21/08/2019
     */
    Node updateTree(int start, int end, int index) {
        if ((end < nodeArray[index].startIndex) || (start > nodeArray[index].endIndex))
            return nodeArray[index];
        if (nodeArray[index].startIndex == nodeArray[index].endIndex) {
            nodeArray[index].max = nodeArray[index].min = nodeArray[index].sum += 4;
            return nodeArray[index];
        }
        Node left = updateTree(start, end, 2 * index + 1);
        Node right = updateTree(start, end, 2 * index + 2);
        nodeArray[index].sum = left.sum + right.sum;
        nodeArray[index].min = Math.min(left.min, right.min);
        nodeArray[index].max = Math.max(left.max, right.max);
        return nodeArray[index];
    }

    /**
     * This method printTree() will be used to print the Segment Tree.
     * 
     * @date 21/08/2019
     */
    void printTree(int a) {
        // if (a == 1) {
        // if (nodeArray[index].startIndex == nodeArray[index].endIndex)
        // System.out.print(nodeArray[index].min+" ");
        // else {
        // System.out.print(nodeArray[index].min +" ");
        // printTree(a, 2 * index + 1);
        // printTree(a, 2 * index + 2);
        // }
        // } else if (a == 2) {
        // if (nodeArray[index].startIndex == nodeArray[index].endIndex)
        // System.out.print(nodeArray[index].max+" ");
        // else {
        // System.out.print(nodeArray[index].max +" ");
        // printTree(a, 2 * index + 1);
        // printTree(a, 2 * index + 2);
        // }
        // } else if (a == 3) {
        // if (nodeArray[index].startIndex == nodeArray[index].endIndex)
        // System.out.print(nodeArray[index].sum +" ");
        // else {
        // System.out.print(nodeArray[index].sum + " ");
        // printTree(a, 2 * index + 1);
        // printTree(a, 2 * index + 2);
        // }
        // }

        if (a == 1) {
            for (int i = 0; i < nodeArray.length; i++) {
                if (nodeArray[i] == null)
                    System.out.print("* ");
                else
                    System.out.print(nodeArray[i].min + " ");
            }
            System.out.println("");
        } else if (a == 2) {
            for (int i = 0; i < nodeArray.length; i++) {
                if (nodeArray[i] == null)
                    System.out.print("* ");
                else
                    System.out.print(nodeArray[i].max + " ");
            }
            System.out.println("");
        } else if (a == 3) {
            for (int i = 0; i < nodeArray.length; i++) {
                if (nodeArray[i] == null)
                    System.out.print("* ");
                else
                    System.out.print(nodeArray[i].sum + " ");
            }
            System.out.println("");
        }
    }
}

class Prob2 {

    /**
     * This method printArray() will be used to print the array.
     * 
     * @param int arr[]
     * @date 21/08/2019
     */
    static void printArray(int arr[]) {
        for (int i = 0; i < arr.length; i++)
            System.out.print(arr[i] + " ");
    }

    /**
     * This method checkValid() will be used to check if indices are valid.
     * @param int start
     * @param int end
     * @param int n
     * @date 21/08/2019
     */
    static boolean checkValid(int n, int start, int end) {
        if ((start < 0) || (end > n - 1) || (start > end))
            return false;
        else
            return true;
    }

    /**
     * This method findMinbyBrute() will be used to find the minimum values
     *        between given indices using Brute Force.
     * @param int arr[]
     * @param int start
     * @param int end
     * @date 21/08/2019
     */
    static int findMinbyBrute(int arr[], int start, int end) {
        int min = arr[start];
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] < min)
                min = arr[i];
        }
        return min;
    }

    /**
     * This method findMaxbyBrute() will be used to find the maximum values
     *        between given indices using Brute Force.
     * @param int arr[]
     * @param int start
     * @param int end
     * @date 21/08/2019
     */
    static int findMaxbyBrute(int arr[], int start, int end) {
        int max = arr[start];
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] > max)
                max = arr[i];
        }
        return max;
    }

    /**
     * This method findSumbyBrute() will be used to find the sum of all
     *        values between given indices using Brute Force.
     * @param int arr[]
     * @param int start
     * @param int end
     * @date 21/08/2019
     */
    static int findSumbyBrute(int arr[], int start, int end) {
        int sum = 0;
        for (int i = start; i <= end; i++) {
            sum += arr[i];
        }
        return sum;
    }

    /**
     * This method findSumbyBrute() will be used to update all values between
     *        given indices using Brute Force.
     * @param int arr[]
     * @param int start
     * @param int end
     * @date 21/08/2019
     */
    static void updatebyBrute(int arr[], int start, int end) {
        for (int i = start; i <= end; i++)
            arr[i] += 4;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.println("Input the number the values in array.");
        int n = sc.nextInt();

        System.out.println("Enter the values.");
        int arr[] = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        SegmentTree tree = new SegmentTree(arr, n);

        while (true) {

            System.out.println("Menu:");
            System.out.println("1. Find Maximum value.");
            System.out.println("2. Find Minimum value.");
            System.out.println("3. Find Sum.");
            System.out.println("4. Update by adding 4.");
            System.out.println("5. Exit");

            int value = sc.nextInt();
            if ((value < 1) || (value > 5)) {
                System.out.println("Enter proper index value.");
                continue;
            }
            if (value == 5) {
                sc.close();
                System.exit(0);
            }

            System.out.println("Enter 1 for Brute force and 2 for using Segment Tree.");
            int way = sc.nextInt();
            if ((way < 1) || (way > 2)) {
                System.out.println("Enter proper way.");
                continue;
            }

            long startTime, endTime;

            System.out.println("Enter start and end index.");

            int start = sc.nextInt();
            int end = sc.nextInt();

            if (!checkValid(n, start, end)) {
                System.out.println("Enter proper start and end indices.");
                continue;
            }

            switch (value) {

            case 1: {
                if (way == 1) {
                    startTime = System.nanoTime();
                    int max = findMaxbyBrute(arr, start, end);
                    endTime = System.nanoTime();
                    System.out.print("Max value : " + max + "\nExecution time = " + (endTime - startTime) + " ns\n");
                } else if (way == 2) {
                    startTime = System.nanoTime();
                    int max = tree.findMax(start, end, 0);
                    endTime = System.nanoTime();
                    System.out.print("Max value : " + max + "\nExecution time = " + (endTime - startTime) + " ns\n");
                }
                break;
            }

            case 2: {
                if (way == 1) {
                    startTime = System.nanoTime();
                    int min = findMinbyBrute(arr, start, end);
                    endTime = System.nanoTime();
                    System.out.print("Min value : " + min + "\nExecution time = " + (endTime - startTime) + " ns\n");
                } else if (way == 2) {
                    startTime = System.nanoTime();
                    int min = tree.findMin(start, end, 0);
                    endTime = System.nanoTime();
                    System.out.print("Min value : " + min + "\nExecution time = " + (endTime - startTime) + " ns\n");
                }
                break;
            }

            case 3: {
                if (way == 1) {
                    startTime = System.nanoTime();
                    int sum = findSumbyBrute(arr, start, end);
                    endTime = System.nanoTime();
                    System.out.print("Sum : " + sum + "\nExecution time = " + (endTime - startTime) + " ns\n");
                } else if (way == 2) {
                    startTime = System.nanoTime();
                    int sum = tree.findSum(start, end, 0);
                    endTime = System.nanoTime();
                    System.out.print("Sum : " + sum + "\nExecution time = " + (endTime - startTime) + " ns\n");
                }
                break;
            }

            case 4: {
                if (way == 1) {
                    startTime = System.nanoTime();
                    updatebyBrute(arr, start, end);
                    endTime = System.nanoTime();
                    System.out.print("Execution time = " + (endTime - startTime) + " ns\n");
                    tree.updateTree(start, end, 0);
                    tree.printTree(1);
                } else if (way == 2) {
                    startTime = System.nanoTime();
                    tree.updateTree(start, end, 0);
                    endTime = System.nanoTime();
                    System.out.print("Execution time = " + (endTime - startTime) + " ns\n");
                    updatebyBrute(arr, start, end);
                    tree.printTree(1);
                }
                break;
            }
            }
        }
    }
}