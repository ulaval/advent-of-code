#!/usr/bin/perl
 
use strict;
use warnings;
use List::AllUtils qw(none first);
 
$| = 1;
 
my $subject_number = 7;
my $remainder = 20201227;

open(FILE, 'input.txt') or die;
chomp( my @cle = <FILE> );

 
my $i = 0;
my $val = $subject_number;
while (none { $val  == $_ } @cle) {
    $val = ($val * $subject_number) % $remainder;
    $i++;
}
 
my $autreCle = first { $_ != $val } @cle;
 
my $val2 = $autreCle;
while ($i--) {
    $val2 = ($val2 * $autreCle) % $remainder;
}
 
print $val2;