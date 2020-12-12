package year2020;

import java.io.IOException;
import java.math.BigInteger;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import common.InputReader;

public class December10th {

	private List<Long> inputs;
	private long diff1Jolt = 0;
	private long diff3Jolts = 0;

	public December10th(List<Long> inputs) {
		this.inputs = inputs;
	}

	public long part1() {
		getDifferenceOfJoltage();
		return diff3Jolts * diff1Jolt;
	}

	public BigInteger part2() {
		Node root = new Node(0L);
		Tree tree = new Tree(root);

		inputs.add(0, 0L);
		inputs.add(inputs.size(), getAdapterJoltage(inputs));

		for (int i = 0; i < inputs.size(); i++) {
			Long parent = inputs.get(i);

			for (int j = i + 1; j < i + 4; j++) {
				if (j < inputs.size()) {
					Long child = inputs.get(j);
					if ((child - parent) <= 3) {
						tree.addChild(new Node(inputs.get(j)), parent);
					}
				}
			}
		}

		tree.countLeaves();
		return tree.root.leafNumber;
	}
	
	public long getAdapterJoltageForInputs() {
		return inputs.get(inputs.size() - 1);
	}

	public long getAdapterJoltage(List<Long> inputsParameter) {
		return inputsParameter.get(inputsParameter.size() - 1) + 3;
	}

	public long getDifferenceOfJoltage() {
		long totalDifference = 0;
		diff1Jolt = 0;
		diff3Jolts = 0;

		long diffOutlet = inputs.get(0) - 0;
		if (diffOutlet == 1) {
			diff1Jolt += 1;
		} else if (diffOutlet == 3) {
			diff3Jolts += 1;
		}

		for (int i = 0; i < inputs.size() - 1; i++) {
			long diff = (inputs.get(i + 1) - inputs.get(i));
			if (diff == 1) {
				diff1Jolt += 1;
			} else if (diff == 3) {
				diff3Jolts += 1;
			}
			totalDifference = totalDifference + diff;
		}

		long diffDevice = getAdapterJoltage(inputs) - inputs.get(inputs.size() - 1);
		if (diffDevice == 1) {
			diff1Jolt += 1;
		} else if (diffDevice == 3) {
			diff3Jolts += 1;
		}

		return totalDifference;
	}

	public class Node {
		public Long value;
		public BigInteger leafNumber = BigInteger.ZERO;
		public Set<Node> children;

		public Node(Long value) {
			this.value = value;
			this.children = new HashSet<>();
		}
		
		public void setLeafNumber(BigInteger number) {
			this.leafNumber = number;
		}

		public boolean isLeaf() {
			return children.isEmpty();
		}

		public String toString() {
			return value.toString();
		}
	}

	public class Tree {
		public Node root;
		public Map<Long, Node> nodes;

		public Tree(Node root) {
			this.root = root;
			nodes = new HashMap<>();
			nodes.put(root.value, root);
		}

		public void addChild(Node child, long parent) {			
			Node childInMap = nodes.get(child.value);
			if (childInMap == null) {
				nodes.put(child.value, child);
				childInMap = nodes.get(child.value);
			}		

			Node parentNode = nodes.get(parent);
			parentNode.children.add(childInMap);
		}
		
		public int countLeaves() {			
			for(int i=inputs.size() - 1; i >=0; i--) {
				Long value = inputs.get(i);
				Node correspondingNode = nodes.get(value);
				
				BigInteger numberOfChildLeaves = BigInteger.ZERO;
				for (Node child : correspondingNode.children) {
					if (child.value == (getAdapterJoltageForInputs())) {
						numberOfChildLeaves = numberOfChildLeaves.add(BigInteger.ONE);
					} else {
						numberOfChildLeaves = numberOfChildLeaves.add(child.leafNumber);
					}
				}
				correspondingNode.setLeafNumber(numberOfChildLeaves);
			}
			
			return 0;
		}
	}

	public static void main(String[] args) throws IOException {
		InputReader reader = new InputReader();
		List<Long> inputs = reader.readInteger(December10th.class, "input10.txt");
		Collections.sort(inputs);
		December10th obj = new December10th(inputs);

		System.out.println("Part 1:" + obj.part1());
		System.out.println("Part 2:" + obj.part2());
	}
}
