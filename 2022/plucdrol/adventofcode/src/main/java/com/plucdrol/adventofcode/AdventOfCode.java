package com.plucdrol.adventofcode;

import com.plucdrol.adventofcode.days.DayFactory;
import lombok.extern.java.Log;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@Log
@SpringBootApplication
public class AdventOfCode implements CommandLineRunner {

    private final DayFactory dayFactory;

    public AdventOfCode(DayFactory dayFactory) {
        this.dayFactory = dayFactory;
    }

    public static void main(String[] args) {
        SpringApplication.run(AdventOfCode.class, args);
    }

    @Override
    public void run(String... args) {
        log.info("🎅🎅🎅");

        var days = dayFactory.createAllDays();
        days.forEach(day -> log.info(day.toString()));

        log.info("🎄🎄🎄");
    }

}
