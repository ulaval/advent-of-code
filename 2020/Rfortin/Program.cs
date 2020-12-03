using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace adventofcode2020
{
    class Program
    {
        static void Main(string[] args)
        {
            // jour 1
            var jour1 = new Jour1();
            System.Console.WriteLine(jour1.P1());
            System.Console.WriteLine(jour1.P2());

            // jour 2
            var jour2 = new Jour2();
            System.Console.WriteLine(jour2.P1());
            System.Console.WriteLine(jour2.P2());

            Console.WriteLine("Quitter?");
            System.Console.ReadKey();
        }
    }
}
