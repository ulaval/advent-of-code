package com.plucdrol.adventofcode.days;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class Day08Test {

    private static final String INPUT_TEST = """
            30373
            25512
            65332
            33549
            35390
            """;

    @Test
    void doTheBartman() {
        var day = new Day08(INPUT_TEST);

        assertThat(day.getAnswer1()).isEqualTo(21);
    }
}
