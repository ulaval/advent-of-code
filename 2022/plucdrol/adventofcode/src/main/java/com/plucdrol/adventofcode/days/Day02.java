package com.plucdrol.adventofcode.days;

import lombok.Getter;

import java.util.Arrays;

@Getter
public class Day02 {

    private final int reponse1;
    private final int reponse2;

    public Day02(String input) {
        var parties = input.split("\n");

        reponse1 = Arrays.stream(parties).mapToInt(this::getScore1).sum();
        reponse2 = Arrays.stream(parties).mapToInt(this::getScore2).sum();
    }

    private int getScore1(String partie) {
        var partieSplit = partie.split(" ");
        var choixOpponent = getChoix(partieSplit[0]);
        var monChoix = getChoix(partieSplit[1]);

        return scorePartie(choixOpponent, monChoix) + valeurChoix(monChoix);
    }

    private String getChoix(String code) {
        return switch (code) {
            case "A", "X" -> "✊";
            case "B", "Y" -> "🤚";
            case "C", "Z" -> "✌";
            default -> throw new IllegalStateException("Unexpected value: " + code);
        };
    }

    private int scorePartie(String opponent, String me) {
        Integer resultat = switch (opponent) {
            case "✊" -> me.equals("🤚") ? 6 : null;
            case "🤚" -> me.equals("✌") ? 6 : null;
            case "✌" -> me.equals("✊") ? 6 : null;
            default -> throw new IllegalStateException("Unexpected value: " + opponent);
        };
        if (resultat == null) {
            resultat = opponent.equals(me) ? 3 : 0;
        }
        return resultat;
    }

    private int getScore2(String partie) {
        var partieSplit = partie.split(" ");
        var choixOpponent = getChoix(partieSplit[0]);
        var monChoix = getMonChoix(choixOpponent, partieSplit[1]);

        return scorePartie(choixOpponent, monChoix) + valeurChoix(monChoix);
    }

    private String getMonChoix(String choixOpponent, String code) {
        return switch (choixOpponent) {
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
            default -> throw new IllegalStateException("Unexpected value: " + choixOpponent);
        };
    }

    private int valeurChoix(String choix) {
        return switch (choix) {
            case "✊" -> 1;
            case "🤚" -> 2;
            case "✌" -> 3;
            default -> throw new IllegalStateException("Unexpected value: " + choix);
        };
    }

    @Override
    public String toString() {
        return String.format("Reponse 1: '%s'; Reponse 2: '%s'", reponse1, reponse2);
    }

}
