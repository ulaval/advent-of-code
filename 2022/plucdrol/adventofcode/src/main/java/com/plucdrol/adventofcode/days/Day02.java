package com.plucdrol.adventofcode.days;

import lombok.Getter;

import java.util.Arrays;

@Getter
public class Day02 extends Day {

    private final long answer1;
    private final long answer2;

    public Day02(String input) {
        super(2);
        var games = input.split("\n");

        answer1 = Arrays.stream(games).mapToInt(this::getScore1).sum();
        answer2 = Arrays.stream(games).mapToInt(this::getScore2).sum();
    }

    private int getScore1(String game) {
        var gameSplit = game.split(" ");
        var opponentChoice = getChoice(gameSplit[0]);
        var myChoice = getChoice(gameSplit[1]);

        return gameScore(opponentChoice, myChoice) + choiceValue(myChoice);
    }

    private String getChoice(String code) {
        return switch (code) {
            case "A", "X" -> "✊";
            case "B", "Y" -> "🤚";
            case "C", "Z" -> "✌";
            default -> throw new IllegalStateException("Unexpected value: " + code);
        };
    }

    private int gameScore(String opponent, String me) {
        var result = switch (opponent) {
            case "✊" -> me.equals("🤚") ? 6 : null;
            case "🤚" -> me.equals("✌") ? 6 : null;
            case "✌" -> me.equals("✊") ? 6 : null;
            default -> throw new IllegalStateException("Unexpected value: " + opponent);
        };
        if (result == null) {
            return opponent.equals(me) ? 3 : 0;
        }
        return result;
    }

    private int getScore2(String game) {
        var gameSplit = game.split(" ");
        var opponentChoice = getChoice(gameSplit[0]);
        var myChoice = getMyChoice(opponentChoice, gameSplit[1]);

        return gameScore(opponentChoice, myChoice) + choiceValue(myChoice);
    }

    private String getMyChoice(String choiceOpponent, String code) {
        return switch (choiceOpponent) {
            case "✊" -> switch (code) {
                case "X" -> "✌";
                case "Y" -> "✊";
                case "Z" -> "🤚";
                default -> throw new IllegalStateException("Unexpected value: " + code);
            };
            case "🤚" -> switch (code) {
                case "X" -> "✊";
                case "Y" -> "🤚";
                case "Z" -> "✌";
                default -> throw new IllegalStateException("Unexpected value: " + code);
            };
            case "✌" -> switch (code) {
                case "X" -> "🤚";
                case "Y" -> "✌";
                case "Z" -> "✊";
                default -> throw new IllegalStateException("Unexpected value: " + code);
            };
            default -> throw new IllegalStateException("Unexpected value: " + choiceOpponent);
        };
    }

    private int choiceValue(String choice) {
        return switch (choice) {
            case "✊" -> 1;
            case "🤚" -> 2;
            case "✌" -> 3;
            default -> throw new IllegalStateException("Unexpected value: " + choice);
        };
    }
}
