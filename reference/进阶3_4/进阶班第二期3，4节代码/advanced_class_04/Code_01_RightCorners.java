package advanced_class_04;

import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;

public class Code_01_RightCorners {
	public static class Node {
		public int x;
		public int y;

		public Node(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}

	public static class MyComparator implements Comparator<Node> {

		@Override
		public int compare(Node o1, Node o2) {
			if (o1.x != o2.x) {
				return o1.x - o2.x;
			} else {
				return o2.y - o1.y;
			}
		}

	}

	public static LinkedList<Node> getRightCornerNodes1(int[] x, int[] y) {
		int size = x.length;
		LinkedList<Node> res = new LinkedList<Node>();
		Node[] nodes = new Node[size];
		for (int i = 0; i < size; i++) {
			nodes[i] = new Node(x[i], y[i]);
		}
		Arrays.sort(nodes, new MyComparator());
		for (int i = 0; i < size; i++) {
			boolean insert = true;
			for (int j = 0; j < size; j++) {
				if ((nodes[i].x < nodes[j].x) && (nodes[i].y < nodes[j].y)) {
					insert = false;
				}
			}
			if (insert) {
				res.add(nodes[i]);
			}
		}
		return res;
	}

	public static LinkedList<Node> getRightCornerNodes2(int[] x, int[] y) {
		int size = x.length;
		LinkedList<Node> res = new LinkedList<Node>();
		Node[] nodes = new Node[size];
		for (int i = 0; i < size; i++) {
			nodes[i] = new Node(x[i], y[i]);
		}
		Arrays.sort(nodes, new MyComparator());
		res.add(nodes[size - 1]);
		int rightMaxY = nodes[size - 1].y;
		for (int i = size - 2; i >= 0; i--) {
			if (nodes[i].y >= rightMaxY) {
				res.addFirst(nodes[i]);
			}
			rightMaxY = Math.max(rightMaxY, nodes[i].y);
		}
		return res;
	}

	public static int[] generateRandomArray(int size) {
		int[] arr = new int[size];
		for (int i = 0; i < size; i++) {
			arr[i] = (int) (Math.random() * 1000);
		}
		return arr;
	}

	public static boolean isEqual(LinkedList<Node> list1, LinkedList<Node> list2) {
		if (list1.size() != list2.size()) {
			return false;
		}
		while (!list1.isEmpty()) {
			Node node1 = list1.pollFirst();
			Node node2 = list2.pollFirst();
			if (node1.x != node2.x || node1.y != node2.y) {
				return false;
			}
		}
		return true;
	}

	public static void printArray(int[] x, int[] y) {
		for (int i = 0; i < x.length; i++) {
			System.out.print("(" + x[i] + "," + y[i] + ") ");
		}
		System.out.println();
	}

	public static void printLinkedList(LinkedList<Node> list) {
		for (Node node : list) {
			System.out.print("(" + node.x + "," + node.y + ") ");
		}
		System.out.println();
	}

	public static void main(String[] args) {
		int testTime = 3000000;
		for (int i = 0; i < testTime; i++) {
			int size = 3;
			int[] x = generateRandomArray(size);
			int[] y = generateRandomArray(size);
			LinkedList<Node> res1 = getRightCornerNodes1(x, y);
			LinkedList<Node> res2 = getRightCornerNodes2(x, y);
			if (!isEqual(res1, res2)) {
				printArray(x, y);
				printLinkedList(res1);
				printLinkedList(res2);
				break;
			}
		}
	}

}
