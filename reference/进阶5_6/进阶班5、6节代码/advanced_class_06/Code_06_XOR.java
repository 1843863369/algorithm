package advanced_class_06;

import java.util.HashMap;

public class Code_06_XOR {

	public static int mostXORs0(int[] arr) {
		int ans = Integer.MIN_VALUE;
		int xor = 0;
		int[] mosts = new int[arr.length];
		HashMap<Integer, Integer> map = new HashMap<>();
		map.put(0, -1);
		for (int i = 0; i < arr.length; i++) {
			xor ^= arr[i];
			if (map.containsKey(xor)) {
				int j = map.get(xor);
				mosts[i] = j == -1 ? 1 : (mosts[j] + 1);
			}
			mosts[i] = Math.max(mosts[i-1], mosts[i]);
			map.put(xor, i);
			ans = Math.max(ans, mosts[i]);
		}
		return ans;
	}

	public static void main(String[] args) {
		int[] test = { 3, 0, 2, 2 };
		System.out.println(mostXORs0(test));
	}

}
