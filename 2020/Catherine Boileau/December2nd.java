package year2020;

import java.io.IOException;
import java.util.List;
import java.util.function.Function;

import common.InputReader;

public class December2nd {

	public boolean verifyPassword(String password) {
		String[] split = password.split(" ");
		Integer minimumOccurences = Integer.valueOf(split[0].substring(0, split[0].indexOf("-")));
		Integer maximumOccurences = Integer.valueOf(split[0].substring(split[0].indexOf("-") + 1));
		char letter = split[1].charAt(0);
		int numberOfLettersInPassword = this.getNumbersOfLetters(split[2], letter);
		
		if (numberOfLettersInPassword >= minimumOccurences && numberOfLettersInPassword <= maximumOccurences) {
			return true;
		}

		return false;
	}

	public boolean verifyPasswordPart2(String password) {
		String[] split = password.split(" ");
		Integer minimumOccurences = Integer.valueOf(split[0].substring(0, split[0].indexOf("-")));
		Integer maximumOccurences = Integer.valueOf(split[0].substring(split[0].indexOf("-") + 1));
		char letter = split[1].charAt(0);
		
		if (split[2].charAt(minimumOccurences - 1) == letter ^ split[2].charAt(maximumOccurences - 1) == letter) { //XOR!!
			return true;	
		}

		return false;
	}

	private int getNumbersOfLetters(String password, char letter) {
		int count = 0;

		for (int i = 0; i < password.length(); i++) {
			if (password.charAt(i) == letter) {
				count++;
			}
		}

		return count;
	}
	
	private int getNumberOfValidPasswords(List<String> inputs, Function<String, Boolean> function) {
		int counter = 0;
		for (int i = 0; i < inputs.size(); i++) {
			if (function.apply(inputs.get(i))) {
				counter++;
			}
		}
		
		return counter;
	}

	public static void main(String[] args) throws IOException {
		December2nd obj = new December2nd();
		InputReader reader = new InputReader();
		List<String> inputs = reader.read(December2nd.class, "input2.txt");
		
		System.out.println("Numbers of valid passwords: " + obj.getNumberOfValidPasswords(inputs, obj::verifyPassword));
		System.out.println("Numbers of valid passwords, part 2: " + obj.getNumberOfValidPasswords(inputs, obj::verifyPasswordPart2));
	}
}
