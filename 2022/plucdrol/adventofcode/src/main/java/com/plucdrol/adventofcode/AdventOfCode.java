package com.plucdrol.adventofcode;

import com.plucdrol.adventofcode.days.Day01;
import com.plucdrol.adventofcode.days.Day02;
import com.plucdrol.adventofcode.days.Day03;
import jakarta.annotation.PostConstruct;
import lombok.extern.java.Log;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.core.io.Resource;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.file.Files;

@Log
@SpringBootApplication
public class AdventOfCode {

    @Value("classpath:days/day01")
    Resource day01Input;
    @Value("classpath:days/day02")
    Resource day02Input;
    @Value("classpath:days/day03")
    Resource day03Input;

    public static void main(String[] args) {
        SpringApplication.run(AdventOfCode.class, args);
    }

    @PostConstruct
    public void doTheBartman() {
        log.info("🎅🎅🎅");

        var day01 = new Day01(lireFichier(day01Input));
        log.info(String.format("⭐ Jour 1: %s", day01));
        var day02 = new Day02(lireFichier(day02Input));
        log.info(String.format("⭐ Jour 2: %s", day02));
        var day03 = new Day03(lireFichier(day03Input));
        log.info(String.format("⭐ Jour 3: %s", day03));

        log.info("🎄🎄🎄");
    }

    private String lireFichier(Resource path) {
        try {
            return Files.readString(path.getFile().toPath()).replaceAll("\r", "");
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
    }

}
