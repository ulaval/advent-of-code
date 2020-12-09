package year2020;

import java.io.IOException;
import java.util.List;

import common.InputReader;

public class December3rd {
	
	public int countTrees(List<String> inputs, int incrementRight, int incrementDown) {
		int treeCounter = 0;
		int positionToCheck = 0;

		for (int i = 0; i < inputs.size(); i+=incrementDown) {
			String input = inputs.get(i);
			char coordinates = input.charAt(positionToCheck % (input.length()));
			if (coordinates == '#') {
				treeCounter++;
			}
			positionToCheck += incrementRight;
		}

		return treeCounter;
	}

	public static void main(String[] args) throws IOException {
		December3rd obj = new December3rd();
		InputReader reader = new InputReader();
		List<String> inputs = reader.read(December3rd.class, "input3.txt");

		int count31 =  obj.countTrees(inputs, 3, 1);
		int count11 =  obj.countTrees(inputs, 1, 1);
		int count51 =  obj.countTrees(inputs, 5, 1);
		int count71 =  obj.countTrees(inputs, 7, 1);
		int count12 =  obj.countTrees(inputs, 1, 2);
		System.out.println("Numbers of Trees (Part 1): " + count31);
		System.out.println("Product (Part 2): " + (count31 * count11 * count51 * count71 * count12));
	}
}
