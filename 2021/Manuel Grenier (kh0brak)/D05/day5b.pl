#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Switch;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my (@lines);
my $n = 1000;

my @arr ;
push @arr, [(0) x $n] for (1..$n);

while (<FILE>) {
	my @match = /(\d+),(\d+) -> (\d+),(\d+)/;
	if ($1==$3){
		for (($2<$4?$2:$4)..($2>$4?$2:$4)){
			$arr[$1][$_]++ ;
		}
	}elsif($2==$4){
		for (($1<$3?$1:$3)..($1>$3?$1:$3)){
			$arr[$_][$2]++ ;
		}
	}else{
		for(0..(abs($1-$3))){
			$arr[$1+($1<$3?$_:-$_)][$2+($2<$4?$_:-$_)]++;
		}
	}
}
my $cnt = 0;
foreach (@arr){
	foreach (@$_) {$cnt++ if($_>=2);}
}			
say "Reponse : $cnt";