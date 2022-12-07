#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Switch;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my $sum = 0;
while (<FILE>) {
	chomp;
	while ( s/(\(\)|\[\]|\{\}|\<\>)//g ){
		say $_;
	}
	if (/(\)|\]|\}|\>)/){
		switch($1){
			case ")" {$sum += 3;}
			case "]" {$sum += 57;}
			case "}" {$sum += 1197;}
			case ">" {$sum += 25137;}
		}
	}
}
say $sum;
