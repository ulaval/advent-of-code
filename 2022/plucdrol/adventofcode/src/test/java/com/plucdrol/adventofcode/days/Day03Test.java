package com.plucdrol.adventofcode.days;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class Day03Test {
    private static final String INPUT_TEST = """
            vJrwpWtwJgWrhcsFMMfFFhFp
            jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
            PmmdzqPrVvPwwTWBwg
            wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
            ttgJtRGJQctTZtZT
            CrZsJsPPZsGzwwsLwLmpwMDw
            """;

    @Test
    void doTheBartman() {
        var day03 = new Day03(INPUT_TEST);

        assertThat(day03.getReponse1()).isEqualTo(157);
        assertThat(day03.getReponse2()).isEqualTo(70);
    }
}
