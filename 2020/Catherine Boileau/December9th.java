package year2020;

import java.io.IOException;
import java.util.List;
import java.util.NoSuchElementException;

import common.InputReader;

public class December9th {

	private List<Long> inputs;
	private int preamble = 25;
	private int startRange = 0;
	private int endRange = 0;

	public December9th(List<Long> inputs) {
		this.inputs = inputs;
	}

	public long part1() {
		for (int i = preamble; i < inputs.size(); i++) {
			Long value = inputs.get(i);
			System.out.println("Value:" + value);
			if (!isNumberValid(value, (i - preamble))) {
				return value;
			}
		}

		return -1;
	}

	public boolean isNumberValid(Long value, int startIndex) {
		for (int j = startIndex; j < (preamble + startIndex); j++) {
			for (int k = startIndex + 1; k < (preamble + startIndex); k++) {
				System.out.println("Addition " + j + "+" + k + ":  " + inputs.get(j) + "+" + inputs.get(k) + "="
						+ (inputs.get(j) + inputs.get(k)));
				if ((inputs.get(j) + inputs.get(k)) == value) {
					return true;
				}
			}
		}

		return false;
	}

	public long part2(long invalidNumber, int startIndex) {
		for (int j = startIndex; j < inputs.size(); j++) {			
			if (sum(invalidNumber, j)) {
				List<Long> range = inputs.subList(startRange, endRange);
				Long max = range.stream().mapToLong(v -> v).max().orElseThrow(NoSuchElementException::new);
				Long min = range.stream().mapToLong(v -> v).min().orElseThrow(NoSuchElementException::new);
				
				return max + min;
			}
		}
		
		return -1;
	}
	
	public boolean sum(long invalidNumber, int startIndex) {
		long sum = 0;
		for (int k = startIndex; k < inputs.size(); k++) {
			sum = sum + inputs.get(k);
			if (sum >= invalidNumber) {
				if (sum == invalidNumber) {
					startRange = startIndex;
					endRange = k;
					return true;
				}
				
				return false;
			}
		}
		
		return false;
	}

	public static void main(String[] args) throws IOException {
		InputReader reader = new InputReader();
		List<Long> inputs = reader.readInteger(December9th.class, "input9.txt");
		December9th obj = new December9th(inputs);
		
		long value = obj.part1();
		System.out.println("Part 1:" + value);
		System.out.println("Part 2:" + obj.part2(value, 0));
	}
}
