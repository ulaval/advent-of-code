package year2020;

import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

import common.InputReader;

public class December7th {

	public int part1(List<String> inputs) {
		Tree tree = new Tree();
		Node root = new Node("shiny gold", 0);
		tree.setRoot(root);

		for (String input : inputs) {
			String parent = input.substring(0, input.indexOf("bag") - 1);
			String[] children = input.substring(input.indexOf("contain") + 7).split(",");

			for (int i = 0; i < children.length; i++) {
				String color = children[i];
				color = color.trim();
				color = color.substring(color.indexOf(" "), color.indexOf("bag") - 1);
				children[i] = color.trim();
				tree.addNode(children[i], parent);
			}
		}

		Set<String> colors = tree.computeNumbersOfUniqueNodes(root);
		colors.remove("shiny gold");
		return colors.size();
	}

	public int part2(List<String> inputs) {
		Tree tree = new Tree();
		Node root = new Node("shiny gold", 0);
		tree.setRoot(root);
		Map<String, String> colors = new HashMap<>();

		for (String input : inputs) {
			String parent = input.substring(0, input.indexOf("bag") - 1);
			String children = input.substring(input.indexOf("contain") + 7);
			colors.put(parent, children);
		}	

		return getColors(colors, "shiny gold");
	}
	
	public int getColors(Map<String, String> colors, String colorToGet) {
		String childrenAsString = colors.get(colorToGet);
		int totalNumberOfBags = 0;
		
		if (Objects.nonNull(childrenAsString)) {
			String[] children = childrenAsString.split(",");
	
			for (int i = 0; i < children.length; i++) {
				String color = children[i].trim();
				String numberAsString = color.substring(0, color.indexOf(" "));
				int number = Integer.valueOf(numberAsString.equals("no") ? "0" : numberAsString);
				color = color.substring(color.indexOf(" "), color.indexOf("bag") - 1).trim();
				totalNumberOfBags = totalNumberOfBags + number + (number * getColors(colors, color));
			}
		}
		
		return totalNumberOfBags;
	}
 
	public class Node {
		String color;
		int numberOfBags;
		Set<Node> children;

		public Node(String color, int number) {
			this.color = color;
			this.numberOfBags = number;
			this.children = new HashSet<>();
		}

		public String toString() {
			return "Node " + color;
		}
	}

	public class Tree {
		Node root;
		Map<String, Node> nodes;

		public Tree() {
			root = null;
			nodes = new HashMap<>();
		}
		
		public void setRoot(Node root) {
			this.root = root;
			nodes.put(root.color, root);
		}

		public void addNode(String parent, String child) {
			if (!child.contains("shiny gold")) {
				if (Objects.nonNull(nodes.get(parent))) { // parent node exists
					Node childNode = Objects.isNull(nodes.get(child)) ? new Node(child, 0) : nodes.get(child);
					nodes.get(parent).children.add(childNode);
					nodes.put(child, childNode);

					return;
				}

				if (Objects.nonNull(nodes.get(child))) { // child node exists
					Node parentNode = Objects.isNull(nodes.get(parent)) ? new Node(parent, 0) : nodes.get(parent);
					parentNode.children.add(nodes.get(child));
					nodes.put(parent, parentNode);

					return;
				}

				// if no node exist
				Node newParentNode = new Node(parent, 0);
				Node newChildNode = new Node(child, 0);
				newParentNode.children.add(newChildNode);
				nodes.put(parent, newParentNode);
				nodes.put(child, newChildNode);
			}
		}
		
		public void addNode(String parent, String child, int number) {
			if (!child.contains("other")) {
				Node newParentNode = new Node(parent, 0);
				Node newChildNode = new Node(child, number);
				newParentNode.children.add(newChildNode);
				nodes.put(parent, newParentNode);
			}
		}
		
		public Set<String> computeNumbersOfUniqueNodes(Node root) {
			Set<String> uniqueColors = new HashSet<>();

			uniqueColors.add(root.color);
			for (Node child : root.children) {
				uniqueColors.add(child.color);
				uniqueColors.addAll(computeNumbersOfUniqueNodes(child));
			}

			return uniqueColors;
		}

		public int computeNumberOfBagsIn(Node root) {
			int number = 0;

			for (Node child : root.children) {
				return number + child.numberOfBags + (child.numberOfBags * computeNumberOfBagsIn(child));
			}

			return number;
		}
	}

	public static void main(String[] args) throws IOException {
		December7th obj = new December7th();
		InputReader reader = new InputReader();
		List<String> inputs = reader.read(December7th.class, "input7.txt");

		System.out.println("Part 1:" + obj.part1(inputs));
		System.out.println("Part 2:" + obj.part2(inputs));
	}
}
