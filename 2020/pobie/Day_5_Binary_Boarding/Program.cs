using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Day_5
{
    static class Program
    {
        private const int numberOfRows = 128;
        private const int numberOfColumns = 8;

        private const int rowCharsStartIndex = 0;
        private const int rowCharsLength = 7;
        private const int columnCharsStartIndex = 7;
        private const int columnCharsLength = 3;

        private const char rowBack = 'B';
        private const char rowFront = 'F';
        private const char columnLeft = 'L';
        private const char columnRight = 'R';

        static void Main()
        {
            var lines = File.ReadAllLines(@"./input");
            var ids = new List<int>();

            foreach (string line in lines)
            {
                var seat = GetSeat(line, numberOfRows, numberOfColumns);
                ids.Add(GetSeatId(seat.Item1, seat.Item2));
            }

            Console.WriteLine($"The highest seat id is {FindHighestSeatId(ids)}");
            Console.WriteLine($"My seat is : {FindLastSeat(ids)}");
        }


        private static Tuple<int, int> GetSeat(string input, int numberOfRows, int numberOfColumns)
        {
            string rowInput = input.Substring(rowCharsStartIndex, rowCharsLength);
            string columnInput = input.Substring(columnCharsStartIndex, columnCharsLength);
            int row = GetSeat(rowInput, 0, numberOfRows - 1, rowFront, rowBack);
            int column = GetSeat(columnInput, 0, numberOfColumns - 1, columnLeft, columnRight);
            return new Tuple<int, int>(row, column);
        }

        private static int GetSeat(string input, int min, int max, char lowerHalfChar, char upperHalfChar)
        {
            string nextInput = input.Length > 1 ? input.Substring(1, input.Length - 1) : "";

            if (input.Length == 0)
            {
                return min;
            }

            if (input[0] == upperHalfChar)
            {
                int upperHalfMin = min + (max - min) / 2 + 1;
                return GetSeat(nextInput, upperHalfMin, max, lowerHalfChar, upperHalfChar);
            }

            if (input[0] == lowerHalfChar)
            {
                int lowerHalfMax = min + (max - min) / 2;
                return GetSeat(nextInput, min, lowerHalfMax, lowerHalfChar, upperHalfChar);
            }

            return -1;
        }

        private static int GetSeatId(int row, int column)
        {
            return row * 8 + column;
        }

        private static int FindHighestSeatId(List<int> seatIds)
        {
            seatIds.Sort();
            return seatIds.Last();
        }

        private static int FindLastSeat(List<int> seatIds)
        {
            seatIds.Sort();
            for (var i = 1; i < seatIds.Count; i++)
            {
                if (seatIds[i] != seatIds[i - 1] + 1)
                {
                    return seatIds[i] - 1;
                }
            }

            return -1;
        }
    }
}