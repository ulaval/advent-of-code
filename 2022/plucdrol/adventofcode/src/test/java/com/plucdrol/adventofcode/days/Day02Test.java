package com.plucdrol.adventofcode.days;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class Day02Test {

    private static final String INPUT_TEST = """
            A Y
            B X
            C Z
            """;

    @Test
    void doTheBartman() {
        var day02 = new Day02(INPUT_TEST);

        assertThat(day02.getAnswer1()).isEqualTo(15);
        assertThat(day02.getAnswer2()).isEqualTo(12);
    }

}
