package com.plucdrol.adventofcode.days;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;

public class Day06Test {

    private static final List<String> INPUT_TEST = List.of(
            "mjqjpqmgbljsphdztnvjfqwrcgsmlb",
            "bvwbjplbgvbhsrlpgdmjqwftvncz",
            "nppdvjthqldpwncqszvftbrmjlhg",
            "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
            "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"
    );

    @Test
    void doTheBartman() {
        var example1 = new Day06(INPUT_TEST.get(0));
        assertThat(example1.getAnswer1()).isEqualTo(7);
        assertThat(example1.getAnswer2()).isEqualTo(19);
        var example2 = new Day06(INPUT_TEST.get(1));
        assertThat(example2.getAnswer1()).isEqualTo(5);
        assertThat(example2.getAnswer2()).isEqualTo(23);
        var example3 = new Day06(INPUT_TEST.get(2));
        assertThat(example3.getAnswer1()).isEqualTo(6);
        assertThat(example3.getAnswer2()).isEqualTo(23);
        var example4 = new Day06(INPUT_TEST.get(3));
        assertThat(example4.getAnswer1()).isEqualTo(10);
        assertThat(example4.getAnswer2()).isEqualTo(29);
        var example5 = new Day06(INPUT_TEST.get(4));
        assertThat(example5.getAnswer1()).isEqualTo(11);
        assertThat(example5.getAnswer2()).isEqualTo(26);
    }
}
