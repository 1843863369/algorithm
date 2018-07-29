package advanced_class_06;

public class Code_01_Remove_Duplicate_Letters {

	public static String removeDuplicateLetters1(String s) {
		int[] cnt = new int[26];
		int pos = 0; // the position for the smallest s[i]
		for (int i = 0; i < s.length(); i++) {
			cnt[s.charAt(i) - 'a']++;
		}
		for (int i = 0; i < s.length(); i++) {
			if (s.charAt(i) < s.charAt(pos)) {
				pos = i;
			}
			if (--cnt[s.charAt(i) - 'a'] == 0) {
				break;
			}
		}
		return s.length() == 0 ? "" : s.charAt(pos)
				+ removeDuplicateLetters1(s.substring(pos + 1).replaceAll(
						"" + s.charAt(pos), ""));
	}

	public static String removeDuplicateLetters2(String str) {
		String res = "";
		char[] chas = str.toCharArray();
		int[] cnt = new int[26];
		for (int i = 0; i < chas.length; i++) {
			cnt[chas[i] - 'a']++;
		}
		int L = 0;
		int R = 0;
		while (R != chas.length) {
			if (chas[R] != 0 && --cnt[chas[R] - 'a'] == 0) {
				int choose = L;
				for (int i = L; i <= R; i++) {
					if (chas[choose] == 0
							|| (chas[i] != 0 && chas[i] < chas[choose])) {
						choose = i;
					}
				}
				res += String.valueOf(chas[choose]);
				cnt = new int[26];
				for (int i = choose + 1; i < chas.length; i++) {
					if (chas[i] == chas[choose]) {
						chas[i] = 0;
					}
					if (chas[i] != 0) {
						cnt[chas[i] - 'a']++;
					}
				}
				L = choose + 1;
				R = choose;
			}
			R++;
		}
		return res;
	}

	public static void main(String[] args) {

	}

}
