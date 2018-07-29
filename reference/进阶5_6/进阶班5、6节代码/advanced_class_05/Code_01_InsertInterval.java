package advanced_class_05;

import java.util.ArrayList;
import java.util.List;

/*
 * https://leetcode.com/problems/insert-interval/description/
 * 
 * Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
 * You may assume that the intervals were initially sorted according to their start times.
 * Example 1:
 * Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
 * Example 2:
 * Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
 * This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
 * 
 */

public class Code_01_InsertInterval {

	public static class Interval {
		int start;
		int end;

		Interval() {
			start = 0;
			end = 0;
		}

		Interval(int s, int e) {
			start = s;
			end = e;
		}
	}

	public List<Interval> insert(List<Interval> items, Interval newItems) {
		List<Interval> result = new ArrayList<>();
		int i = 0;
		while (i < items.size() && items.get(i).end < newItems.start) {
			result.add(items.get(i++));
		}
		while (i < items.size() && items.get(i).start <= newItems.end) {
			newItems.start = Math.min(newItems.start, items.get(i).start);
			newItems.end = Math.max(newItems.end, items.get(i).end);
			i++;
		}
		result.add(newItems);
		while (i < items.size()) {
			result.add(items.get(i++));
		}
		return result;
	}

}
