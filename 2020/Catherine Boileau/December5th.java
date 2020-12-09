package year2020;

import java.io.IOException;
import java.util.List;

import common.InputReader;

public class December5th {

	public int part1(List<String> inputs) {
		int highestSeat = 0;
		
		for (String input : inputs) {
			int row = getRow(input);
			int seat = getSeat(input);
			int seatId = row * 8 + seat;
			
			if (seatId > highestSeat) {
				highestSeat = seatId;
			}
		}

		return highestSeat;
	}

	public int part2(List<String> inputs) {
		int[] seatsTaken = new int[886];
		
		for (String input : inputs) {
			int row = getRow(input);
			int seat = getSeat(input);
			int seatId = row * 8 + seat;
			
			seatsTaken[seatId] = 1;
		}
		
		for (int i = 40; i<886; i++) {
			if (seatsTaken[i] == 0) {
				return i;
			}
		}
		
		return 0;
	}

	public int getRow(String input) {
		char[] chars = input.toCharArray();
		int start = 0;
		int end = 127;

		for (int i = 0; i < 7; i++) {
			char row = chars[i];
			
			if(row == 'F') {
				int range = ((end - start) / 2);
				range = (range % 2 == 1) ? range + 1 : range;
				end = end - range;
			} else {
				int range = ((end - start) / 2);
				range = (range % 2 == 1) ? range + 1 : range;
				start = start + range;
			}			
		}
		
		return (chars[6] == 'F') ? start : end;
	}
	
	public int getSeat(String input) {
		char[] chars = input.toCharArray();
		int start = 0;
		int end = 7;

		for (int i = 7; i < 10; i++) {
			char seat = chars[i];
			
			if(seat == 'L') {
				int range = ((end - start) / 2);
				range = (range % 2 == 1) ? range + 1 : range;
				end = end - range;
			} else {
				int range = ((end - start) / 2);
				range = (range % 2 == 1) ? range + 1 : range;
				start = start + range;
			}			
		}
		
		return (chars[9] == 'L') ? start : end;
	}

	public static void main(String[] args) throws IOException {
		December5th obj = new December5th();
		InputReader reader = new InputReader();
		List<String> inputs = reader.read(December3rd.class, "input5.txt");

		System.out.println("Part 1:" + obj.part1(inputs));
		System.out.println("Part 2:" + obj.part2(inputs));
	}
}
