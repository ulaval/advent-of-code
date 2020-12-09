package year2020;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;

import common.InputReader;

public class December1st {

	public Integer getAnswerPart1(List<String> inputs) {
		List<Integer> inputsAsInt = inputs.stream().map(input -> Integer.valueOf(input)).collect(Collectors.toList());

		for (int i = 0; i < inputsAsInt.size(); i++) {
			for (int j = i + 1; j < inputsAsInt.size(); j++) {
				int first = inputsAsInt.get(i);
				int second = inputsAsInt.get(j);

				if ((first + second) == 2020) {
					System.out.println(first + "+" + second + "=" + (first + second));
					System.out.println(first + "*" + second + "=" + (first * second));
					return first * second;
				}
			}
		}
		
		return 0;
	}

	public Integer getAnswerPart2(List<String> inputs) {
		List<Integer> inputsAsInt = inputs.stream().map(input -> Integer.valueOf(input)).collect(Collectors.toList());

		for (int i = 0; i < inputsAsInt.size(); i++) {
			for (int j = 0; j < inputsAsInt.size(); j++) {
				for (int k = 0; k < inputsAsInt.size(); k++) {
					int first = inputsAsInt.get(i);
					int second = inputsAsInt.get(j);
					int third = inputsAsInt.get(k);

					if ((first + second + third) == 2020) {
						System.out.println(first + "+" + second + "+" + third + "=" + (first + second + third));
						System.out.println(first + "x" + second + "=" + (first * second * third));
						return first * second * third;
					}
				}
			}
		}

		return 0;
	}

	public static void main(String[] args) throws IOException {
		December1st obj = new December1st();
		InputReader reader = new InputReader();
		List<String> inputs = reader.read(December1st.class, "input.txt");

		System.out.println("Answer Part 1: " + obj.getAnswerPart1(inputs));
		System.out.println("Answer Part 2: " + obj.getAnswerPart2(inputs));
	}
}
