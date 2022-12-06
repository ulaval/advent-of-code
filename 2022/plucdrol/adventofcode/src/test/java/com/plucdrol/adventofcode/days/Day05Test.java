package com.plucdrol.adventofcode.days;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class Day05Test {

    private static final String INPUT_TEST = """
                [D]   \s
            [N] [C]   \s
            [Z] [M] [P]
             1   2   3\s
                        
            move 1 from 2 to 1
            move 3 from 1 to 3
            move 2 from 2 to 1
            move 1 from 1 to 2
            """;

    @Test
    void doTheBartman() {
        var day05 = new Day05(INPUT_TEST);

        assertThat(day05.getAnswer1()).isEqualTo("CMZ");
        assertThat(day05.getAnswer2()).isEqualTo("MCD");
    }
}
