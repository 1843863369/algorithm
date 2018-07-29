package advanced_class_02;

public class Code_04_GasStations {

	public static boolean[] stations(int[] dis, int[] oil) {
		if (dis == null || oil == null || dis.length < 2
				|| dis.length != oil.length) {
			return null;
		}
		int size = dis.length;
		int start = -1;
		for (int i = 0; i < size; i++) {
			dis[i] = oil[i] - dis[i];
			if (dis[i] >= 0) {
				start = i;
			}
		}
		boolean[] res = new boolean[size];
		if (start == -1) {
			return res;
		}
		int end = nextIndex(start, size);
		int need = 0;
		int rest = 0;
		int count = 0;
		while (count < size) {
			if (dis[start] < need) {
				need -= dis[start];
			} else {
				rest += dis[start] - need;
				need = 0;
				while (rest >= 0 && end != start) {
					rest += dis[end];
					end = nextIndex(end, size);
				}
				if (rest >= 0) {
					res[start] = true;
					end = lastIndex(end, size);
					rest -= dis[end];
				}
			}
			start = lastIndex(start, size);
			count++;
		}
		return res;
	}

	public static int lastIndex(int index, int size) {
		return index == 0 ? (size - 1) : index - 1;
	}

	public static int nextIndex(int index, int size) {
		return index == size - 1 ? 0 : (index + 1);
	}

	// for test
	public static boolean[] test(int[] dis, int[] oil) {
		if (dis == null || oil == null || dis.length < 2
				|| dis.length != oil.length) {
			return null;
		}
		boolean[] res = new boolean[dis.length];
		for (int i = 0; i < dis.length; i++) {
			dis[i] = oil[i] - dis[i];
		}
		for (int i = 0; i < dis.length; i++) {
			res[i] = canWalkThrough(dis, i);
		}
		return res;
	}

	// for test
	public static boolean canWalkThrough(int[] arr, int index) {
		int sum = 0;
		for (int i = 0; i < arr.length; i++) {
			sum += arr[index];
			if (sum < 0) {
				return false;
			}
			index = nextIndex(index, arr.length);
		}
		return true;
	}

	// for test
	public static void printArray(int[] dis, int[] oil) {
		for (int i = 0; i < dis.length; i++) {
			System.out.print(oil[i] - dis[i] + " ");
		}
		System.out.println();
	}

	// for test
	public static void printBooleanArray(boolean[] arr) {
		for (int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.println();
	}

	// for test
	public static int[] generateArray() {
		int[] res = new int[7];
		for (int i = 0; i < res.length; i++) {
			res[i] = (int) (Math.random() * 10);
		}
		return res;
	}

	// for test
	public static int[] copyArray(int[] arr) {
		int[] res = new int[arr.length];
		for (int i = 0; i < res.length; i++) {
			res[i] = arr[i];
		}
		return res;
	}

	// for test
	public static boolean isEqual(boolean[] res1, boolean[] res2) {
		for (int i = 0; i < res1.length; i++) {
			if (res1[i] != res2[i]) {
				return false;
			}
		}
		return true;
	}

	public static void main(String[] args) {
		for (int i = 0; i < 5000000; i++) {
			int[] dis = generateArray();
			int[] oil = generateArray();
			int[] dis1 = copyArray(dis);
			int[] oil1 = copyArray(oil);
			int[] dis2 = copyArray(dis);
			int[] oil2 = copyArray(oil);
			boolean[] res1 = stations(dis1, oil1);
			boolean[] res2 = test(dis2, oil2);
			if (!isEqual(res1, res2)) {
				printArray(dis, oil);
				printBooleanArray(res1);
				printBooleanArray(res2);
				System.out.println("what a fucking day!");
				break;
			}
		}
	}

}
