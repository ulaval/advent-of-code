package year2020;

import java.io.IOException;
import java.util.List;

import common.InputReader;

public class December4th {

	public int countValidPassportsPart1(List<String> inputs) {
		int totalPassports = 0;
		int validPassportsCounter = 0;
		for (String input : inputs) {
			totalPassports++;
			if (input.contains("byr:") && input.contains("iyr:") && input.contains("eyr:") && input.contains("hgt:")
					&& input.contains("hcl:") && input.contains("ecl:") && input.contains("pid:")) {
				validPassportsCounter++;
			}
		}

		System.out.println("Total:" + totalPassports);
		return validPassportsCounter;
	}

	public int countValidPassportsPart2(List<String> inputs) {
		int totalPassports = 0;
		int validPassportsCounter = 0;
		for (String input : inputs) {
			totalPassports++;
			if (inputBYR(input) && inputIYR(input) && inputEYR(input) && inputHGT(input) && inputHCL(input)
					&& inputECL(input) && inputPID(input)) {
				validPassportsCounter++;
			}
		}

		System.out.println("Total:" + totalPassports);
		return validPassportsCounter;
	}

	public boolean inputBYR(String input) {
		int index = input.indexOf("byr:");
		if (index > -1) {
			String year = input.substring(index + 4, input.indexOf(" ", index));
			if (year.matches("^[0-9]{4}$")) {
				int yearInt = Integer.valueOf(year);

				return yearInt >= 1920 && yearInt <= 2002;
			}
		}

		return false;
	}

	public boolean inputIYR(String input) {
		int index = input.indexOf("iyr:");
		if (index > -1) {
			String year = input.substring(index + 4, input.indexOf(" ", index));
			if (year.matches("^[0-9]{4}$")) {
				int yearInt = Integer.valueOf(year);

				return yearInt >= 2010 && yearInt <= 2020;
			}
		}

		return false;
	}

	public boolean inputEYR(String input) {
		int index = input.indexOf("eyr:");
		if (index > -1) {
			String year = input.substring(index + 4, input.indexOf(" ", index));
			if (year.matches("^[0-9]{4}$")) {
				int yearInt = Integer.valueOf(year);

				return yearInt >= 2020 && yearInt <= 2030;
			}
		}

		return false;
	}

	public boolean inputHCL(String input) {
		int index = input.indexOf("hcl:");
		if (index > -1) {
			String hairColor = input.substring(index + 4, input.indexOf(" ", index));
			if (hairColor.matches("^#[a-f0-9]{6}$")) {
				return true;
			}
		}
		return false;
	}

	public boolean inputECL(String input) {
		int index = input.indexOf("ecl:");
		if (index > -1) {
			String eyeColor = input.substring(index + 4, input.indexOf(" ", index));
			if (eyeColor.equals("amb") || eyeColor.equals("blu") || eyeColor.equals("brn") || eyeColor.equals("gry")
					|| eyeColor.equals("grn") || eyeColor.equals("hzl") || eyeColor.equals("oth")) {
				return true;
			}
		}
		return false;
	}

	public boolean inputPID(String input) {
		int index = input.indexOf("pid:");
		if (index > -1) {
			String pid = input.substring(index + 4, input.indexOf(" ", index));
			if (pid.matches("^[0-9]{9}$")) {
				return true;
			}
		}
		return false;
	}

	public boolean inputHGT(String input) {
		int index = input.indexOf("hgt:");
		if (index > -1) {
			String hgt = input.substring(input.indexOf("hgt:") + 4, input.indexOf(" ", index));
			if (hgt.endsWith("in")) {
				int height = Integer.valueOf(hgt.substring(0, hgt.indexOf("in")));

				return height >= 59 && height <= 76;
			}
			if (hgt.endsWith("cm")) {
				int height = Integer.valueOf(hgt.substring(0, hgt.indexOf("cm")));

				return height >= 150 && height <= 193;
			}
		}

		return false;
	}

	public static void main(String[] args) throws IOException {
		December4th obj = new December4th();
		InputReader reader = new InputReader();
		List<String> inputs = reader.readPassport(December4th.class, "input4.txt");

		System.out.println("Valid Passports: " + obj.countValidPassportsPart1(inputs));		
		System.out.println("Valid Passports (Part 2): " + obj.countValidPassportsPart2(inputs));
	}
}
