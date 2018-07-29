package advanced_class_06;

import java.util.ArrayList;
import java.util.List;

public class Code_02_Remove_Invalid_Parentheses {

	public List<String> removeInvalidParentheses(String s) {
		List<String> ans = new ArrayList<>();
		remove(s, ans, 0, 0, new char[] { '(', ')' });
		return ans;
	}

	public void remove(String s, List<String> ans, int preValid,
			int lastNoValid, char[] par) {
		for (int stack = 0, i = preValid; i < s.length(); i++) {
			if (s.charAt(i) == par[0]) {
				stack++;
			}
			if (s.charAt(i) == par[1]) {
				stack--;
			}
			if (stack < 0) {
				for (int j = lastNoValid; j <= i; ++j)
					if (s.charAt(j) == par[1]
							&& (j == lastNoValid || s.charAt(j - 1) != par[1]))
						remove(s.substring(0, j)
								+ s.substring(j + 1, s.length()), ans, i, j,
								par);
				return;
			}
		}
		String reversed = new StringBuilder(s).reverse().toString();
		if (par[0] == '(') { // finished left to right
			remove(reversed, ans, 0, 0, new char[] { ')', '(' });
		} else {
			ans.add(reversed);
		}
	}

}
