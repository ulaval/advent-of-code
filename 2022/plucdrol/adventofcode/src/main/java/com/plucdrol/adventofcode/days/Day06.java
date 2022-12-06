package com.plucdrol.adventofcode.days;

import java.util.ArrayList;

import lombok.Getter;

@Getter
public class Day06 extends Day {

    private Integer answer1;
    private Integer answer2;

    public Day06(String input) {
        super(6);

        var characters = input.toCharArray();
        var packetDecoder = new PacketDecoder();
        var messageDecoder = new MessageDecoder();
        var foundFirstPacket = false;
        for (var index = 0; index < characters.length; index++) {

            var character = characters[index];

            if (!foundFirstPacket) {
                if (packetDecoder.findMarker(character)) {
                    answer1 = index + 1;
                    foundFirstPacket = true;
                }
            }

            if (messageDecoder.findMarker(character)) {
                answer2 = index + 1;
                break;
            }
        }
    }

    abstract static class Decoder {

        protected final int distinctCount;
        private final ArrayList<Character> lastCharacters;

        public Decoder(int distinctCount) {
            this.distinctCount = distinctCount;
            this.lastCharacters = new ArrayList<>();
        }

        public boolean findMarker(char character) {
            lastCharacters.add(character);
            if (lastCharacters.size() > distinctCount) {
                lastCharacters.remove(0);
                return lastCharacters.stream().distinct().count() == lastCharacters.size();
            } else {
                return false;
            }
        }
    }

    static class PacketDecoder extends Decoder {
        public PacketDecoder() {
            super(4);
        }
    }

    static class MessageDecoder extends Decoder {
        public MessageDecoder() {
            super(14);
        }
    }
}
