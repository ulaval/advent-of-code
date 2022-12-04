package com.plucdrol.adventofcode.days;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class Day04Test {

    private static final String INPUT_TEST = """
            2-4,6-8
            2-3,4-5
            5-7,7-9
            2-8,3-7
            6-6,4-6
            2-6,4-8
            """;

    @Test
    void doTheBartman() {
        var day = new Day04(INPUT_TEST);

        assertThat(day.getAnswer1()).isEqualTo(2);
        assertThat(day.getAnswer2()).isEqualTo(4);
    }
}
