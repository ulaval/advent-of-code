package year2020;

import java.io.IOException;
import java.util.List;

import common.InputReader;

public class December11th {

	public static final char EMPTY = 'L';
	public static final char OCCUPIED = '#';

	private final int height;
	private final int width;

	private char[][] seatingPositions;
	private char[][] seatingPositionsRoundBefore;

	public December11th(List<String> inputs) {
		this.height = inputs.size();
		this.width = inputs.get(0).length();
		seatingPositions = new char[width][height];
		seatingPositionsRoundBefore = new char[width][height];
		for (int i = 0; i < height; i++) {
			char[] line = inputs.get(i).toCharArray();
			for (int j = 0; j < line.length; j++) {
				seatingPositions[j][i] = line[j];
			}
		}
	}

	public int part1() {
		do {
			copySeatingPositions();
			executeIteration(4, false);
		} while (!isSeatingPositionEqualsToRoundBefore());

		return getTotalNumberOfSeatsOccupied();
	}

	public int part2() {
		do {
			copySeatingPositions();
			executeIteration(5, true);
		} while (!isSeatingPositionEqualsToRoundBefore());

		return getTotalNumberOfSeatsOccupied();
	}

	/** Copy array into another for comparison. */
	public void copySeatingPositions() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				seatingPositionsRoundBefore[j][i] = seatingPositions[j][i];
			}
		}
	}

	/** Equals on the array now and the array before. */
	public boolean isSeatingPositionEqualsToRoundBefore() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (seatingPositionsRoundBefore[j][i] != seatingPositions[j][i]) {
					return false;
				}
			}
		}

		return true;
	}

	/** Count number of '#' in array. */
	public int getTotalNumberOfSeatsOccupied() {
		int counterOfOccupiedSeats = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (seatingPositions[i][j] == OCCUPIED) {
					counterOfOccupiedSeats += 1;
				}
			}
		}
		return counterOfOccupiedSeats;
	}

	public void executeIteration(int numberOfNeighborsAccepted, boolean loop) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (seatingPositionsRoundBefore[x][y] == EMPTY && getNumberOfOccupiedSeats(x, y, loop) == 0) { // empty
																													// seat
					seatingPositions[x][y] = OCCUPIED;
				} else if (seatingPositionsRoundBefore[x][y] == OCCUPIED
						&& getNumberOfOccupiedSeats(x, y, loop) >= numberOfNeighborsAccepted) {
					seatingPositions[x][y] = EMPTY;
				}
			}
		}

	}

	public int getNumberOfOccupiedSeats(int x, int y, boolean loop) {
		int count = 0;
		count = isSeatOccupied(x, y, -1, 0, loop) ? count + 1 : count;
		count = isSeatOccupied(x, y, 1, 0, loop) ? count + 1 : count;
		count = isSeatOccupied(x, y, 0, 1, loop) ? count + 1 : count;
		count = isSeatOccupied(x, y, 0, -1, loop) ? count + 1 : count;
		count = isSeatOccupied(x, y, -1, -1, loop) ? count + 1 : count;
		count = isSeatOccupied(x, y, -1, 1, loop) ? count + 1 : count;
		count = isSeatOccupied(x, y, 1, -1, loop) ? count + 1 : count;
		count = isSeatOccupied(x, y, 1, 1, loop) ? count + 1 : count;
		return count;
	}

	public boolean isSeatOccupied(int x, int y, int variationX, int variationY, boolean loop) {

		do {
			x += variationX;
			y += variationY;
			if (isWithinBoundaries(x, y)) {
				if (seatingPositionsRoundBefore[x][y] == OCCUPIED) {
					return true;
				} else if (seatingPositionsRoundBefore[x][y] == EMPTY) {
					return false;
				}
			}
		} while (isWithinBoundaries(x, y) && loop);

		return false;
	}

	public boolean isWithinBoundaries(int x, int y) {
		return x >= 0 && x < width && y >= 0 && y < height;
	}

	public static void main(String[] args) throws IOException {
		InputReader reader = new InputReader();
		List<String> inputs = reader.read(December11th.class, "input11.txt");
		
		December11th part1 = new December11th(inputs);
		System.out.println("Part 1:" + part1.part1());
		
		December11th part2 = new December11th(inputs);
		System.out.println("Part 2:" + part2.part2());
	}
}
