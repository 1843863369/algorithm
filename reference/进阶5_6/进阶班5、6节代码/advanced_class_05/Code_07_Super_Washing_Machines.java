package advanced_class_05;

public class Code_07_Super_Washing_Machines {

	/*
	 * You have n super washing machines on a line. Initially, each washing
	 * machine has some dresses or is empty. For each move, you could choose any
	 * m (1 ≤ m ≤ n) washing machines, and pass one dress of each washing
	 * machine to one of its adjacent washing machines at the same time .
	 * 
	 * Given an integer array representing the number of dresses in each washing
	 * machine from left to right on the line, you should find the minimum
	 * number of moves to make all the washing machines have the same number of
	 * dresses. If it is not possible to do it, return -1.
	 */
	public static int findMinMoves(int[] machines) {
		int total = 0;
		for (int i : machines) {
			total += i;
		}
		if (total % machines.length != 0) {
			return -1;
		}
		int avg = total / machines.length, cnt = 0, max = 0, gorl = 0;
		for (int load : machines) {
			gorl = load - avg;
			cnt += gorl;
			max = Math.max(max, Math.max(gorl, Math.abs(cnt)));
		}
		return max;
	}

	public static void main(String[] args) {
		int[] test = { 1, 0, 5 };
		System.out.println(findMinMoves(test));

	}

}
