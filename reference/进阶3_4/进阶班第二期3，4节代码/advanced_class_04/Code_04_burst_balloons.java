package advanced_class_04;

// https://leetcode.com/problems/burst-balloons/description/
public class Code_04_burst_balloons {

	public static int maxCoins1(int[] arr) {
		if (arr == null || arr.length == 0) {
			return 0;
		}
		if (arr.length == 1) {
			return arr[0];
		}
		int[] help = new int[arr.length + 2];
		help[0] = 1;
		help[help.length - 1] = 1;
		for (int i = 0; i < arr.length; i++) {
			help[i + 1] = arr[i];
		}
		return process(help, 1, help.length - 2);
	}

	public static int process(int[] arr, int l, int r) {
		if (l == r) {
			return arr[l - 1] * arr[l] * arr[r + 1];
		}
		int max = Math.max(
				arr[l - 1] * arr[l] * arr[r + 1] + process(arr, l + 1, r),
				arr[l - 1] * arr[r] * arr[r + 1] + process(arr, l, r - 1)
				);
		for (int i = l + 1; i < r; i++) {
			max = Math.max(
					max, 
					arr[l - 1] * arr[i] * arr[r + 1] 
							+ process(arr, l, i - 1) 
							+ process(arr, i + 1, r));
		}
		return max;
	}

	public static int maxCoins2(int[] arr) {
		if (arr == null || arr.length == 0) {
			return 0;
		}
		int size = arr.length;
		int[] all = new int[size + 2];
		all[0] = 1;
		all[size + 1] = 1;
		for (int i = 0; i < size; i++) {
			all[i + 1] = arr[i];
		}
		int[][] dp = new int[size][size];
		for (int i = size - 1; i >= 0; i--) {
			dp[i][i] = all[i] * all[i + 1] * all[i + 2];
			for (int j = i + 1; j < size; j++) {
				int coins = 0;
				for (int k = i; k <= j; k++) {
					coins = all[i] * all[k + 1] * all[j + 2];
					coins += k != i ? dp[i][k - 1] : 0;
					coins += k != j ? dp[k + 1][j] : 0;
					dp[i][j] = Math.max(dp[i][j], coins);
				}
			}
		}
		return dp[0][size - 1];
	}

	public static void main(String[] args) {
		int[] arr = { 3, 2, 6, 4, 2, 7, 4, 7, 9 };
		System.out.println(maxCoins1(arr));
		System.out.println(maxCoins2(arr));
	}

}
