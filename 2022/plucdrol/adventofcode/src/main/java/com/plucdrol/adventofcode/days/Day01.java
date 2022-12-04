package com.plucdrol.adventofcode.days;

import lombok.Getter;

import java.util.Arrays;

@Getter
public class Day01 extends Day {

    private final long answer1;
    private final long answer2;

    public Day01(String input) {
        super(1);
        var valueGroups = input.split("\n\n");
        var sums = Arrays.stream(valueGroups).map(this::calculateSum).sorted().toList();

        var top3 = sums.subList(sums.size() - 3, sums.size());

        answer1 = top3.get(top3.size() - 1);
        answer2 = top3.stream().mapToInt(Integer::intValue).sum();
    }

    private int calculateSum(String group) {
        String[] values = group.split("\n");
        return Arrays.stream(values).mapToInt(Integer::parseInt).sum();
    }
}
