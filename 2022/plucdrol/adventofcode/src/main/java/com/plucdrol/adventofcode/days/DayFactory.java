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
    @Value("classpath:days/day06")
    Resource day06Input;
    @Value("classpath:days/day07")
    Resource day07Input;
    @Value("classpath:days/day08")
    Resource day08Input;

    public List<Day> createAllDays() {
        return List.of(
                new Day01(readFile(day01Input)),
                new Day02(readFile(day02Input)),
                new Day03(readFile(day03Input)),
                new Day04(readFile(day04Input)),
                new Day05(readFile(day05Input)),
                new Day06(readFile(day06Input)),
                new Day07(readFile(day07Input)),
                new Day08(readFile(day08Input))
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
