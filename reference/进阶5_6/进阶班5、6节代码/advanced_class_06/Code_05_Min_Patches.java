package advanced_class_06;

public class Code_05_Min_Patches {

	public static int minPatches(int[] arr, int n) {
		int patches = 0;
		long range = 0;
		for (int i = 0; i != arr.length; i++) {
			while (arr[i] > range + 1) {
				range += range + 1;
				patches++;
				if (range >= n) {
					return patches;
				}
			}
			range += arr[i];
			if (range >= n) {
				return patches;
			}
		}
		while (n >= range + 1) {
			range += range + 1;
			patches++;
		}
		return patches;
	}

	public static void main(String[] args) {
		int[] test = { 1, 2, 31, 33 };
		int n = 2147483647;
		System.out.println(minPatches(test, n));

	}

}
