package year2020;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import common.InputReader;

public class December8th {

	public int part1(List<String> inputs) {
		int[] instructionsExecuted = new int[inputs.size()];
		int accumulator = 0;
		int currentPosition = 0;
		String instruction = "";

		while (instructionsExecuted[currentPosition] == 0) {
			instruction = inputs.get(currentPosition);
			if (instruction.startsWith("acc")) {
				int value = getValue(instruction);
				accumulator += value;
				instructionsExecuted[currentPosition] = 1;
				currentPosition += 1;
			} else if (instruction.startsWith("jmp")) {
				int value = getValue(instruction);
				instructionsExecuted[currentPosition] = 1;
				currentPosition += value;
			} else if (instruction.startsWith("nop")) {
				currentPosition += 1;
			}
		}

		return accumulator;
	}

	public int part2(List<String> inputs) {
		List<Integer> instructionsExecuted = new ArrayList<>(inputs.size());
		for (int i = 0; i < inputs.size(); i++) {
			instructionsExecuted.add(Integer.valueOf(0));
		}

		int accumulator = 0;
		int currentPosition = 0;
		String instruction = "";

		while (currentPosition < inputs.size()) {
			instruction = inputs.get(currentPosition);
			if (instruction.startsWith("acc")) {
				int value = getValue(instruction);
				accumulator += value;
				instructionsExecuted.set(currentPosition, instructionsExecuted.get(currentPosition) + 1);
				currentPosition += 1;
			} else if (instruction.startsWith("jmp")) {
				int value = getValue(instruction);
				instructionsExecuted.set(currentPosition, instructionsExecuted.get(currentPosition) + 1);
				currentPosition += value;
			} else if (instruction.startsWith("nop")) {
				currentPosition += 1;
			}

			if (instructionsExecuted.contains(Integer.valueOf(2))) {
				return -1;
			}
		}

		return accumulator;
	}

	public int part2Big(List<String> inputs) {
		int resultatPart2 = 0;
		int startingIndex = 0;
		List<String> nextInputs = new ArrayList<>(inputs.size());
		for (int i = 0; i < inputs.size(); i++) {
			nextInputs.add("");
		}
		Collections.copy(nextInputs, inputs);

		while (startingIndex != -1 && startingIndex < inputs.size()) {
			if (resultatPart2 < 1) {
				resultatPart2 = part2(nextInputs);

				if (resultatPart2 > 0) {
					return resultatPart2;
				}
			}
			startingIndex = getNextIndexOf(inputs, startingIndex + 1);
			if (startingIndex >= 0) {
				nextInputs = getNewInput(inputs, startingIndex);
			}
		}

		return resultatPart2;
	}

	public int getNextIndexOf(List<String> inputs, int startIndex) {
		List<String> inputsTruncated = inputs.subList(startIndex, inputs.size());
		for (int i = 0; i < inputsTruncated.size(); i++) {
			if (inputsTruncated.get(i).startsWith("jmp") || inputsTruncated.get(i).startsWith("nop")) {
				//System.out.println("Next index: " + (i+startIndex));
				return i + startIndex;
			}
		}
		return -1;
	}

	public List<String> getNewInput(List<String> inputs, int index) {
		String instruction = inputs.get(index);
		List<String> newInputs = new ArrayList<>(inputs.size());
		for (int i = 0; i < inputs.size(); i++) {
			newInputs.add("");
		}
		Collections.copy(newInputs, inputs);

		if (instruction.startsWith("jmp")) {
			String instructionToChange = newInputs.get(index);
			instructionToChange = instructionToChange.replace("jmp", "nop");
			newInputs.set(index, instructionToChange);
		} else if (instruction.startsWith("nop")) {
			String instructionToChange = newInputs.get(index);
			instructionToChange = instructionToChange.replace("nop", "jmp");
			newInputs.set(index, instructionToChange);
		}
		//System.out.println("New instructions: " + newInputs);
		return newInputs;
	}

	public int getValue(String input) {
		return Integer.valueOf(input.substring(input.indexOf(" ") + 1));
	}

	public static void main(String[] args) throws IOException {
		December8th obj = new December8th();
		InputReader reader = new InputReader();
		List<String> inputs = reader.read(December8th.class, "input8.txt");

		System.out.println("Part 1:" + obj.part1(inputs));
		System.out.println("Part 2:" + obj.part2Big(inputs));
	}
}
