package year2020;

import java.io.IOException;
import java.util.List;

import common.InputReader;

public class December12th {

	private List<String> inputs;
	private int facing = 90;
	private int eastWest = 0;
	private int northSouth = 0;
	private int waypointEast = 10;
	private int waypointNorth = 1;

	public December12th(List<String> inputs) {
		this.inputs = inputs;
	}

	public int part1() {
		for (String direction : inputs) {
			System.out.println("Direction: " + direction + ", East = " + eastWest + ", North = " + northSouth);
			int distance = Integer.valueOf(direction.substring(1));

			if (direction.startsWith("N")) {
				northSouth += distance;

			} else if (direction.startsWith("S")) {
				northSouth -= distance;

			} else if (direction.startsWith("E")) {
				eastWest += distance;

			} else if (direction.startsWith("W")) {
				eastWest -= distance;

			} else if (direction.startsWith("R")) {
				facing = (facing + distance) % 360;
				if (facing < 0) {
					facing = 360 + facing;
				}
			} else if (direction.startsWith("L")) {
				facing = (facing - distance) % 360;
				if (facing < 0) {
					facing = 360 + facing;
				}
			} else if (direction.startsWith("F")) {
				if (facing == 90) {
					eastWest += distance;
				} else if (facing == 180) {
					northSouth -= distance;
				} else if (facing == 270) {
					eastWest -= distance;
				} else if (facing == 0 || facing == 360) {
					northSouth += distance;
				}
			}

		}

		return Math.abs(eastWest) + Math.abs(northSouth);
	}

	public int part2() {
		for (String direction : inputs) {
			System.out.println("Direction: " + direction + ", East = " + eastWest + ", North = " + northSouth);
			int distance = Integer.valueOf(direction.substring(1));

			if (direction.startsWith("N")) {
				waypointNorth += distance;
			} else if (direction.startsWith("S")) {
				waypointNorth -= distance;
			} else if (direction.startsWith("E")) {
				waypointEast += distance;
			} else if (direction.startsWith("W")) {
				waypointEast -= distance;
			} else if (direction.startsWith("R") || direction.startsWith("L")) {
				if (distance == 180) {
					int east = waypointEast;
					int north = waypointNorth;
					waypointEast = east * -1;
					waypointNorth = north * -1;
				} else if ((direction.startsWith("R") && distance == 90)
						|| (direction.startsWith("L") && distance == 270)) {
					int east = waypointEast;
					int north = waypointNorth;
					waypointEast = north;
					waypointNorth = east * -1;
				} else if ((direction.startsWith("L") && distance == 90)
						|| (direction.startsWith("R") && distance == 270)) {
					int east = waypointEast;
					int north = waypointNorth;
					waypointEast = north * -1;
					waypointNorth = east;
				} 
			} else if (direction.startsWith("F")) {
				northSouth += (waypointNorth * distance);
				eastWest += (waypointEast * distance);
			}

		}

		return Math.abs(eastWest) + Math.abs(northSouth);
	}

	public static void main(String[] args) throws IOException {
		InputReader reader = new InputReader();
		List<String> inputs = reader.read(December12th.class, "input12.txt");

		December12th part1 = new December12th(inputs);
		System.out.println("Part 1:" + part1.part1());

		December12th part2 = new December12th(inputs);
		System.out.println("Part 2:" + part2.part2());
	}
}
