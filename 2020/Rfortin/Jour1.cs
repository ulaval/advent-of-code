using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace adventofcode2020
{
    class Jour1
    {
        public int P1()
        {
            var reponse = 0;
            var chiffre = 0;
            var lines = System.IO.File.ReadAllLines(@"../../files/1.txt");
            foreach (var nombre in lines)
            {
                chiffre = Convert.ToInt32(nombre);
                foreach (var nombre2 in lines)
                {
                    if (chiffre != Convert.ToInt32(nombre2) && (chiffre + Convert.ToInt32(nombre2)) == 2020)
                    {
                        reponse = chiffre * Convert.ToInt32(nombre2);
                    }
                }
            }

            return reponse;
        }

        public int P2()
        {
            var reponse = 0;
            var chiffre = 0;
            var chiffre2 = 0;
            var lines = System.IO.File.ReadAllLines(@"../../files/1.txt");
            foreach (var nombre in lines)
            {
                chiffre = Convert.ToInt32(nombre);
                foreach (var nombre2 in lines)
                {
                    if (chiffre != Convert.ToInt32(nombre2))
                    {
                        chiffre2 = Convert.ToInt32(nombre2);
                        foreach (var nombre3 in lines)
                        {
                            if (chiffre != Convert.ToInt32(nombre3) && chiffre2 != Convert.ToInt32(nombre3) && (chiffre + Convert.ToInt32(nombre3) + chiffre2) == 2020)
                            {
                                reponse = chiffre * chiffre2 * Convert.ToInt32(nombre3);
                            }
                        }
                    }
                }
            }

            return reponse;
        }

        public int Jour2()
        {
            var lines = System.IO.File.ReadAllLines(@"../../files/2.txt");
            var reponse = 0;

            foreach (var line in lines)
            {
                var policyMin = Convert.ToInt32(line.Split(' ')[0].Split('-')[0]);
                var policyMax = Convert.ToInt32(line.Split(' ')[0].Split('-')[1]);
                var letter = line.Split(' ')[1].Substring(0,1);
                var password = line.Split(' ')[2];
                var compteurLettre = 0;

                foreach (var lettre in password.ToCharArray())
                {
                    if (lettre == Convert.ToChar(letter))
                    {
                        compteurLettre++;
                    }
                }

                if (compteurLettre >= policyMin && compteurLettre <= policyMax)
                {
                    reponse++;
                }
            }

                return reponse;
        }

        public int Jour2p2()
        {
            var lines = System.IO.File.ReadAllLines(@"../../files/2.txt");
            var reponse = 0;

            foreach (var line in lines)
            {
                var policy1 = Convert.ToInt32(line.Split(' ')[0].Split('-')[0]);
                var policy2 = Convert.ToInt32(line.Split(' ')[0].Split('-')[1]);
                var letter = line.Split(' ')[1].Substring(0, 1);
                var password = line.Split(' ')[2].ToCharArray();
                var trouver = false;

                for (var i=0; i < password.Length; i++)
                {
                    if (i == (policy1 - 1) && password[i] == Convert.ToChar(letter))
                    {
                        if (trouver == false)
                        {
                            trouver = true;
                        } else
                        {
                            trouver = false;
                        }
                    }

                    if (i == (policy2 - 1) && password[i] == Convert.ToChar(letter))
                    {
                        if (trouver == false)
                        {
                            trouver = true;
                        }
                        else
                        {
                            trouver = false;
                        }
                    }
                }
                if (trouver)
                {
                    reponse++;
                }
                
            }

            return reponse;
        }
    }
}
