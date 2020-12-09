package year2020;

import java.io.IOException;
import java.util.List;

import common.InputReader;

public class December6th {

	public int part1(List<String> inputs) {
		int totalCount = 0;
		for (String input : inputs) {
			String[] peopleAnswersInGroup = input.split(" ");

			int[] yesAnswers = new int[26];
			for(int i=0; i<peopleAnswersInGroup.length; i++) {
				char[] answerFor1 = peopleAnswersInGroup[i].toCharArray();
				
				for(int j=0;j<answerFor1.length;j++) {
					char caractere = answerFor1[j];
					yesAnswers[caractere-97] = 1;
				}
			}
			
			int count = 0;
			for (int k=0; k<26; k++) {
				if (yesAnswers[k] == 1) {
					count++;
				}
			}
			System.out.println("Count = " + count);
			totalCount += count;
		}
						
		return totalCount;		
	}

	public int part2(List<String> inputs) {
		int totalCount = 0;
		for (String input : inputs) {
			String[] peopleAnswersInGroup = input.split(" ");

			int[] yesAnswers = new int[26];
			for(int i=0; i<peopleAnswersInGroup.length; i++) {
				char[] answerFor1 = peopleAnswersInGroup[i].toCharArray();
				
				for(int j=0;j<answerFor1.length;j++) {
					char caractere = answerFor1[j];
					yesAnswers[caractere-97] = yesAnswers[caractere-97]+1;
				}
			}
			
			int count = 0;
			for (int k=0; k<26; k++) {
				if (yesAnswers[k] == (peopleAnswersInGroup.length - 1)) {
					count++;
				}
			}
			System.out.println("Count = " + count);
			totalCount += count;
		}
						
		return totalCount;	
	}

	public static void main(String[] args) throws IOException {
		December6th obj = new December6th();
		InputReader reader = new InputReader();
		List<String> inputs = reader.readCustomAnswers(December6th.class, "input6.txt");

		System.out.println("Part 1:" + obj.part1(inputs));
		System.out.println("Part 2:" + obj.part2(inputs));
	}
}
