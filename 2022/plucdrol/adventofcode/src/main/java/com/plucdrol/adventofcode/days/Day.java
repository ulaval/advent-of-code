package com.plucdrol.adventofcode.days;

import lombok.Getter;

@Getter
public abstract class Day {

    private final int number;

    public Day(int number) {
        this.number = number;
    }

    @Override
    public String toString() {
        return String.format("⭐ Day %s:\tAnswer 1: '%s';\tAnswer 2: '%s'", getNumber(), getAnswer1(), getAnswer2());
    }

    public abstract Object getAnswer1();

    public abstract Object getAnswer2();
}
