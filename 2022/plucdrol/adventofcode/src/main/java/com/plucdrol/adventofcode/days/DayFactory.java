package com.plucdrol.adventofcode.days;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.core.io.Resource;
import org.springframework.stereotype.Component;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.file.Files;
import java.util.List;

@Component
public class DayFactory {

    @Value("classpath:days/day01")
    Resource day01Input;
    @Value("classpath:days/day02")
    Resource day02Input;
    @Value("classpath:days/day03")
    Resource day03Input;
    @Value("classpath:days/day04")
    Resource day04Input;
    @Value("classpath:days/day05")
    Resource day05Input;

    public List<Day> createAllDays() {
        return List.of(
                new Day01(readFile(day01Input)),
                new Day02(readFile(day02Input)),
                new Day03(readFile(day03Input)),
                new Day04(readFile(day04Input)),
                new Day05(readFile(day05Input))
        );
    }

    private String readFile(Resource path) {
        try {
            return Files.readString(path.getFile().toPath()).replaceAll("\r", "");
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
    }
}